CC      = gcc
CFLAGS  = -Wall -Wextra -Ibus/i2c -Idrivers
SRC     = drivers/aht_driver.c bus/i2c/i2c.c example/aht20-example.c
OUT     = build/example

$(OUT): $(SRC)
	mkdir -p build
	$(CC) $(CFLAGS) $(SRC) -o $(OUT)

clean:
	rm -rf build