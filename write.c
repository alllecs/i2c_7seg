#include <errno.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <linux/i2c-dev.h>
#include <sys/ioctl.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

void main(void) {
    int file;
    char filename[40];
    const char *buffer;
    int addr = 0b01110001;        // The I2C address of the ADC
	char buf[10];

    sprintf(filename,"/dev/i2c-1");
    if ((file = open(filename,O_RDWR)) < 0) {
       printf("Failed to open the bus.");
        /* ERROR HANDLING; you can check errno to see what went wrong */
  }

    if (ioctl(file,I2C_SLAVE,addr) < 0) {
        printf("Failed to acquire bus access and/or talk to slave.\n");
        /* ERROR HANDLING; you can check errno to see what went wrong */
    }

    //buf[0] = 0b01110001;
//    buf[0] = 0b01110001;

    buf[0] = 'A';
    buf[1] = 'b';
    buf[2] = 'C';
    buf[3] = '0';


    if (write(file, buf, 4) != 1) {
        /* ERROR HANDLING: i2c transaction failed */
        printf("Failed to write to the i2c bus.\n");
        buffer = strerror(errno);
        printf(buffer);
        printf("\n\n");
    }

    // close?
}
