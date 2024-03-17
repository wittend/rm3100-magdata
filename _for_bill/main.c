//=========================================================================
// main.c
//
// A command line interface for the RM3100 3-axis magnetometer from PNI Sensor Corp.
//
// Author:      David Witten, KD0EAG
// Date:        December 18, 2023
// License:     GPL 3.0
// Note:        replaces i2c.c (using file system calls to read(), write(), etc.
//              with calls to pigpio. 
//              Also adding callbacks on GPIO27 for PPS rising edge.
//=========================================================================
// #include "commands.h"
// #include "cmdmgr.h"
#include <pigpiod_if2.h>
#include "main.h"

//------------------------------------------
// Debugging output
//------------------------------------------
// see main.h

//------------------------------------------
// Macros
//------------------------------------------
#define PPS_GPIO_PIN    27
#define PPS_TIMEOUTSECS 2.0

//------------------------------------------
// Static and Global variables
//------------------------------------------
int volatile PPS_Flag = PPS_FLAG_FALSE;
int volatile killflag = 0;
char   Version[32]      = MAGDATA_VERSION;
static char outBuf[256] = "";

char fifoCtrl[] = "/home/pi/PSWS/Sstat/magctl.fifo";
char fifoData[] = "/home/pi/PSWS/Sstat/magdata.fifo";
int PIPEIN  = -1;
int PIPEOUT = -1;
ctlList ctl;

