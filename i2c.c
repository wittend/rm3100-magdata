//=========================================================================
// i2c.c
//
// An interface for the RM3100 3-axis magnetometer from PNI Sensor Corp.
// Derived in part from several sources:
//      https://github.com/miguelrasteiro/RM3100.X
//      Jeremiah Mattison / Rm3100: https://os.mbed.com/users/fwrawx/code/Rm3100/
//      https://github.com/shannon-jia/rm3100
//      Song Qiang <songqiang1304521@gmail.com (Linux driver):
//          Linux kernel driver: https://github.com/torvalds/linux/tree/v5.3/drivers/iio/magnetometer
// 
// Author:      David Witten, KD0EAG
// Date:        April 21, 2020
// License:     GPL 3.0
//=========================================================================
#include <linux/i2c.h>
#include <linux/i2c-dev.h>
#include "device_defs.h"
#include "i2c.h"
#include "main.h"

//------------------------------------------
// i2c_setAddress()
//
// set the I2C slave address for all
// subsequent I2C device transfers.
//------------------------------------------
void i2c_setAddress(int fd, int devAddr)
{
    if (ioctl(fd, I2C_SLAVE, devAddr) < 0)
    {
        perror("i2c_SetAddress");
        exit(1);
    }
}

//
//No obvious API call available
////------------------------------------------
//// i2c_setBitRate()
////
//// set the I2C bus address for all
//// subsequent I2C device transfers.
////------------------------------------------
//void i2c_setBitRate(int fd, int devspeed)
//{
//    if(ioctl(fd, I2C_SET_SPEED, devspeed) < 0)
//    {
//        perror("i2c_setBitRate");
//        exit(1);
//    }
//}

//------------------------------------------
// write an 8 bit value to a device register.
//------------------------------------------
int i2c_write(int fd, uint8_t reg, uint8_t value)
{
    static uint8_t data[2];
    data[0] = reg;
    data[1] = value & 0xff;
    int rv = 0;

    if(write(fd, data, 2) != 2)
    {
        perror("i2c_write()");
    }
    return rv;
}

//------------------------------------------
// i2c_writebuf()
// write a buffer of values to the device
//------------------------------------------
int i2c_writebuf(int fd, uint8_t reg, char *buffer, short int length)
{
    static uint8_t data[2];
    data[0] = reg;
    int rv = 0;

    if((rv = write(fd, data, 2)) != 2)
    {
        perror("i2c_writebuf(): write()");
    }
    if((rv = write(fd, buffer, length)) != length)
    {
        perror("i2c_writebuf(): write(data)");
        exit(1);
    }
    return rv;
}

//------------------------------------------
// read an 8 bit value from a register.
//------------------------------------------
uint8_t i2c_read(int fd, uint8_t reg)
{
    static uint8_t data[2];
    data[0] = reg;
    int rv = 0;

    if((rv = write(fd, data, 1)) != 1)
    {
        perror("i2c_writebuf(): write()");
    }
    if(read(fd, data + 1, 1) != 1)
    {
        perror("i2c_read read value.");
    }
    return data[1];
}

//------------------------------------------
// i2c_readbuf()
// write a buffer to the device
//------------------------------------------
int i2c_readbuf(int fd, uint8_t reg, uint8_t* buf, short int length)
{
    int bytes_read;
    static uint8_t data[2];
    data[0] = reg;
    int rv = 0;

    if((rv = write(fd, data, 1)) != 1)
    {
        perror("i2c_readbuf(): write()");
    }
    if((bytes_read = read(fd, buf, length)) != length)
    {
        perror("i2c transaction i2c_readbuf() failed.\n");
    }
    return bytes_read;
}

///**
// * @fn SensorStatus mag_enable_interrupts();
// *
// * @brief Enables the interrupt request from the sensor.
// *
// * @returns Status of the sensor. Not supported in AKM8975
// */
//SensorStatus mag_enable_interrupts()
//{
//    static char data[] = { RM3100_ENABLED };
//
//    if (mSensorMode == SensorPowerModeActive) 
//    {
//        rm3100_i2c_write(RM3100_BEACON_REG, data, sizeof(data)/sizeof(char));
//    }
//    return SensorOK;
//}
//
///**
// * @fn SensorStatus mag_disable_interrupts();
// *
// * @brief Disables the interrupt request from the sensor.
// *
// * @returns Status of the sensor.
// */
//SensorStatus mag_disable_interrupts()
//{
//    static char data[] = { RM3100_DISABLED };
//    rm3100_i2c_write(RM3100_BEACON_REG, data, sizeof(data)/sizeof(char));
//    return SensorOK;
//}
//

///**
// * @fn unsigned short int mag_set_sample_rate(unsigned short int sample_rate);
// *
// * @brief Requests the hardware to perform sample conversions at the specified rate.
// *
// * @param sample_rate The requested sample rate of the sensor in Hz.
// *
// * @returns The actual sample rate of the sensor.
// */
