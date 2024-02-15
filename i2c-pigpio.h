//=========================================================================
// i2c-pigpio.h
//
// An interface for the RM3100 3-axis magnetometer from PNI Sensor Corp.
// 
// Author:      David Witten, KD0EAG
// Date:        December 18, 2023
// License:     GPL 3.0
// Note:        replaces i2c.c (using file system calls to read(), write(), etc.
//              with calls to pigpio. 
//              Also adding callbacks on GPIO27 for PPS rising edge.
//=========================================================================
#ifndef PNIRM3100_I2C_H
#define PNIRM3100_I2C_H

#include <pigpiod_if2.h>
#include "main.h"

//------------------------------------------
// Prototypes
//------------------------------------------
// int i2c_open(pList *p);
// void i2c_close(int fd);
void i2c_setAddress(int fd, int devAddr);
void i2c_setBitRate(int fd, int devspeed);
int i2c_write(int fd, uint8_t reg, uint8_t value);
uint8_t i2c_read(int fd, uint8_t reg);
int i2c_writebuf(int fd, uint8_t reg, char* buffer, short int length);
int i2c_readbuf(int fd, uint8_t reg, uint8_t* buf, short int length);

#endif //PNIRM3100_I2C_H
