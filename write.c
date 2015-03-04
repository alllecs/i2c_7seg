#include <stdio.h>
#include <stdlib.h>
#include <linux/i2c-dev.h>
#include <fcntl.h>

void clearDisplayI2C(int file)
{
	char buf[10];
	buf[0] = 0x76;
	write(file, buf, 1); 
}

void main(void) {
	int file;
	char filename[40];
	const char *buffer;
	int addr = 0x71;
	int i;
	char buf[10];
	char j;

	sprintf(filename,"/dev/i2c-1");
	if ((file = open(filename,O_RDWR)) < 0) {
		printf("Failed to open the bus.");
	}

	if (ioctl(file,I2C_SLAVE,addr) < 0) {
		printf("Failed to acquire bus access and/or talk to slave.\n");
	}

	clearDisplayI2C(file);

	for (i = 0; i < 4; i++) {
		scanf("%c", &j);
		buf[i] = j;
	}

		write(file, buf, 4);
/*
	buf[0] = 'A';
	buf[1] = 'B';
	buf[2] = 'C';
	buf[3] = '0';	
		
	if (write(file, buf, 4) != 4) {
		printf("Failed to write to the i2c bus.\n");
		buffer = strerror(errno);
		printf(buffer);
		printf("\n\n");
	}
*/
	close(file);
}

