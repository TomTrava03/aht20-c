#include <stdio.h>
#include <stdlib.h>

#include "aht20_driver.h"

void aht20_init(int *i2c_bus_fd) 
{
        uint8_t buffer[] = { AHT20_INIT_ADDRESS };
        i2c_write(i2c_bus, buffer, 3);
}

void aht_calculate_crc8(const uint8_t *data, size_t len) 
{
        uint8_t crc = ATH20_CRC8_INIT;
        for (size_t i = 0; i < len; i++) {
                crc ^= data[i];
                for (int bit = 0; bit < 8; bit++) {
                        if (crc & 0x80)
                                crc = (crc << 1) ^ ATH20_CRC8_POLY;
                        else
                                crc <<= 1;
                }
        }
        return crc; 
}

void check_payload(const uint8_t payload[7])
{
        uint8_t computed = aht_calculate_crc8(payload, 6);   
        return computed == payload[6]; 
}

void aht20_trigger_measurement(int *i2c_bus_fd, uint8_t *buffer) {

        // WRITE
        uint8_t buffer[] = {0x00, 0xFE};
        write_to_bus(i2c_bus_fd, buffer, 2);
        while() {
                // LOOP WHITE 
        }
        read_from_bus(i2c_bus_fd, buffer);
        check_payload(buffer);
}

// INTERFACES
double get_temperature(int *i2c_bus_fd, int unit) {
        aht20_trigger_measurement();

        double temperature = ((s_temperature / pow(2, 20)) * 200) - 50;
        if(unit == 1) { // KELVIN
                temperature += 273.15d;
        } else if(unit == 2) { // FAHRENHEIT
                temperature = (temperature * 9 / 5) + 32;
        } else {
                printf("Using DEFAULT behaviour (CELSIUS)");
        }
        return temperature;
}

int get_humidity(int *i2c_bus_fd) {
        aht20_trigger_measurement();

        int humidity = round((s_humidity/pow(2, 20)) * 100);
        return humidity;     
}


