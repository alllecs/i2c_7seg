#include <stdio.h>
#include <stdlib.h>
#include <linux/i2c-dev.h>
#include <fcntl.h>

/*
Parameters:

  * display I2C address (0x71 by default);
  * I2C bus number (/dev/i2c-<bus number>);
*/

#define DEV "/dev/i2c-1"
#define ADDR 0x71


/* print out only one symbol (character).
   Use <file> as file number for write()
*/


void i2c_display_putc(int file, char symbol)
{
	if (write(file, &symbol, 1) != 1) {
		printf("Failed to write to the i2c bus.\n");
	}
}

void i2c_display_clear(int file)
{
	char buf = 0x76;
	if (write(file, &buf, 1) != 1) {
		printf("Failed to write to the i2c bus.\n");
	}
}

/*
  * exit on error;
  * int main() -> return code;
    ** 0 --- success;
    ** != 0 --- error;
*/
void main(int argc, char *argv[])
{

	char buf[10];

	int file;
	char filename[40];
	const char *buffer;
	int i;
	char j = 0;

	if (argc != 5) {
		printf("Filed enter numbers.\n");
		exit(1);
	}

	sprintf(filename, DEV);
	if ((file = open(filename,O_RDWR)) < 0) {
		printf("Failed to open the bus.");
		exit(1);
	}

	if (ioctl(file,I2C_SLAVE, ADDR) < 0) {
		printf("Failed to acquire bus access and/or talk to slave.\n");
		exit(1);
	}

	i2c_display_clear(file);

	for (i = 0; i < 4; i++) {
		sscanf(argv[i+1], "%c", &j);
		i2c_display_putc(file, j);
	}	

	close(file);

}
