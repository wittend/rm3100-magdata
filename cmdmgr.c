//=========================================================================
// cmdmgr.c
//
// commandline / configuration management routines for runMag utility.
//
// Author:      David Witten, KD0EAG
// Date:        December 18, 2023
// License:     GPL 3.0
// Note:        replaces i2c.c (using file system calls to read(), write(), etc.
//              with calls to pigpio. 
//              Also adding callbacks on GPIO27 for PPS rising edge.
//=========================================================================
#include "main.h"
#include "cmdmgr.h"

extern char Version;

//------------------------------------------
// currentTimeMillis()
//------------------------------------------
long currentTimeMillis()
{
    struct timeval time;
    gettimeofday(&time, NULL);
    return time.tv_sec * 1000 + time.tv_usec / 1000;
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

//------------------------------------------
// showSettings()
//------------------------------------------
void showSettings(ctlList *p)
{
    char pathStr[128] = "";
    snprintf(pathStr, sizeof(pathStr), "/dev/i2c-%i", p->i2cBusNumber);

    fprintf(stdout, "\nVersion = %s\n", p->Version);
    fprintf(stdout, "\nCurrent Parameters:\n\n");
#if (USE_PIPES)
    fprintf(stdout, "   Log output to pipes:                        %s\n",          p->usePipes ? "TRUE" : "FALSE");
    fprintf(stdout, "   Input file path:                            %s\n",          p->pipeInPath);
    fprintf(stdout, "   Output file path:                           %s\n",          p->pipeOutPath);
#endif
    fprintf(stdout, "   I2C bus number as integer:                  %i (dec)\n",    p->i2cBusNumber);
    fprintf(stdout, "   I2C bus path as string:                     %s\n",          pathStr);
    fprintf(stdout, "   Built in self test (BIST) value:            %02X (hex)\n",  p->doBistMask);
    fprintf(stdout, "   Device sampling mode:                       %s\n",          p->samplingMode     ? "CONTINUOUS" : "POLL");
    fprintf(stdout, "   Data ready delay value:                     %i (dec)\n",    p->DRDYdelay);
    fprintf(stdout, "   Cycle counts by vector:                     X: %3i (dec), Y: %3i (dec), Z: %3i (dec)\n", p->cc_x, p->cc_y, p->cc_z);
    fprintf(stdout, "   Gain by vector:                             X: %3i (dec), Y: %3i (dec), Z: %3i (dec)\n", p->x_gain, p->y_gain, p->z_gain);
    fprintf(stdout, "   Read back CC Regs after set:                %s\n",          p->readBackCCRegs   ? "TRUE" : "FALSE");
//    fprintf(stdout, "   CMM sample rate:                            %2X (hex)\n",   p->CMMSampleRate);
    fprintf(stdout, "   TMRC reg value:                             %2X (hex)\n",   p->TMRCRate);
    fprintf(stdout, "   Remote temperature address:                 %02X (hex)\n",  p->remoteTempAddr);
    fprintf(stdout, "   Magnetometer address:                       %02X {hex)\n",  p->magnetometerAddr);
    fprintf(stdout, "\n\n");
}

//------------------------------------------
// getCommandLine()
//------------------------------------------
int getCommandLine(int argc, char** argv, ctlList *p)
{
    int c;
//    int NOSval = 0;
//    int magAddr = 0;
//    int lTmpAddr = 0;
//    int rTmpAddr = 0;

//    if(p != NULL)
//    {
//        memset(p, 0, sizeof(ctlList));
//    }
//
//    p->cc_x             = CC_400;
//    p->cc_y             = CC_400;
//    p->cc_z             = CC_400;
//    p->x_gain           = GAIN_150;
//    p->y_gain           = GAIN_150;
//    p->z_gain           = GAIN_150;
//
//    p->samplingMode     = POLL;
//    p->readBackCCRegs   = FALSE;
//    p->CMMSampleRate    = 400;
// 
//    p->remoteTempAddr   = MCP9808_RMT_I2CADDR_DEFAULT;
//    p->magnetometerAddr = RM3100_I2C_ADDRESS;
//    p->tsMilliseconds   = FALSE;
//    p->TMRCRate         = 0x96;

    while((c = getopt(argc, argv, "?B:c:CD:g:V")) != -1)
    {
        //int this_option_optind = optind ? optind : 1;
        switch(c)
        {
            case 'B':
                p->doBistMask = atoi(optarg);
                // printf("Not implemented yet.");
                break;
            case 'C':
                p->readBackCCRegs = TRUE;
                break;
            case 'c':
                p->cc_x = p->cc_y = p->cc_z = atoi(optarg);
                if((p->cc_x > CC_800) || (p->cc_x <= 0))
                {
                    fprintf(stderr, "\n ERROR Invalid: cycle count > 800 (dec) or cycle count  <= 0.\n\n");
                    exit(1);
                }
                p->x_gain = p->y_gain = p->z_gain = getCCGainEquiv(p->cc_x);
                break;
            case 'D':
                p->CMMSampleRate = atoi(optarg);
                break;
            case 'g':
                p->samplingMode = atoi(optarg);
                break;
            case 'V':
                fprintf(stdout, "\nVersion: %s\n", p->Version);
                exit(0);
                break;
            case 'h':
            case '?':
                fprintf(stdout, "\nParameters:\n\n");
                fprintf(stdout, "   -B <reg mask>          :  Do built in self test (BIST).         [ Not implemented ]\n");
                fprintf(stdout, "   -C                     :  Read back cycle count registers before sampling.\n");
                fprintf(stdout, "   -c <count>             :  Set cycle counts as integer.          [ default 200 decimal]\n");
                fprintf(stdout, "   -D <rate>              :  Set magnetometer sample rate.         [ TMRC reg 96 hex default ].\n");
                fprintf(stdout, "   -g <mode>              :  Device sampling mode.                 [ POLL=0 (default), CONTINUOUS=1 ]\n");
                fprintf(stdout, "   -V                     :  Display software version and exit.\n");
                fprintf(stdout, "   -h or -?               :  Display this help.\n\n");
                return 1;
                break;
            default:
                fprintf(stdout, "\n?? getopt returned character code 0x%2X ??\n", c);
                break;
        }
    }
    if(optind < argc)
    {
        printf("non-option ARGV-elements: ");
        while(optind < argc)
        {
            printf("%s ", argv[optind++]);
        }
        printf("\n");
    }
    return 0;
}

