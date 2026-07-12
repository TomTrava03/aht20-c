#ifndef AHT20_DRIVER_H
#define AHT20_DRIVER_H

#include <stdint.h>
#include <stddef.h>

#include "i2c.h"

// ADDRESSES
#define AHT20_I2C_ADDRESS 0x38
#define AHT20_INIT_ADDRESS 0xBE, 0x08, 0x00
#define AHT20_MEASURE_ADDRESS 0x00, 0xFE

#define AHT20_MESSAGE_LEN 7

struct {
        uint32_t my_20_bit_value : 20;
} _uint20_t;

/**
 * @brief      send INITIALIZE command to ATH20 sensor
 * @param[in]  *file descriptor for I2C bus 
 * @return     none
 * @note       none
 */
uint8_t aht20_init(uint8_t * );

uint8_t aht20_close(uint8_t * );

typedef struct {
        double temperature;
        int humidity;
} measures_t;
/**
 * @brief      read bytes
 * @param[in]  *file descriptor for I2C bus
 * @param[out] *data pointer to ATH20 
 * @return     status code
 *             - 0 success
 *             - 1 read failed
 * @note       none
 */
uint8_t aht20_trigger_measurements(int * , struct measures_t * );

#define AHT20_CRC8_POLY 0x31   // x^8 + x^5 + x^4 + 1
#define AHT20_CRC8_INIT 0x00

uint8_t aht20_calcultate_crc8(const uint8_t payload[7]); 




#endif // AHT20_DRIVER