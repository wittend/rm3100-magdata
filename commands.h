//=========================================================================
// commands.h
// 
// An interface for the RM3100 3-axis magnetometer from PNI Sensor Corp.
// 
// Author:      David Witten, KD0EAG
// Date:        December 18, 2023
// License:     GPL 3.0
// Note:        
//              
//              
//=========================================================================
#ifndef SWXCOMMANDS_h
#define SWXCOMMANDS_h

#include "main.h"

#define USE_PIGPIO      0
#define USE_PIGPIO_IF2  1
#define USE_I2CFILES    0

#if(USE_I2CFILES)

#endif // USE_I2CFILES

#if(USE_PIGPIO)

#include <pigpio.h>

#endif // USE_PIGPIO

#if(USE_PIGPIO_IF2)

#include <pigpiod_if2.h>

int  init_IO();
void terminate_IO(volatile ctlList *p);
void verifySensor(volatile ctlList *p);
int  readSensor(volatile ctlList *ctl);
char *formatOutput(volatile ctlList *, char *outBuf);
int  waitForRequest(volatile ctlList *);

#endif // USE_PIGPIO_IF2


#endif //SWXCOMMANDS_h            

