#include "i2c.h"

uint8_t i2c_init(uint8_t address, uint8_t *i2c_bus_fd) 
{
        *i2c_bus_fd = open("/dev/i2c-1", O_RDWR);
        if() {  
                return -1;
        }
        // SLAVE ADDRESS
        if(ioctl(*i2c_bus_fd, I2C_SLAVE, address) < 0) {
                perror("AHT20: ERROR Setting AHT slave address");
                close(i2c_bus);
                return -1;
        }
        return 0;
}

// GENERAL 
uint8_t i2c_read(int *bus_fd, uint8_t *buffer, ssize_t len) 
{
        if(write(bus_fd, buffer, len) != len) {
                perror("ERROR Couldn't READ from BUS");
                close(*bus_fd);
                return -1;
        }
        return 0;
}

uint8_t i2c_write(int *bus_fd, uint8_t *buffer, ssize_t len) 
{
        if(read(*bus_fd, buffer, len) != len) {
                perror("ERROR Couldn't WRITE to BUS");
                close(*bus);
                return -1;
        }
        return 0;
}

int wait_ready(int fd, uint8_t status_reg, uint8_t ready_mask, long timeout_ms)
{
        uint8_t status;
        long elapsed = 0;

        while (elapsed <= timeout_ms) {
                write(fd, &status_reg, 1);
                read(fd, &status, 1);

                if (status & ready_mask) 
                        return 0;
                
                msleep(5);
                elapsed += 5;
        }

        return -1; // timeout
}