//---------------------------------------------------------------
//  main()
//---------------------------------------------------------------
int main(int argc, char** argv)
{
//    ctlList ctl;
    ctlList *p = &ctl;
    int     rv = 0;
    FILE    *outfp = stdout;
    char    utcStr[UTCBUFLEN] = "";
    struct  tm *utcTime = getUTC();

#if(_DEBUG)
    fprintf(OUTPUT_PRINT, "\n[CHILD] In %s child process.\n", argv[0]);
    fflush(stdout);
#endif

    //-----------------------------------------
    //  Setup magnetometer parameter defaults.
    //-----------------------------------------
    if(p != NULL)
    {
        memset(p, 0, sizeof(ctlList));
    }

    p->pi = 0;
    p->i2cBusNumber     = RASPI_I2C_BUS1;
    p->magHandle        = 0;
    p->magnetometerAddr = RM3100_I2C_ADDRESS;
    p->localTempHandle  = 0;
    p->localTempAddr    = MCP9808_LCL_I2CADDR_DEFAULT;
    p->remoteTempHandle = 0;
    p->remoteTempAddr   = MCP9808_RMT_I2CADDR_DEFAULT;
    p->doBistMask       = 0;
    p->cc_x             = CC_400;
    p->cc_y             = CC_400;
    p->cc_z             = CC_400;
    p->x_gain           = GAIN_150;
    p->y_gain           = GAIN_150;
    p->z_gain           = GAIN_150;
    p->tsMilliseconds   = 0;
    p->TMRCRate         = 0x96;
    p->Version          = Version;
    p->samplingMode     = POLL;
    p->readBackCCRegs   = FALSE;
    p->CMMSampleRate    = 400;
    p->NOSRegValue      = 10;
    p->DRDYdelay        = 10;
    p->magRevId         = 0x0;
    p->usePipes         = USE_PIPES;
    p->pipeInPath       = fifoCtrl;
    p->pipeOutPath      = fifoData;
    p->readBackCCRegs   = FALSE;

//    if((rv = getCommandLine(argc, argv, p)) != 0)
//    {
//        return rv;
//    }

#if(USE_PIPES)
    //-----------------------------------------
    //  Setup the I/O pipes
    //-----------------------------------------
    int  fdPipeIn;
    int  fdPipeOut;

    if(p->usePipes == TRUE)
    {
        // Notice that fdPipeOut and fdPipeIn are intentionally reversed.
        if(!(fdPipeOut = open(p->pipeInPath, O_WRONLY | O_CREAT)))
        {
            perror("    [CHILD] Open PIPE Out failed: ");
            fprintf(OUTPUT_PRINT, p->pipeInPath);
            exit(1);
        }
#if(_DEBUG)
         else
        {
            fprintf(OUTPUT_PRINT, "    [CHILD] Open PIPE Out OK.\n");
            fflush(OUTPUT_PRINT);
            PIPEOUT = fdPipeOut;
        }
#endif

        if(!(fdPipeIn = open(p->pipeOutPath, O_RDONLY | O_CREAT)))
        {    
            perror("    [CHILD] Open PIPE In failed: ");
            fprintf(OUTPUT_PRINT, p->pipeInPath);
            exit(1);
        }
#if(_DEBUG)
        else
        {
            fprintf(OUTPUT_PRINT, "    [CHILD] Open PIPE In OK.\n");
            fflush(OUTPUT_PRINT);
            PIPEIN = fdPipeIn;
        }
#endif
    }

#endif // USE_PIPES

    unsigned edge_cb_id = 0;
    
#if(_DEBUG)
    fprintf(OUTPUT_PRINT, "    [CHILD] Before setting up GPIO.\n");
    fflush(OUTPUT_PRINT);
#endif

    //-----------------------------------------
    //  Initialize the PIGPIO interface.
    //-----------------------------------------
    if((p->pi = initGPIO(p)) < 0)
    {
        utcTime = getUTC();
        strftime(utcStr, UTCBUFLEN, "%d %b %Y %T", utcTime);
        fprintf(OUTPUT_PRINT, "    [CHILD] {ts: \"%s\", lastStatus: \"Unable to set up GPIO.\"}", utcStr); 
        fflush(OUTPUT_PRINT);
        exit(2);
    }

    //-----------------------------------------
    //  Verify the Mag sensor presence and Version.
    //-----------------------------------------
    if(verifyMagSensor(p))
    {
        utcTime = getUTC();
        strftime(utcStr, UTCBUFLEN, "%d %b %Y %T", utcTime);
        fprintf(OUTPUT_ERROR, "    [CHILD] {ts: \"%s\", lastStatus: \"Unable to Verify the magnetometer.\"}", utcStr); 
        fflush(OUTPUT_ERROR);
        exit(2);
    }
    else
    {
        //-----------------------------------------
        //  Initialize the Mag sensor registers.
        //-----------------------------------------
        if(initMagSensor(p))
        {
            utcTime = getUTC();
            strftime(utcStr, UTCBUFLEN, "%d %b %Y %T", utcTime);
            fprintf(OUTPUT_ERROR, "    [CHILD] {ts: \"%s\", lastStatus: \"Unable to initialize the magnetometer.\"}", utcStr); 
            fflush(OUTPUT_ERROR);
            exit(2);
        }
    }

    //-----------------------------------------
    //  Setup the PPS calback notification.
    //-----------------------------------------
    if((rv = set_mode(p->pi, (unsigned) PPS_GPIO_PIN, PI_INPUT) == 0))
    {
        if((edge_cb_id = callback(p->pi, (unsigned) PPS_GPIO_PIN, RISING_EDGE, (CBFunc_t) onEdge)) != 0)                   // RISING_EDGE, FALLING_EDGE, or EITHER_EDGE
        {
            switch(edge_cb_id)
            {
                case pigif_bad_malloc:
                    fprintf(OUTPUT_PRINT, "    [CHILD] After setting up callback, return value = [pgif_bad_malloc]\n");
                    fflush(OUTPUT_PRINT);
                    exit(2);
                    break;
                case pigif_duplicate_callback:
                    fprintf(OUTPUT_PRINT, "    [CHILD] After setting up callback, return value = [pigif_duplicate_callback]\n");
                    fflush(OUTPUT_PRINT);
                    exit(2);
                    break;
                case pigif_bad_callback:
                    fprintf(OUTPUT_PRINT, "    [CHILD] After setting up callback, return value = [pigif_bad_callback]\n");
                    fflush(OUTPUT_PRINT);
                    exit(2);
                    break;
            }
        }
    }

    //-----------------------------------------
    //  Main program loop.
    //-----------------------------------------
    while(1)
    {
        if(PPS_Flag == PPS_FLAG_TRUE)
        { 
            PPS_Flag = PPS_FLAG_FALSE;
            formatOutput(p, outBuf);
            fflush(outfp);
        }
#ifdef USE_WAITFOREDGE
        if(!(rv = wait_for_edge(p->pi, (unsigned) PPS_GPIO_PIN, RISING_EDGE, PPS_TIMEOUTSECS)))
        {
            char outstr[MAXPATHBUFLEN] = "";
            utcTime = getUTC();
            strftime(utcStr, UTCBUFLEN, "%d %b %Y %T", utcTime);                // RFC 2822: "%a, %d %b %Y %T %z"      RFC 822: "%a, %d %b %y %T %z"
            sprintf(outstr, "   [CHILD]: {ts: \"%s\", lastStatus: \"Missed PPS Timeout!\"}", utcStr); 

#if(CONSOLE_OUTPUT)
            fprintf(OUTPUT_PRINT, outstr);
            fflush(OUTPUT_PRINT);
#else
            sprintf(outstr, "   [CHILD]: {ts: \"%s\", lastStatus: \"Missed PPS Timeout!\"}", utcStr); 
            write(PIPEOUT, outstr);
#endif      // CONSOLE_OUTPUT

            // Set exit return value.
            rv = 2;
            break;
        }
#endif      // USE_WAITFOREDGE
    }

    //-----------------------------------------
    //  Cleanup Callback, PIGPIO, and exit.
    //-----------------------------------------
    termGPIO(p);
    exit(rv);
}

