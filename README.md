# rm3100-runMag

This is a program intended to assist in testing the PNI RM3100 geomagnetic sensor.

The rm3100 support boards were developed for use with the Personal Space Weather Station (PSWS) TangerineSDR and Grape Space Weather monitors.  These board pairs report magnetic field strength as three independent vectors, from which a total field strength may be derived.  They also report the temperature in the immediate environment of the remotely placed sensor and at the near end of the pair as a fraction of a degree C.  They may also be used standalone with only a Pi or Pi clone board.  Various pieces of software have been used to develop, test, and run these boards as part of the hardware suite or as standalone low-cost monitors of the Earth's magnetic field.

At one time or another, testers and developers of these boards have used utilities included in the Raspberry Pi OS I2Ctools package, ad hoc python scripts, and purpose-built programs written in C for their work.  All are possible.

Currently the program code most used in this project is called **runMag**. 

The utility **runMag** is a program intended to assist in testing the PNI RM3100 geomagnetic sensor.  
It is written in simple, portable C.

* The **runMag** utility is written as a Linux command line program and takes all configuration parameters from its commandline. **runMag** has some built-in documentation that displays the command line options when a user types 'runMag -h' at a command prompt. It has a feature that reports the options understood by the program when the user types 'runMag -P' + the options used.

* As long as the Pi I2C kernel driver is activated (usually by configuring I2C I/O in the raspi-setup utility), no other library dependencies are required. 
* **runMag** does not require any specialized software libraries that work only with boards created by the Raspberry Pi foundation.  
* It does not support RM3100 devices configured to require an SPI interface.  

* This software was written to be used on boards such as the Raspberry Pi 3/4, Odroid, Nvidia Nano and their kin. It has been tested, if not thoroughly, on many similar single board designs. **runMag** was written with the expectation that the host provides the defacto standard 40 pin IO bus of Raspberry Pi 3's and their clones.
* While the code may build on desktop systems, its use makes no sense unless the I2C bus is accessible.
 
* **runMag** uses Linux OS file handles to open, read, write, and close the device through the appropriate I2C bus.  
The utility was written for maximum generality and should compile on any Linux host that supplies the standard GNU C compiler and build utilities.

* **runMag** assumes that the I2C kernel drivers are installed, and that I2C bus names such as /dev/i2c-1, /dev/i2c-2, can be listed using ls. (The exact numbers vary depending on the device used).

* The software allows reading almost all of the useful registers of the RM3100.  It also reads the MCP9808 (or equivalent) precision temperature sensors on both the local and remote components of the support board pair.

* **runMag** concatenates each collected sample of data to a log file as an individual JSON object at 1s intervals. The software writes a log file to a specified location on the host system for collection and transfer to a data aggregation system. If no output file is configured, the output is written to the 'stdout', ordinarily the system console. **runMag** observes the current host's clock time and closes each day's log at 00:00:00 UTC and open's a new one for the next UTC day.


The current pre-release code is 0.1.2

Just clone this project into your home directory on the Raspberry Pi or board with similar bus using:

    git clone https://github.com/wittend/rm3100-runMag.git

Then do:

    $ cd rm3100-runMag
    $ make


and if all goes well type:

    $ sudo ./runMag
    (most flavors of Linux will require sudo)


and now you should see some results!

## Example on Raspberry Pi 3/4, using logging:

This creates a logfile in the directory ./logs with the format 'kd0eag-20200624-runmag.log'.
Here 'kd0eag' is used as a site ID and '20200624' is the UTC 'YYYYMMDD' format of date.
This file will be closed at the end of the current UTC day and a new one opened named with the new day number.
Logging will continue to the new file uninterrupted.

    dave@raspi-3: ~/projects/rm3100-runMag $ ./runMag -kPS kd0eag



## Example on Odroid N2, output JSON, show totalized magnetic field.

    dave@odroid:~/$ sudo ./runMag -j -Z -b 2

    { ts:"03 May 2020 23:56:55",  lt:"24.62", x:"14" , y:"-11" , z:"49", rx:"1109", ry:"-844", rz:"3707", Tm: "52" }
    { ts:"03 May 2020 23:56:59",  lt:"24.62", x:"14" , y:"-11" , z:"49", rx:"1111", ry:"-865", rz:"3712", Tm: "52" }
    { ts:"03 May 2020 23:57:03",  lt:"24.62", x:"14" , y:"-11" , z:"49", rx:"1105", ry:"-862", rz:"3706", Tm: "52" }
    ...

    Tm : (sqrt((x*x) + (y*y) + (z*z)))


