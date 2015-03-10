#include <stdio.h>
#include <stdlib.h>
#include <linux/i2c-dev.h>
#include <fcntl.h>

#define dev "/dev/i2c-1"
#define addr 0x71


void clearDisplayI2C(int file)
{
	char buf = 0x76;
	if (write(file, &buf, 4) != 4) {
		printf("Failed to write to the i2c bus.\n");
	}
}

/*
Parameters:

  * display I2C address (0x71 by default);
  * I2C bus number (/dev/i2c-<bus number>);
  * exit on error;
  * int main() -> return code;
    ** 0 --- success;
    ** != 0 --- error;
*/

void main(int argc, char *argv[]) {

	char buf[10];

	int file;
	char filename[40];
	const char *buffer;
	int i;
	char j;

	sprintf(filename, dev);
	if ((file = open(filename,O_RDWR)) < 0) {
		printf("Failed to open the bus.");
		exit(1);
	}

	if (ioctl(file,I2C_SLAVE,addr) < 0) {
		printf("Failed to acquire bus access and/or talk to slave.\n");
		exit(1);
	}

	clearDisplayI2C(file);

	for (i = 0; i < 4; i++) {
		scanf("%c", &j);
		buf[i] = j;
	}

	if (write(file, buf, 4) != 4) {
		printf("Failed to write to the i2c bus.\n");
		printf("\n\n");
	}
	close(file);
}