//---------------------------------------------------------------
// void formatOutput(volatile ctlList *p, char *outBuf)
//---------------------------------------------------------------
char *formatOutput(volatile ctlList *p, char *outBuf)
{
    char fmtBuf[128] = "";
    int fmtBuf_len = sizeof fmtBuf;
    struct tm *utcTime = getUTC();
    char utcStr[128] = "";
    double xyz[3];
    int localTemp  = 0;
    int remoteTemp = 0;
    float rcLocalTemp = 0.0;
    float rcRemoteTemp = 0.0;

    strncpy(outBuf, "", 1);

    localTemp    = readLocalTemp(p);
    rcLocalTemp  = localTemp * 0.0625;

    remoteTemp   = readRemoteTemp(p);
    rcRemoteTemp = remoteTemp * 0.0625;

    readMagPOLL(p);

    xyz[0] = (((double)p->XYZ[0] / p->NOSRegValue) / p->x_gain);
    xyz[1] = (((double)p->XYZ[1] / p->NOSRegValue) / p->y_gain);
    xyz[2] = (((double)p->XYZ[2] / p->NOSRegValue) / p->z_gain);

    snprintf(fmtBuf, fmtBuf_len, "{ ");
    strncat(outBuf, fmtBuf, strlen(fmtBuf));

    utcTime = getUTC();

#if(FOR_GRAPE2)
    strftime(utcStr, UTCBUFLEN, "%Y%m%e%y%M%S", utcTime);               // YYYYMMDDHHMMSS  (Gaak!)
    snprintf(fmtBuf, fmtBuf_len, "\"ts\":%s", utcStr);
#else
    strftime(utcStr, UTCBUFLEN, "%d %b %Y %T", utcTime);                // RFC 2822: "%a, %d %b %Y %T %z"
    snprintf(fmtBuf, fmtBuf_len, "\"ts\":\"%s\"", utcStr);
#endif

    strncat(outBuf, fmtBuf, strlen(fmtBuf));

    fmtBuf[0] = 0;
    if(rcLocalTemp < -100.0)
    {
        snprintf(fmtBuf, fmtBuf_len, ", \"lt\": 0.0");
        strncat(outBuf, fmtBuf, strlen(fmtBuf));
    }
    else
    {
        snprintf(fmtBuf, fmtBuf_len, ", \"lt\": %.2f",  rcLocalTemp);
        strncat(outBuf, fmtBuf, strlen(fmtBuf));
    }

    fmtBuf[0] = 0;
    if(rcRemoteTemp < -100.0)
    {
        snprintf(fmtBuf, fmtBuf_len, ", \"rt\": 0.0");
        strncat(outBuf, fmtBuf, strlen(fmtBuf));
    }
    else
    {
        snprintf(fmtBuf, fmtBuf_len, ", \"rt\": %.2f",  rcRemoteTemp);
        strncat(outBuf, fmtBuf, strlen(fmtBuf));
    }

    snprintf(fmtBuf, fmtBuf_len, ", \"x\":%.3f", xyz[0]);
    strncat(outBuf, fmtBuf, strlen(fmtBuf));
    snprintf(fmtBuf, fmtBuf_len, ", \"y\":%.3f", xyz[1]);
    strncat(outBuf, fmtBuf, strlen(fmtBuf));
    snprintf(fmtBuf, fmtBuf_len, ", \"z\":%.3f", xyz[2]);
    strncat(outBuf, fmtBuf, strlen(fmtBuf));

    snprintf(fmtBuf, fmtBuf_len, " }\n");
    strncat(outBuf, fmtBuf, strlen(fmtBuf));

#if(CONSOLE_OUTPUT)
    fprintf(OUTPUT_PRINT, "    [CHILD]: %s", outBuf);
    fflush(OUTPUT_PRINT);
#else
    write(PIPEOUT, outBuf);
#endif

    return outBuf;
}

