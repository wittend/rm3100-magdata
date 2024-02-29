#!/usr/bin/env python3
# =========================================================================
#  check4mag.py
# 
#  A line tool to check for the presence of a PNI RM3100 3-axis magnetometer.
# 
#  Author:      David Witten, KD0EAG
#  Date:        February 23, 2024
#  License:     GPL 3.0
#  Note:        Checks for magnetometer presense by attampting to open the PNI
#               rm3100 magnetometer's bus/address and reading the 'version' 
#               register. It first trys osing the PIGPIO interface.  If 
#               this fails(pigpiod is not running) it try's other methods.
# =========================================================================
import sys
sys.path.append('.')
import os
import os.path
import pigpio
from smbus2 import SMBus

VERSION_EXPECTED = 0x22

I2C_BUS = 1
RM3100_ADDRESS = 0x20
RM3100I2C_REVID = 0x36

i2cDeviceHandle = 0

# Swap these to get numeric exit values
# GOOD = 0
# BAD  = 1
GOOD = "GOOD"
BAD  = "BAD"

def main():
    exitv = GOOD
    
    try:
        f = open("/dev/i2c-1", "r")
    except:
        print("i2cbus 1 is not present.")
        exit(BAD)
    else:
        print("i2cbus 1 IS present.")
    finally:
        f.close()
        
    pi = pigpio.pi('localhost', 8888, False)
    if not pi.connected:
        # Use smbus2 to read version register
        print("pigpiod NOT present. Using smbus2.")
        bus = SMBus(1)
        rv = bus.read_byte_data(RM3100_ADDRESS, RM3100I2C_REVID)
        if(rv == VERSION_EXPECTED):
            # version matched
            print("SMBUS2 version matched");
            bus.close()   
            evitv = GOOD
        else:
            # version didn't match
            print("SMBUS2 version didn't match")
            bus.close()   
            exitv = BAD
    else:
        print("pigpiod IS present.")
        # Then use pigpio to read-version register
        try:
            i2cDeviceHandle = pi.i2c_open(I2C_BUS, RM3100_ADDRESS)
        except (FileNotFoundError, PermissionError, OSError):
            print("i2cDeviceHandle = pi.i2c_open(I2C_BUS, RM3100_ADDRESS) failed.")
            exitv = BAD
        else:
            if(i2cDeviceHandle > -1):
                
                # turn off pigpiod exception handling
                pigpio.exceptions = False
                
                try:
                    rv = pi.i2c_read_byte_data(i2cDeviceHandle, RM3100I2C_REVID)
                #except(IOError, OSError):
                except:
                    # Read succeeded
                    print(pigpio.error_text(rv))
                    pi.i2c_close(i2cDeviceHandle)
                    exitv = BAD
                else:    
                    if(rv == VERSION_EXPECTED):
                        # version matched
                        print("rm3100 version matched");
                        pi.i2c_close(i2cDeviceHandle)
                        exitv = GOOD
                    else:
                        # version didn't match
                        print("rm3100 version didn't match or could not be read.")
                        pi.i2c_close(i2cDeviceHandle)
                        exitv = BAD
                
                # turn pigpiod exception handling back on
                pigpio.exceptions = True
                
            else:
                # Read failed
                print("rm3100 Read failed")
                exitv = BAD

    print("Exit value: ", exitv)
 

main()

