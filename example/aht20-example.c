#include "../drivers/aht20-driver.h"

int main() 
{
        uint8_t *fd;
        if(i2c_init(AHT20_INIT_ADDRESS, fd) < 0) {
                return -1;
        }

        if(aht20_init(fd);

        double temp;
        uint8_t hum;

        if(aht20_get_temperature(fd, &temp)<1) {
                return -1;
        }
        if(aht20_get_humidity(fd, &hum)<1) {
                return -1;
        }

        struct measures_t m = aht20_get_temperature_humidity(fd);
        return 0;
}