//------------------------------------------
// readLocalTemp(volatile ctlList *p)
//------------------------------------------
int readLocalTemp(volatile ctlList *p)
{
    int rv = 0;
    int temp = -9999;
    char data[2] = {0};

    rv = i2c_read_i2c_block_data(p->pi, p->localTempHandle, MCP9808_REG_AMBIENT_TEMP, (char *)data, 2);
    if(rv < 0)
    {
        fprintf(OUTPUT_ERROR, "Error : I/O error reading temp  Local Handle: [%i] sensor at address: [0x%2X].\n", p->localTempHandle, MCP9808_REG_AMBIENT_TEMP);
        showPIGPIOErrMsg(rv);
    }
    else
    {
        // Convert the data to 13-bits
        temp = (int)((data[0] & 0x1F) * 256 + data[1]);
        if(temp > 4095)
        {
            temp -= 8192;
        }
        return temp;
    }
    return rv;
}

//------------------------------------------
// readRemoteTemp(volatile ctlList *p)
//------------------------------------------
int readRemoteTemp(volatile ctlList *p)
{
    int rv = 0;
    int temp = -9999;
    char data[2] = {0};

    rv = i2c_read_i2c_block_data(p->pi, p->remoteTempHandle, MCP9808_REG_AMBIENT_TEMP, (char *) data, 2);
    if(rv != 2)
    {
        fprintf(OUTPUT_ERROR, "Error : I/O error reading temp Remote Handle: [%i] sensor at address: [0x%2X].\n", p->remoteTempHandle, MCP9808_REG_AMBIENT_TEMP);
        showPIGPIOErrMsg(rv);
    }
    else
    {
        // Convert the data to 13-bits
        temp = (int)((data[0] & 0x1F) * 256 + data[1]);
        if(temp > 4095)
        {
            temp -= 8192;
        }
        return temp;
    }
    return rv;
}


//------------------------------------------
// readMagPOLL()
//------------------------------------------
int readMagPOLL(volatile ctlList *p)
{
    int     rv = 0;
    int     bytes_read = 9;
    short   pmMode = (PMMODE_ALL);

    char    xyzBuf[XYZ_BUFLEN] = "";

    // Write command to  use Polled measurement Mode.
    rv = i2c_write_byte_data(p->pi, p->magHandle, RM3100_MAG_POLL, pmMode);
    if(rv != 0)
    {
        showPIGPIOErrMsg(rv);
        usleep(p->DRDYdelay);
    }

    // If a delay is specified after DRDY goes high, sleep it off.
    if(p->DRDYdelay)
    {
        usleep(p->DRDYdelay);
    }

    // Tell the sensor that you want to read XYZ data. RM3100I2C_POLLXYZ
    // rv = i2c_write_byte_data(p->pi, p->magHandle, RM3100I2C_XYZ, TRUE);
    rv = i2c_write_byte(p->pi, p->magHandle, RM3100I2C_XYZ);
    if(rv < 0)
    {
        showPIGPIOErrMsg(p->magHandle);
    }
    else if(rv == 0)
    {
        // Wait for DReady Flag.
        rv = i2c_read_byte(p->pi, p->magHandle);
        rv = (rv & RM3100I2C_READMASK);
        while((rv != RM3100I2C_READMASK))
        {
            rv = i2c_read_byte(p->pi, p->magHandle);
            rv = (rv & RM3100I2C_READMASK);
        }

        // Read the data registers.
        rv = i2c_read_i2c_block_data(p->pi, p->magHandle, RM3100I2C_XYZ, (char *)xyzBuf, XYZ_BUFLEN);
        if(rv == XYZ_BUFLEN)
        {
            p->XYZ[0] = ((signed char)xyzBuf[0]) * 256 * 256;
            p->XYZ[0] |= xyzBuf[1] * 256;
            p->XYZ[0] |= xyzBuf[2];

            p->XYZ[1] = ((signed char)xyzBuf[3]) * 256 * 256;
            p->XYZ[1] |= xyzBuf[4] * 256;
            p->XYZ[1] |= xyzBuf[5];

            p->XYZ[2] = ((signed char)xyzBuf[6]) * 256 * 256;
            p->XYZ[2] |= xyzBuf[7] * 256;
            p->XYZ[2] |= xyzBuf[8];
        }
        else
        {
            showPIGPIOErrMsg(rv);
        }
    }
    return bytes_read;
}

