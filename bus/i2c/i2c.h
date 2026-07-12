#ifndef I2C_H
#define I2C_H

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

uint8_t i2c_init(uint8_t , uint8_t * );
uint8_t i2c_read(int * , uint8_t * , ssize_t);
uint8_t i2c_write(int * , uint8_t * , ssize_t);

#endif // I2C_H