CROSS_COMPILE=/home/alecs/virt2real-sdk/fs/output/host/usr/bin/arm-none-linux-gnueabi-

CC=$(CROSS_COMPILE)gcc

write: write.c
	$(CC) -o $@ $^

clean: 
	$(RM) write