//---------------------------------------------------------------
// void verifyMagSensor(volatile ctlList *p)
//---------------------------------------------------------------
int verifyMagSensor(volatile ctlList *p)
{
    int rv = 0;
    char revBuf[] = {0};

    //-----------------------------------------
    // Make sure PGPIO connection is OK.
    //-----------------------------------------
    if(p->pi >= 0)
    {
        p->magRevId = 0;

        //-----------------------------------------
        // Read the version register.
        //-----------------------------------------
        if((rv = i2c_read_i2c_block_data(p->pi, p->magHandle, RM3100I2C_REVID, revBuf, 1)) > 0)
        {
            p->magRevId = *revBuf;
            if(*revBuf != (uint8_t) RM3100_VER_EXPECTED)
            {
                // Fail, exit...
                fprintf(OUTPUT_ERROR, "\n    [Child]: RM3100 REVID NOT CORRECT: ");
                fprintf(OUTPUT_ERROR, "RM3100 REVID: 0x%X <> EXPECTED: 0x%X.\n\n", (unsigned) p->magRevId, RM3100_VER_EXPECTED);
                fflush(OUTPUT_ERROR);
                return 1;
            }
            else
            {
                return 0;
            }
        }
        else
        {
            showPIGPIOErrMsg(rv);
            return(1);
        }
    }
    return 0;
}

//------------------------------------------
// setNOSReg(volatile ctlList *p)
//------------------------------------------
int setNOSReg(volatile ctlList *p)
{
    int rv = 0;
#if _DEBUG
    fprintf(OUTPUT_PRINT, "    [Child]: In setNOSReg():: Setting undocumented NOS register to value: %2X\n", p->NOSRegValue);
#endif
    rv = i2c_write_byte_data(p->pi, p->magHandle, RM3100I2C_NOS, p->NOSRegValue);

    return rv;
}

//------------------------------------------
// getCCGainEquiv()
//   Gn=(Aval*(0.3671*Cycnt+1.5)/1000)
//------------------------------------------
unsigned short getCCGainEquiv(unsigned short CCVal)
{
    unsigned short gain = 0;
    double dGain = (0.3671 * CCVal + 1.5); 
    gain = (unsigned short) dGain;

    return gain;
}

//------------------------------------------
// setCycleCounts_by_Reg()
//------------------------------------------
void setCycleCounts_by_Reg(volatile ctlList *p)
{

    i2c_write_byte_data(p->pi, p->magHandle, RM3100I2C_CCX_1, (p->cc_x >> 8));
    i2c_write_byte_data(p->pi, p->magHandle, RM3100I2C_CCX_0, (p->cc_x & 0xff));
    p->x_gain = getCCGainEquiv(p->cc_x);

    i2c_write_byte_data(p->pi, p->magHandle, RM3100I2C_CCY_1, (p->cc_y >> 8));
    i2c_write_byte_data(p->pi, p->magHandle, RM3100I2C_CCY_0, (p->cc_y & 0xff));
    p->y_gain = getCCGainEquiv(p->cc_y);

    i2c_write_byte_data(p->pi, p->magHandle, RM3100I2C_CCZ_1, (p->cc_z >> 8));
    i2c_write_byte_data(p->pi, p->magHandle, RM3100I2C_CCZ_0, (p->cc_z & 0xff));
    p->z_gain = getCCGainEquiv(p->cc_z);

#if _DEBUG
    fprintf(OUTPUT_PRINT, "\nIn setCycleCountRegs():: Setting NOS register to value: %2X\n", p->NOSRegValue);
    fprintf(OUTPUT_PRINT, "CycleCounts  - X: %u, Y: %u, Z: %u.\n", p->cc_x, p->cc_y, p->cc_x);
    fprintf(OUTPUT_PRINT, "Gains        - X: %u, Y: %u, Z: %u.\n", p->x_gain, p->y_gain, p->z_gain);
    fprintf(OUTPUT_PRINT, "NOS Register - %2X.\n", p->NOSRegValue);
    fflush(OUTPUT_PRINT);
#endif

}