## Example output using -h or -? option:

    david@marmoset:~/Projects/git/rm3100-runMag$ ./runMag -h

    ./runMag Version = 0.1.0

    Parameters:

       -a                     :  List known SBC I2C bus numbers.       [ use with -b ]
       -A                     :  Set NOS (0x0A) register value.        [ Don't use unless you know what you are doing ]
       -B <reg mask>          :  Do built in self test (BIST).         [ Not implemented ]
       -b <bus as integer>    :  I2C bus number as integer.
       -C                     :  Read back cycle count registers before sampling.
       -c <count>             :  Set cycle counts as integer.          [ default 200 decimal]
       -D <rate>              :  Set magnetometer sample rate.         [ TMRC reg 96 hex default ].
       -E                     :  Show cycle count/gain/sensitivity relationship.
       -f <filename>          :  Read configuration from file (JSON).  [ Not implemented ]
       -F <filename>          :  Write configuration to file (JSON).   [ Not implemented ]
       -g <mode>              :  Device sampling mode.                 [ POLL=0 (default), CONTINUOUS=1 ]
       -H                     :  Hide raw measurments.
       -j                     :  Format output as JSON.
       -k                     :  Create and roll log files.            [ 00:00 UTC default ]
       -L <addr as integer>   :  Local temperature address.            [ default 19 hex ]
       -l                     :  Read local temperature only.
       -M <addr as integer>   :  Magnetometer address.                 [ default 20 hex ]
       -m                     :  Read magnetometer only.
       -O <filename>          :  Output file path.                     [ Must be valid path with write permissions ]
       -P                     :  Show Parameters.
       -q                     :  Quiet mode.                           [ partial ]
       -v                     :  Verbose output.
       -R <addr as integer>   :  Remote temperature address.           [ default 18 hex ]
       -r                     :  Read remote temperature only.
       -s                     :  Return single reading.                [ Do one measurement loop only ]
       -S                     :  Site prefix string for log files.     [ 32 char max. Do not use /'"* etc. Try callsign! ]
       -T                     :  Raw timestamp in milliseconds.        [ default: UTC string ]
       -V                     :  Display software version and exit.
       -Z                     :  Show total field.                     [ sqrt((x*x) + (y*y) + (z*z)) ]
       -h or -?               :  Display this help.


## Example output using the -E option:

    dave@odroid:~/projects/rm3100-runMag$ sudo ./runMag -E
        -----------------------------------------------------------------------
        |    Cycle Count/Gain/Sensitivity        |     RM3100 Measurement     |
        |---------------------------------------------------------------------|
        | Cycle |   Gain   |                     |                            |
        | Count | (LSB/uT) | Sensitivity(nT/LSB) | in count | microTesla (uT) |
        |---------------------------------------------------------------------|
        |   50  |    20    |      50.000         |   3000   |     150.000     |
        |  100  |    38    |      26.316         |   3000   |      78.947     |
        |  200  |    75    |      13.333         |   3000   |      40.000     |
        |  300  |   113    |       8.850         |   3000   |      26.549     |
        |  400  |   150    |       6.667         |   3000   |      20.000     |
        -----------------------------------------------------------------------
    From: RM3100_FAQ_R02.pdf


## Example output using the -P option:

    dave@raspi-3:~/projects/rm3100-runMag $ ./runMag -Psl

        Version = 0.0.7

        Current Parameters:

            Magnetometer revision ID detected:          34 (dec)
            Log output path:                            TRUE
            Log output:                                 TRUE
            Log site prefix string:                     kd0eag
            Output file path:                           ./logs/kd0eag-20200624-runmag.log
            I2C bus number as integer:                  1 (dec)
            I2C bus path as string:                     /dev/i2c-1
            Built in self test (BIST) value:            00 (hex)
            NOS Register value:                         00 (hex)
            Device sampling mode:                       POLL
            Cycle counts by vector:                     X: 200 (dec), Y: 200 (dec), Z: 200 (dec)
            Gain by vector:                             X:  75 (dec), Y:  75 (dec), Z:  75 (dec)
            Read back CC Regs after set:                FALSE
            Software Loop Delay (uSec):                 1000000 (dec)
            Magnetometer sample rate:                   200 (dec)
            CMM magnetometer sample rate (TMRC reg):    150 (dec)
            Format output as JSON:                      TRUE
            Read local temperature only:                TRUE
            Read remote temperature only:               FALSE
            Read magnetometer only:                     FALSE
            Local temperature address:                  18 (hex)
            Remote temperature address:                 19 (hex)
            Magnetometer address:                       20 {hex)
            Show parameters:                            TRUE
            Quiet mode:                                 TRUE
            Hide raw measurements:                      FALSE
            Return single magnetometer reading:         FALSE
            Read Simple Magnetometer Board (SMSB):      TRUE
            Read Board with Extender (MSBx):            FALSE
            Magnetometer configuation:                  Local standalone
            Timestamp format:                           UTCSTRING
            Verbose output:                             FALSE
            Show total field:                           FALSE


     Time: 12 Jun 2020 04:29:12, lTemp: 23.88, x: -8.160, y: 6.573, z: 54.813, rx: -612, ry: 493, rz: 4111
