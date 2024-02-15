void getPigpioErrStr(int err);

void getPigpioErrStr(int err)
{
    switch(err)
    {
        case PI_INIT_FAILED:        // -1 
            fputs(stdout,   "gpioInitialise failed.");
            break;
        case PI_BAD_USER_GPIO:        //      -2 
            fputs(stdout,   "GPIO not 0-31.");
            break;
        case PI_BAD_GPIO:        //           -3 
            fputs(stdout,   "GPIO not 0-53.");
            break;
        case PI_BAD_MODE:        //           -4 
            fputs(stdout,   "mode not 0-7.");
            break;
        case PI_BAD_LEVEL:        //          -5 
            fputs(stdout,   "level not 0-1.");
            break;
        case PI_BAD_PUD:        //            -6 
            fputs(stdout,   "pud not 0-2.");
            break;
        case PI_BAD_PULSEWIDTH:        //     -7 
            fputs(stdout,   "pulsewidth not 0 or 500-2500.");
            break;
        case PI_BAD_DUTYCYCLE:        //      -8 
            fputs(stdout,   "dutycycle outside set range.");
            break;
        case PI_BAD_TIMER:        //          -9 
            fputs(stdout,   "timer not 0-9.");
            break;
        case PI_BAD_MS:        //            -10 
            fputs(stdout,   "ms not 10-60000.");
            break;
        case PI_BAD_TIMETYPE:        //      -11 
            fputs(stdout,   "timetype not 0-1.");
            break;
        case PI_BAD_SECONDS:        //       -12 
            fputs(stdout,   "seconds < 0.");
            break;
        case PI_BAD_MICROS:        //        -13 
            fputs(stdout,   "micros not 0-999999.");
            break;
        case PI_TIMER_FAILED:        //      -14 
            fputs(stdout,   "gpioSetTimerFunc failed.");
            break;
        case PI_BAD_WDOG_TIMEOUT:        // -15 
            fputs(stdout,   "timeout not 0-60000.");
            break;
        case PI_NO_ALERT_FUNC:        //     -16 
            fputs(stdout,   "DEPRECATED.");
            break;
        case PI_BAD_CLK_PERIPH:        //    -17 
            fputs(stdout,   "clock peripheral not 0-1.");
            break;
        case PI_BAD_CLK_SOURCE:        //    -18 
            fputs(stdout,   "DEPRECATED.");
            break;
        case PI_BAD_CLK_MICROS:        //    -19 
            fputs(stdout,   "clock micros not 1, 2, 4, 5, 8, or 10.");
            break;
        case PI_BAD_BUF_MILLIS:        //    -20 
            fputs(stdout,   "buf millis not 100-10000.");
            break;
        case PI_BAD_DUTYRANGE:        //     -21 
            fputs(stdout,   "dutycycle range not 25-40000.");
            break;
        case PI_BAD_DUTY_RANGE:        //    -21             
            fputs(stdout,   "DEPRECATED (use PI_BAD_DUTYRANGE).");
            break;
        case PI_BAD_SIGNUM:        //        -22             
            fputs(stdout,   "signum not 0-63.");
            break;
        case PI_BAD_PATHNAME:        //      -23
            fputs(stdout,   "can't open pathname.");
            break;
        case PI_NO_HANDLE:        //         -24             
            fputs(stdout,   "no handle available.");
            break;
        case PI_BAD_HANDLE:        //        -25 
            fputs(stdout,   "unknown handle.");
            break;
        case PI_BAD_IF_FLAGS:        //      -26 
            fputs(stdout,   "ifFlags > 4.");
            break;
        case PI_BAD_CHANNEL:        //       -27 
            fputs(stdout,   "DMA channel not 0-15.");
            break;
        case PI_BAD_PRIM_CHANNEL:        //  -27 
            fputs(stdout,   "DMA primary channel not 0-15.");
            break;
        case PI_BAD_SOCKET_PORT:        //  -28  
            fputs(stdout,   "socket port not 1024-32000.");
            break;
        case PI_BAD_FIFO_COMMAND:        //  -29             
            fputs(stdout,   "unrecognized fifo command.");
            break;
        case PI_BAD_SECO_CHANNEL:        //  -30             
            fputs(stdout,   "DMA secondary channel not 0-15.");
            break;
        case PI_NOT_INITIALISED:        //   -31             
            fputs(stdout,   "function called before gpioInitialise.");
            break;
        case PI_INITIALISED:        //       -32             
            fputs(stdout,   "function called after gpioInitialise.");
            break;
        case PI_BAD_WAVE_MODE:        //     -33             
            fputs(stdout,   "waveform mode not 0-3.");
            break;
        case PI_BAD_CFG_INTERNAL:        //  -34             
            fputs(stdout,   "bad parameter in gpioCfgInternals call.");
            break;
        case PI_BAD_WAVE_BAUD:        //     -35             
            fputs(stdout,   "baud rate not 50-250K(RX)/50-1M(TX).");
            break;
        case PI_TOO_MANY_PULSES:        //   -36             
            fputs(stdout,   "waveform has too many pulses.");
            break;
        case PI_TOO_MANY_CHARS:        //    -37             
            fputs(stdout,   "waveform has too many chars.");
            break;
        case PI_NOT_SERIAL_GPIO:        //   -38             
            fputs(stdout,   "no bit bang serial read on GPIO.");
            break;
        case PI_BAD_SERIAL_STRUC:        //  -39             
            fputs(stdout,   "bad (null) serial structure parameter.");
            break;
        case PI_BAD_SERIAL_BUF:        //   -40             
            fputs(stdout,   "bad (null) serial buf parameter.");
            break;
        case PI_NOT_PERMITTED:        //     -41             
            fputs(stdout,   "GPIO operation not permitted.");
            break;
        case PI_SOME_PERMITTED:        //    -42             
            fputs(stdout,   "one or more GPIO not permitted.");
            break;
        case PI_BAD_WVSC_COMMND:        //   -43             
            fputs(stdout,   "bad WVSC subcommand.");
            break;
        case PI_BAD_WVSM_COMMND:        //   -44             
            fputs(stdout,   "bad WVSM subcommand.");
            break;
        case PI_BAD_WVSP_COMMND:        //   -45             
            fputs(stdout,   "bad WVSP subcommand.");
            break;
        case PI_BAD_PULSELEN :        //     -46             
            fputs(stdout,   "trigger pulse length not 1-100.");
            break;
        case PI_BAD_SCRIPT:        //        -47             
            fputs(stdout,   "invalid script.");
            break;
        case PI_BAD_SCRIPT_ID:        //     -48             
            fputs(stdout,   "unknown script id.");
            break;
        case PI_BAD_SER_OFFSET :        //   -49             
            fputs(stdout,   "add serial data offset > 30 minutes.");
            break;
        case PI_GPIO_IN_USE:        //       -50             
            fputs(stdout,   "GPIO already in use.");
            break;
        case PI_BAD_SERIAL_COUNT:        //  -51             
            fputs(stdout,   "must read at least a byte at a time.");
            break;
        case PI_BAD_PARAM_NUM:        //     -52             
            fputs(stdout,   "script parameter id not 0-9.");
            break;
        case PI_DUP_TAG:        //           -53             
            fputs(stdout,   "script has duplicate tag.");
            break;
        case PI_TOO_MANY_TAGS:        //     -54            
            fputs(stdout,   "script has too many tags.");
            break;
        case PI_BAD_SCRIPT_CMD:        //    -55             
            fputs(stdout,   "illegal script command.");
            break;
        case PI_BAD_VAR_NUM :        //      -56             
            fputs(stdout,   "script variable id not 0-149.");
            break;
        case PI_NO_SCRIPT_ROOM :        //   -57             
            fputs(stdout,   "no more room for scripts.");
            break;
        case PI_NO_MEMORY:        //         -58             
            fputs(stdout,   "can't allocate temporary memory.");
            break;
        case PI_SOCK_READ_FAILED:        //  -59             
            fputs(stdout,   "socket read failed.");
            break;
        case PI_SOCK_WRIT_FAILED:        //  -60             
            fputs(stdout,   "socket write failed.");
            break;
        case PI_TOO_MANY_PARAM:        //    -61             
            fputs(stdout,   "too many script parameters (> 10).");
            break;
        case PI_NOT_HALTED :        //       -62             
            fputs(stdout,   "DEPRECATED.");
            break;
        case PI_SCRIPT_NOT_READY:        //  -62             
            fputs(stdout,   "script initialising.");
            break;
        case PI_BAD_TAG :        //          -63             
            fputs(stdout,   "script has unresolved tag.");
            break;
        case PI_BAD_MICS_DELAY:        //    -64             
            fputs(stdout,   "bad MICS delay (too large).");
            break;
        case PI_BAD_MILS_DELAY:        //    -65             
            fputs(stdout,   "bad MILS delay (too large).");
            break;
        case PI_BAD_WAVE_ID:        //       -66             
            fputs(stdout,   "non existent wave id.");
            break;
        case PI_TOO_MANY_CBS:        //      -67             
            fputs(stdout,   "No more CBs for waveform.");
            break;
        case PI_TOO_MANY_OOL:        //      -68             
            fputs(stdout,   "No more OOL for waveform.");
            break;
        case PI_EMPTY_WAVEFORM :        //   -69             
            fputs(stdout,   "attempt to create an empty waveform.");
            break;
        case PI_NO_WAVEFORM_ID:        //    -70             
            fputs(stdout,   "no more waveforms.");
            break;
        case PI_I2C_OPEN_FAILED:        //   -71             
            fputs(stdout,   "can't open I2C device.");
            break;
        case PI_SER_OPEN_FAILED:        //   -72             
            fputs(stdout,   "can't open serial device.");
            break;
        case PI_SPI_OPEN_FAILED:        //   -73             
            fputs(stdout,   "can't open SPI device.");
            break;
        case PI_BAD_I2C_BUS:        //      -74             
            fputs(stdout,   "bad I2C bus.");
            break;
        case PI_BAD_I2C_ADDR:        //     -75             
            fputs(stdout,   "bad I2C address.");
            break;
        case PI_BAD_SPI_CHANNEL:        //   -76             
            fputs(stdout,   "bad SPI channel.");
            break;
        case PI_BAD_FLAGS:        //         -77             
            fputs(stdout,   "bad i2c/spi/ser open flags.");
            break;
        case PI_BAD_SPI_SPEED:        //     -78             
            fputs(stdout,   "bad SPI speed.");
            break;
        case PI_BAD_SER_DEVICE:        //    -79             
            fputs(stdout,   "bad serial device name.");
            break;
        case PI_BAD_SER_SPEED:        //     -80             
            fputs(stdout,   "bad serial baud rate.");
            break;
        case PI_BAD_PARAM:        //        -81             
            fputs(stdout,   "bad i2c/spi/ser parameter.");
            break;
        case PI_I2C_WRITE_FAILED:        // -82             
            fputs(stdout,   "i2c write failed.");
            break;
        case PI_I2C_READ_FAILED:        //   -83             
            fputs(stdout,   "i2c read failed.");
            break;
        case PI_BAD_SPI_COUNT:        //    -84             
            fputs(stdout,   "bad SPI count.");
            break;
        case PI_SER_WRITE_FAILED:        //  -85             
            fputs(stdout,   "ser write failed.");
            break;
        case PI_SER_READ_FAILED:        //   -86             
            fputs(stdout,   "ser read failed.");
            break;
        case PI_SER_READ_NO_DATA:        //  -87             
            fputs(stdout,   "ser read no data available.");
            break;
        case PI_UNKNOWN_COMMAND:        //   -88             
            fputs(stdout,   "unknown command.");
            break;
        case PI_SPI_XFER_FAILED:        //  -89             
            fputs(stdout,   "spi xfer/read/write failed.");
            break;
        case PI_BAD_POINTER:        //       -90             
            fputs(stdout,   "bad (NULL) pointer.");
            break;
        case PI_NO_AUX_SPI:        //        -91             
            fputs(stdout,   "no auxiliary SPI on Pi A or B.");
            break;
        case PI_NOT_PWM_GPIO:        //      -92             
            fputs(stdout,   "GPIO is not in use for PWM.");
            break;
        case PI_NOT_SERVO_GPIO:        //    -93             
            fputs(stdout,   "GPIO is not in use for servo pulses.");
            break;
        case PI_NOT_HCLK_GPIO:        //     -94             
            fputs(stdout,   "GPIO has no hardware clock.");
            break;
        case PI_NOT_HPWM_GPIO:        //     -95             
            fputs(stdout,   "GPIO has no hardware PWM.");
            break;
        case PI_BAD_HPWM_FREQ:        //    -96             
            fputs(stdout,   "invalid hardware PWM frequency.");
            break;
        case PI_BAD_HPWM_DUTY:        //     -97             
            fputs(stdout,   "hardware PWM dutycycle not 0-1M.");
            break;
        case PI_BAD_HCLK_FREQ:        //     -98             
            fputs(stdout,   "invalid hardware clock frequency.");
            break;
        case PI_BAD_HCLK_PASS:        //     -99             
            fputs(stdout,   "need password to use hardware clock 1.");
            break;
        case PI_HPWM_ILLEGAL:        //     -100             
            fputs(stdout,   "illegal, PWM in use for main clock.");
            break;
        case PI_BAD_DATABITS:        //     -101             
            fputs(stdout,   "serial data bits not 1-32.");
            break;
        case PI_BAD_STOPBITS:        //     -102             
            fputs(stdout,   "serial (half) stop bits not 2-8.");
            break;
        case PI_MSG_TOOBIG:        //       -103             
            fputs(stdout,   "socket/pipe message too big.");
            break;
        case PI_BAD_MALLOC_MODE:        //  -104             
            fputs(stdout,   "bad memory allocation mode.");
            break;
        case PI_TOO_MANY_SEGS:        //    -105             
            fputs(stdout,   "too many I2C transaction segments.");
            break;
        case PI_BAD_I2C_SEG:        //      -106             
            fputs(stdout,   "an I2C transaction segment failed.");
            break;
        case PI_BAD_SMBUS_CMD:        //    -107             
            fputs(stdout,   "SMBus command not supported by driver.");
            break;
        case PI_NOT_I2C_GPIO:        //     -108             
            fputs(stdout,   "no bit bang I2C in progress on GPIO.");
            break;
        case PI_BAD_I2C_WLEN:        //     -109            
            fputs(stdout,   "bad I2C write length.");
            break;
        case PI_BAD_I2C_RLEN :        //    -110             
            fputs(stdout,   "bad I2C read length.");
            break;
        case PI_BAD_I2C_CMD:        //      -111             
            fputs(stdout,   "bad I2C command.");
            break;
        case PI_BAD_I2C_BAUD:        //     -112             
            fputs(stdout,   "bad I2C baud rate, not 50-500k.");
            break;
        case PI_CHAIN_LOOP_CNT:        //   -113             
            fputs(stdout,   "bad chain loop count.");
            break;
        case PI_BAD_CHAIN_LOOP:        //   -114             
            fputs(stdout,   "empty chain loop.");
            break;
        case PI_CHAIN_COUNTER:        //   -115             
            fputs(stdout,   "too many chain counters.");
            break;
        case PI_BAD_CHAIN_CMD:        //    -116             
            fputs(stdout,   "bad chain command.");
            break;
        case PI_BAD_CHAIN_DELAY:        //  -117            
            fputs(stdout,   "bad chain delay micros.");
            break;
        case PI_CHAIN_NESTING:        //    -118             
            fputs(stdout,   "chain counters nested too deeply.");
            break;
        case PI_CHAIN_TOO_BIG:        //    -119             
            fputs(stdout,   "chain is too long.");
            break;
        case PI_DEPRECATED:        //       -120             
            fputs(stdout,   "deprecated function removed.");
            break;
        case PI_BAD_SER_INVERT:        //   -121             
            fputs(stdout,   "bit bang serial invert not 0 or 1.");
            break;
        case PI_BAD_EDGE :        //        -122             
            fputs(stdout,   "bad ISR edge value, not 0-2.");
            break;
        case PI_BAD_ISR_INIT:        //     -123             
            fputs(stdout,   "bad ISR initialisation.");
            break;
        case PI_BAD_FOREVER :        //     -124             
            fputs(stdout,   "loop forever must be last command.");
            break;
        case PI_BAD_FILTER:        //      -125             
            fputs(stdout,   "bad filter parameter.");
            break;
        case PI_BAD_PAD :        //         -126             
            fputs(stdout,   "bad pad number.");
            break;
        case PI_BAD_STRENGTH:        //     -127             
            fputs(stdout,   "bad pad drive strength.");
            break;
        case PI_FIL_OPEN_FAILED:        // -128             
            fputs(stdout,   "file open failed.");
            break;
        case PI_BAD_FILE_MODE:        //    -129             
            fputs(stdout,   "bad file mode.");
            break;
        case PI_BAD_FILE_FLAG:        //    -130             
            fputs(stdout,   "bad file flag.");
            break;
        case PI_BAD_FILE_READ:        //    -131             
            fputs(stdout,   "bad file read.");
            break;
        case PI_BAD_FILE_WRITE:        //   -132             
            fputs(stdout,   "bad file write.");
            break;
        case PI_FILE_NOT_ROPEN:        //   -133             
            fputs(stdout,   "file not open for read.");
            break;
        case PI_FILE_NOT_WOPEN:        //   -134             
            fputs(stdout,   "file not open for write.");
            break;
        case PI_BAD_FILE_SEEK:        //    -135             
            fputs(stdout,   "bad file seek.");
            break;
        case PI_NO_FILE_MATCH:        //    -136             
            fputs(stdout,   "no files match pattern.");
            break;
        case PI_NO_FILE_ACCESS:        //   -137             
            fputs(stdout,   "no permission to access file.");
            break;
        case PI_FILE_IS_A_DIR:        //    -138             
            fputs(stdout,   "file is a directory.");
            break;
        case PI_BAD_SHELL_STATUS:        //  -139            
            fputs(stdout,   "bad shell return status.");
            break;
        case PI_BAD_SCRIPT_NAME:        //  -140             
            fputs(stdout,   "bad script name.");
            break;
        case PI_BAD_SPI_BAUD:        //     -141             
            fputs(stdout,   "bad SPI baud rate, not 50-500k.");
            break;
        case PI_NOT_SPI_GPIO:        //     -142             
            fputs(stdout,   "no bit bang SPI in progress on GPIO.");
            break;
        case PI_BAD_EVENT_ID:        //     -143             
            fputs(stdout,   "bad event id.");
            break;
        case PI_CMD_INTERRUPTED:        //  -144             
            fputs(stdout,   "Used by Python.");
            break;
        case PI_NOT_ON_BCM2711:        //   -145             
            fputs(stdout,   "not available on BCM2711.");
            break;
        case PI_ONLY_ON_BCM2711:        //  -146             
            fputs(stdout,   "only available on BCM2711.");
            break;
        default:
            break;
    }
}