//------------------------------------------
// setCycleCountsReg(volatile ctlList *p)
// - alternative all in-one-write method.
//------------------------------------------
int setCycleCountsReg(volatile ctlList *p)
{
    int rv = 0;
#if _DEBUG
    fprintf(OUTPUT_PRINT, "    [Child]: In setCycleCountsReg():: Setting undocumented NOS register to value: %2X\n", p->NOSRegValue);
#endif
    // Write it all at once:
    unsigned char regBuf[] = {0x90, 0x01, 0x90, 0x01, 0x90, 0x01}; 
    rv = i2c_write_i2c_block_data(p->pi, p->magHandle, RM3100I2C_CCX_1, (char *)regBuf, 6);

    return rv;
}

//------------------------------------------
// readCycleCountRegs()
//------------------------------------------
void readCycleCountRegs(volatile ctlList *p)
{
    int rv = 0;
    uint8_t regCC[7]= { 0, 0, 0, 0, 0, 0, 0 };

    rv = i2c_read_i2c_block_data(p->pi, p->magHandle, RM3100I2C_CCX_1, (char *)regCC, 7);
    if(rv > 0)
    {
        fprintf(OUTPUT_PRINT, "regCC[%i]: 0x%X\n",    0, (uint8_t)regCC[0]);
        fprintf(OUTPUT_PRINT, "regCC[%i]: 0x%X\n",    1, (uint8_t)regCC[1]);
        fprintf(OUTPUT_PRINT, "regCC[%i]: 0x%X\n",    2, (uint8_t)regCC[2]);
        fprintf(OUTPUT_PRINT, "regCC[%i]: 0x%X\n",    3, (uint8_t)regCC[3]);
        fprintf(OUTPUT_PRINT, "regCC[%i]: 0x%X\n",    4, (uint8_t)regCC[4]);
        fprintf(OUTPUT_PRINT, "regCC[%i]: 0x%X\n",    5, (uint8_t)regCC[5]);
        fprintf(OUTPUT_PRINT, "NOS:      0x%X\n\n",     (uint8_t)regCC[6]);
        fflush(OUTPUT_PRINT);
    }
}

//---------------------------------------------------------------
// void initGPIO(volatile ctlList *p)
//---------------------------------------------------------------
int initGPIO(volatile ctlList *p)
{
    //-----------------------------------------
    // Try to connect to pigpio daemon.
    //-----------------------------------------
    if((p->pi = pigpio_start(NULL, NULL)) >= 0)
    {
    }
    else
    {
        return -1;
    }

    //-----------------------------------------
    // Register the Magnetometer address.
    //-----------------------------------------
    p->magHandle = i2c_open(p->pi, (unsigned) RASPI_I2C_BUS1, (unsigned) RM3100_I2C_ADDRESS, (unsigned) 0);
    if(p->magHandle >= 0)
    {
        fprintf(OUTPUT_PRINT, "    [CHILD] i2c_open(RM3100) Magnetometer OK. Reg: %i, Handle: %i\n", RM3100_I2C_ADDRESS, p->magHandle );
        fflush(OUTPUT_PRINT);
    }
    else
    {
        fprintf(OUTPUT_PRINT, "    [CHILD] i2c_open(RM3100) Magnetometer FAIL. Reg: %i, Handle: %i\n", RM3100_I2C_ADDRESS, p->magHandle );
        fflush(OUTPUT_PRINT);
        return -1;
    }

    setNOSReg(p);
    setCycleCounts_by_Reg(p);
#if _DEBUG
    readCycleCountRegs(p);
#endif

    //-----------------------------------------
    // Register the Local Temp Sensor address.
    //-----------------------------------------
    p->localTempHandle = i2c_open(p->pi, (unsigned) RASPI_I2C_BUS1, (unsigned) 0x18, (unsigned) 0);
    if(p->localTempHandle >= 0)
    {
#if _DEBUG
        fprintf(OUTPUT_PRINT, "    [CHILD] i2c_open(MCP9808) Local Temp OK. Reg: %i, Handle: %i\n", MCP9808_LCL_I2CADDR_DEFAULT, p->localTempHandle );
        fflush(OUTPUT_PRINT);
#endif
    }
    else
    {
#if _DEBUG
        fprintf(OUTPUT_PRINT, "    [CHILD] i2c_open(MCP9808) Local Temp FAIL. Reg: %i, Handle: %i\n", MCP9808_LCL_I2CADDR_DEFAULT, p->localTempHandle );
        fflush(OUTPUT_PRINT);
#endif
        showPIGPIOErrMsg(p->localTempHandle);
        return -1;
    }

    //-----------------------------------------
    // Register the Remote Temp Sensor address.
    //-----------------------------------------
    p->remoteTempHandle = i2c_open(p->pi, (unsigned) RASPI_I2C_BUS1, (unsigned) 0x19, (unsigned) 0);
    if(p->remoteTempHandle >= 0)
    {
#if _DEBUG
        fprintf(OUTPUT_PRINT, "    [CHILD] i2c_open(MCP9808) Remote Temp OK. Reg: %i, Remote Handle: %i\n", MCP9808_RMT_I2CADDR_DEFAULT, p->remoteTempHandle );
        fflush(OUTPUT_PRINT);
#endif
    }
    else
    {
#if _DEBUG
        fprintf(OUTPUT_PRINT, "    [CHILD] i2c_open(MCP9808) Remote Temp FAIL. Reg: %i, Remote Handle: %i\n", MCP9808_RMT_I2CADDR_DEFAULT, p->remoteTempHandle );
        fflush(OUTPUT_PRINT);
#endif
        showPIGPIOErrMsg(p->remoteTempHandle);
        return -1;
    }
    return p->pi;
}

//---------------------------------------------------------------
// void termGPIO(volatile ctlList p)
//---------------------------------------------------------------
void termGPIO(volatile ctlList *p)
{
    // Knock down all of the pigpio setup here.
    p->magHandle = i2c_close(p->pi, p->magHandle);
    p->localTempHandle = i2c_close(p->pi, p->localTempHandle);
    p->remoteTempHandle = i2c_close(p->pi, p->remoteTempHandle);
    pigpio_stop(p->pi);
}

//---------------------------------------------------------------
// int initMagSensor(volatile ctlList *p)
//---------------------------------------------------------------
int initMagSensor(volatile ctlList *p)
{
    int rv = 0;

    // Setup the Mag sensor register initial state here.
    if(p->samplingMode == POLL)                                         
    {
        if((rv = i2c_write_byte_data(p->pi, p->magHandle, RM3100_MAG_POLL, TRUE)) != 0)
        {
            showPIGPIOErrMsg(rv);
            return FALSE;
        }
    }
    else
    {
        if((rv = i2c_write_byte_data(p->pi, p->magHandle, RM3100I2C_CMM, TRUE) != 0))
        {
            showPIGPIOErrMsg(rv);
            return FALSE;
        }
    }
    return rv;
}

//---------------------------------------------------------------
// void showPIGPIOErrMsg(int rv)
//---------------------------------------------------------------
void showPIGPIOErrMsg(int rv)
{
    char    utcStr[UTCBUFLEN] = "";
    struct  tm *utcTime = getUTC();  
    strftime(utcStr, UTCBUFLEN, "%d %b %Y %T", utcTime);
#if(CONSOLE_OUTPUT)
    fprintf(OUTPUT_PRINT, "    [Child]: { \"ts\": \"%s\", \"lastError\": \"%s\" }\n", utcStr, pigpio_error(rv));
    fflush(OUTPUT_PRINT);
#else
    char errstr[MAXPATHBUFLEN] = "";
    sprintf(errstr, "    [Child]: { \"ts\": \"%s\", \"lastError\": \"%s\" }\n", utcStr, pigpio_error(rv));
    write(PIPEOUT, errstr);
#endif
}

//------------------------------------------
// getUTC()
//------------------------------------------
struct tm *getUTC()
{
    time_t now = time(&now);
    if(now == -1)
    {
        puts("The time() function failed");
    }
    struct tm *ptm = gmtime(&now);
    if(ptm == NULL)
    {
        puts("The gmtime() function failed");
    }
    return ptm;
}

//---------------------------------------------------------------
// void onEdge(void)
//---------------------------------------------------------------
void onEdge(void)
{
    PPS_Flag = PPS_FLAG_TRUE;
}