/*
    switch(err)
    {
        case PI_INIT_FAILED:        // -1 
            fputs(stdout,   "gpioInitialise failed.");
            break;
        case PI_BAD_USER_GPIO     -2 
            fputs(stdout,   "GPIO not 0-31.");
            break;
        case PI_BAD_GPIO          -3 
            fputs(stdout,   "GPIO not 0-53.");
            break;
        case PI_BAD_MODE          -4 
            fputs(stdout,   "mode not 0-7.");
            break;
        case PI_BAD_LEVEL         -5 
            fputs(stdout,   "level not 0-1.");
            break;
        case PI_BAD_PUD           -6 
            fputs(stdout,   "pud not 0-2.");
            break;
        case PI_BAD_PULSEWIDTH    -7 
            fputs(stdout,   "pulsewidth not 0 or 500-2500.");
            break;
        case PI_BAD_DUTYCYCLE     -8 
            fputs(stdout,   "dutycycle outside set range.");
            break;
        case PI_BAD_TIMER         -9 
            fputs(stdout,   "timer not 0-9.");
            break;
        case PI_BAD_MS           -10 
            fputs(stdout,   "ms not 10-60000.");
            break;
        case PI_BAD_TIMETYPE     -11 
            fputs(stdout,   "timetype not 0-1.");
            break;
        case PI_BAD_SECONDS      -12 
            fputs(stdout,   "seconds < 0.");
            break;
        case PI_BAD_MICROS       -13 
            fputs(stdout,   "micros not 0-999999.");
            break;
        case PI_TIMER_FAILED     -14 
            fputs(stdout,   "gpioSetTimerFunc failed.");
            break;
        case PI_BAD_WDOG_TIMEOUT -15 
            fputs(stdout,   "timeout not 0-60000.");
            break;
        case PI_NO_ALERT_FUNC    -16 
            fputs(stdout,   "DEPRECATED.");
            break;
        case PI_BAD_CLK_PERIPH   -17 
            fputs(stdout,   "clock peripheral not 0-1.");
            break;
        case PI_BAD_CLK_SOURCE   -18 
            fputs(stdout,   "DEPRECATED.");
            break;
        case PI_BAD_CLK_MICROS   -19 
            fputs(stdout,   "clock micros not 1, 2, 4, 5, 8, or 10.");
            break;
        case PI_BAD_BUF_MILLIS   -20 
            fputs(stdout,   "buf millis not 100-10000.");
            break;
        case PI_BAD_DUTYRANGE    -21 
            fputs(stdout,   "dutycycle range not 25-40000.");
            break;
        case PI_BAD_DUTY_RANGE   -21             fputs(stdout,   "DEPRECATED (use PI_BAD_DUTYRANGE).");
            break;
        case PI_BAD_SIGNUM       -22             fputs(stdout,   "signum not 0-63.");
            break;
        case PI_BAD_PATHNAME     -23             fputs(stdout,   "can't open pathname.");
            break;
        case PI_NO_HANDLE        -24             fputs(stdout,   "no handle available.");
            break;
        case PI_BAD_HANDLE       -25             fputs(stdout,   "unknown handle.");
            break;
        case PI_BAD_IF_FLAGS     -26             fputs(stdout,   "ifFlags > 4.");
            break;
        case PI_BAD_CHANNEL      -27             fputs(stdout,   "DMA channel not 0-15.");
            break;
        case PI_BAD_PRIM_CHANNEL -27             fputs(stdout,   "DMA primary channel not 0-15.");
            break;
        case PI_BAD_SOCKET_PORT  -28             fputs(stdout,   "socket port not 1024-32000.");
            break;
        case PI_BAD_FIFO_COMMAND -29             fputs(stdout,   "unrecognized fifo command.");
            break;
        case PI_BAD_SECO_CHANNEL -30             fputs(stdout,   "DMA secondary channel not 0-15.");
            break;
        case PI_NOT_INITIALISED  -31             fputs(stdout,   "function called before gpioInitialise.");
            break;
        case PI_INITIALISED      -32             fputs(stdout,   "function called after gpioInitialise.");
            break;
        case PI_BAD_WAVE_MODE    -33             fputs(stdout,   "waveform mode not 0-3.");
            break;
        case PI_BAD_CFG_INTERNAL -34             fputs(stdout,   "bad parameter in gpioCfgInternals call.");
            break;
        case PI_BAD_WAVE_BAUD    -35             fputs(stdout,   "baud rate not 50-250K(RX)/50-1M(TX).");
            break;
        case PI_TOO_MANY_PULSES  -36             fputs(stdout,   "waveform has too many pulses.");
            break;
        case PI_TOO_MANY_CHARS   -37             fputs(stdout,   "waveform has too many chars.");
            break;
        case PI_NOT_SERIAL_GPIO  -38             fputs(stdout,   "no bit bang serial read on GPIO.");
            break;
        case PI_BAD_SERIAL_STRUC -39             fputs(stdout,   "bad (null) serial structure parameter.");
            break;
        case PI_BAD_SERIAL_BUF   -40             fputs(stdout,   "bad (null) serial buf parameter.");
            break;
        case PI_NOT_PERMITTED    -41             fputs(stdout,   "GPIO operation not permitted.");
            break;
        case PI_SOME_PERMITTED   -42             fputs(stdout,   "one or more GPIO not permitted.");
            break;
        case PI_BAD_WVSC_COMMND  -43             fputs(stdout,   "bad WVSC subcommand.");
            break;
        case PI_BAD_WVSM_COMMND  -44             fputs(stdout,   "bad WVSM subcommand.");
            break;
        case PI_BAD_WVSP_COMMND  -45             fputs(stdout,   "bad WVSP subcommand.");
            break;
        case PI_BAD_PULSELEN     -46             fputs(stdout,   "trigger pulse length not 1-100.");
            break;
        case PI_BAD_SCRIPT       -47             fputs(stdout,   "invalid script.");
            break;
        case PI_BAD_SCRIPT_ID    -48             fputs(stdout,   "unknown script id.");
            break;
        case PI_BAD_SER_OFFSET   -49             fputs(stdout,   "add serial data offset > 30 minutes.");
            break;
        case PI_GPIO_IN_USE      -50             fputs(stdout,   "GPIO already in use.");
            break;
        case PI_BAD_SERIAL_COUNT -51             fputs(stdout,   "must read at least a byte at a time.");
            break;
        case PI_BAD_PARAM_NUM    -52             fputs(stdout,   "script parameter id not 0-9.");
            break;
        case PI_DUP_TAG          -53             fputs(stdout,   "script has duplicate tag.");
            break;
        case PI_TOO_MANY_TAGS    -54             fputs(stdout,   "script has too many tags.");
            break;
        case PI_BAD_SCRIPT_CMD   -55             fputs(stdout,   "illegal script command.");
            break;
        case PI_BAD_VAR_NUM      -56             fputs(stdout,   "script variable id not 0-149.");
            break;
        case PI_NO_SCRIPT_ROOM   -57             fputs(stdout,   "no more room for scripts.");
            break;
        case PI_NO_MEMORY        -58             fputs(stdout,   "can't allocate temporary memory.");
            break;
        case PI_SOCK_READ_FAILED -59             fputs(stdout,   "socket read failed.");
            break;
        case PI_SOCK_WRIT_FAILED -60             fputs(stdout,   "socket write failed.");
            break;
        case PI_TOO_MANY_PARAM   -61             fputs(stdout,   "too many script parameters (> 10).");
            break;
        case PI_NOT_HALTED       -62             fputs(stdout,   "DEPRECATED.");
            break;
        case PI_SCRIPT_NOT_READY -62             fputs(stdout,   "script initialising.");
            break;
        case PI_BAD_TAG          -63             fputs(stdout,   "script has unresolved tag.");
            break;
        case PI_BAD_MICS_DELAY   -64             fputs(stdout,   "bad MICS delay (too large).");
            break;
        case PI_BAD_MILS_DELAY   -65             fputs(stdout,   "bad MILS delay (too large).");
            break;
        case PI_BAD_WAVE_ID      -66             fputs(stdout,   "non existent wave id.");
            break;
        case PI_TOO_MANY_CBS     -67             fputs(stdout,   "No more CBs for waveform.");
            break;
        case PI_TOO_MANY_OOL     -68             fputs(stdout,   "No more OOL for waveform.");
            break;
        case PI_EMPTY_WAVEFORM   -69             fputs(stdout,   "attempt to create an empty waveform.");
            break;
        case PI_NO_WAVEFORM_ID   -70             fputs(stdout,   "no more waveforms.");
            break;
        case PI_I2C_OPEN_FAILED  -71             fputs(stdout,   "can't open I2C device.");
            break;
        case PI_SER_OPEN_FAILED  -72             fputs(stdout,   "can't open serial device.");
            break;
        case PI_SPI_OPEN_FAILED  -73             fputs(stdout,   "can't open SPI device.");
            break;
        case PI_BAD_I2C_BUS      -74             fputs(stdout,   "bad I2C bus.");
            break;
        case PI_BAD_I2C_ADDR     -75             fputs(stdout,   "bad I2C address.");
            break;
        case PI_BAD_SPI_CHANNEL  -76             fputs(stdout,   "bad SPI channel.");
            break;
        case PI_BAD_FLAGS        -77             fputs(stdout,   "bad i2c/spi/ser open flags.");
            break;
        case PI_BAD_SPI_SPEED    -78             fputs(stdout,   "bad SPI speed.");
            break;
        case PI_BAD_SER_DEVICE   -79             fputs(stdout,   "bad serial device name.");
            break;
        case PI_BAD_SER_SPEED    -80             fputs(stdout,   "bad serial baud rate.");
            break;
        case PI_BAD_PARAM        -81             fputs(stdout,   "bad i2c/spi/ser parameter.");
            break;
        case PI_I2C_WRITE_FAILED -82             fputs(stdout,   "i2c write failed.");
            break;
        case PI_I2C_READ_FAILED  -83             fputs(stdout,   "i2c read failed.");
            break;
        case PI_BAD_SPI_COUNT    -84             fputs(stdout,   "bad SPI count.");
            break;
        case PI_SER_WRITE_FAILED -85             fputs(stdout,   "ser write failed.");
            break;
        case PI_SER_READ_FAILED  -86             fputs(stdout,   "ser read failed.");
            break;
        case PI_SER_READ_NO_DATA -87             fputs(stdout,   "ser read no data available.");
            break;
        case PI_UNKNOWN_COMMAND  -88             fputs(stdout,   "unknown command.");
            break;
        case PI_SPI_XFER_FAILED  -89             fputs(stdout,   "spi xfer/read/write failed.");
            break;
        case PI_BAD_POINTER      -90             fputs(stdout,   "bad (NULL) pointer.");
            break;
        case PI_NO_AUX_SPI       -91             fputs(stdout,   "no auxiliary SPI on Pi A or B.");
            break;
        case PI_NOT_PWM_GPIO     -92             fputs(stdout,   "GPIO is not in use for PWM.");
            break;
        case PI_NOT_SERVO_GPIO   -93             fputs(stdout,   "GPIO is not in use for servo pulses.");
            break;
        case PI_NOT_HCLK_GPIO    -94             fputs(stdout,   "GPIO has no hardware clock.");
            break;
        case PI_NOT_HPWM_GPIO    -95             fputs(stdout,   "GPIO has no hardware PWM.");
            break;
        case PI_BAD_HPWM_FREQ    -96             fputs(stdout,   "invalid hardware PWM frequency.");
            break;
        case PI_BAD_HPWM_DUTY    -97             fputs(stdout,   "hardware PWM dutycycle not 0-1M.");
            break;
        case PI_BAD_HCLK_FREQ    -98             fputs(stdout,   "invalid hardware clock frequency.");
            break;
        case PI_BAD_HCLK_PASS    -99             fputs(stdout,   "need password to use hardware clock 1.");
            break;
        case PI_HPWM_ILLEGAL    -100             fputs(stdout,   "illegal, PWM in use for main clock.");
            break;
        case PI_BAD_DATABITS    -101             fputs(stdout,   "serial data bits not 1-32.");
            break;
        case PI_BAD_STOPBITS    -102             fputs(stdout,   "serial (half) stop bits not 2-8.");
            break;
        case PI_MSG_TOOBIG      -103             fputs(stdout,   "socket/pipe message too big.");
            break;
        case PI_BAD_MALLOC_MODE -104             fputs(stdout,   "bad memory allocation mode.");
            break;
        case PI_TOO_MANY_SEGS   -105             fputs(stdout,   "too many I2C transaction segments.");
            break;
        case PI_BAD_I2C_SEG     -106             fputs(stdout,   "an I2C transaction segment failed.");
            break;
        case PI_BAD_SMBUS_CMD   -107             fputs(stdout,   "SMBus command not supported by driver.");
            break;
        case PI_NOT_I2C_GPIO    -108             fputs(stdout,   "no bit bang I2C in progress on GPIO.");
            break;
        case PI_BAD_I2C_WLEN    -109             fputs(stdout,   "bad I2C write length.");
            break;
        case PI_BAD_I2C_RLEN    -110             fputs(stdout,   "bad I2C read length.");
            break;
        case PI_BAD_I2C_CMD     -111             fputs(stdout,   "bad I2C command.");
            break;
        case PI_BAD_I2C_BAUD    -112             fputs(stdout,   "bad I2C baud rate, not 50-500k.");
            break;
        case PI_CHAIN_LOOP_CNT  -113             fputs(stdout,   "bad chain loop count.");
            break;
        case PI_BAD_CHAIN_LOOP  -114             fputs(stdout,   "empty chain loop.");
            break;
        case PI_CHAIN_COUNTER   -115             fputs(stdout,   "too many chain counters.");
            break;
        case PI_BAD_CHAIN_CMD   -116             fputs(stdout,   "bad chain command.");
            break;
        case PI_BAD_CHAIN_DELAY -117             fputs(stdout,   "bad chain delay micros.");
            break;
        case PI_CHAIN_NESTING   -118             fputs(stdout,   "chain counters nested too deeply.");
            break;
        case PI_CHAIN_TOO_BIG   -119             fputs(stdout,   "chain is too long.");
            break;
        case PI_DEPRECATED      -120             fputs(stdout,   "deprecated function removed.");
            break;
        case PI_BAD_SER_INVERT  -121             fputs(stdout,   "bit bang serial invert not 0 or 1.");
            break;
        case PI_BAD_EDGE        -122             fputs(stdout,   "bad ISR edge value, not 0-2.");
            break;
        case PI_BAD_ISR_INIT    -123             fputs(stdout,   "bad ISR initialisation.");
            break;
        case PI_BAD_FOREVER     -124             fputs(stdout,   "loop forever must be last command.");
            break;
        case PI_BAD_FILTER      -125             fputs(stdout,   "bad filter parameter.");
            break;
        case PI_BAD_PAD         -126             fputs(stdout,   "bad pad number.");
            break;
        case PI_BAD_STRENGTH    -127             fputs(stdout,   "bad pad drive strength.");
            break;
        case PI_FIL_OPEN_FAILED -128             fputs(stdout,   "file open failed.");
            break;
        case PI_BAD_FILE_MODE   -129             fputs(stdout,   "bad file mode.");
            break;
        case PI_BAD_FILE_FLAG   -130             fputs(stdout,   "bad file flag.");
            break;
        case PI_BAD_FILE_READ   -131             fputs(stdout,   "bad file read.");
            break;
        case PI_BAD_FILE_WRITE  -132             fputs(stdout,   "bad file write.");
            break;
        case PI_FILE_NOT_ROPEN  -133             fputs(stdout,   "file not open for read.");
            break;
        case PI_FILE_NOT_WOPEN  -134             fputs(stdout,   "file not open for write.");
            break;
        case PI_BAD_FILE_SEEK   -135             fputs(stdout,   "bad file seek.");
            break;
        case PI_NO_FILE_MATCH   -136             fputs(stdout,   "no files match pattern.");
            break;
        case PI_NO_FILE_ACCESS  -137             fputs(stdout,   "no permission to access file.");
            break;
        case PI_FILE_IS_A_DIR   -138             fputs(stdout,   "file is a directory.");
            break;
        case PI_BAD_SHELL_STATUS -139            fputs(stdout,   "bad shell return status.");
            break;
        case PI_BAD_SCRIPT_NAME -140             fputs(stdout,   "bad script name.");
            break;
        case PI_BAD_SPI_BAUD    -141             fputs(stdout,   "bad SPI baud rate, not 50-500k.");
            break;
        case PI_NOT_SPI_GPIO    -142             fputs(stdout,   "no bit bang SPI in progress on GPIO.");
            break;
        case PI_BAD_EVENT_ID    -143             fputs(stdout,   "bad event id.");
            break;
        case PI_CMD_INTERRUPTED -144             fputs(stdout,   "Used by Python.");
            break;
        case PI_NOT_ON_BCM2711  -145             fputs(stdout,   "not available on BCM2711.");
            break;
        case PI_ONLY_ON_BCM2711 -146             fputs(stdout,   "only available on BCM2711.");
            break;
        default:
            break;
    }
*/
