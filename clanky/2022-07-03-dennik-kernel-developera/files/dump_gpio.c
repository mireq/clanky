#include <errno.h>
#include <fcntl.h>
#include <linux/gpio.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/ioctl.h>
#include <unistd.h>


#define DEV_NAME "/dev/gpiochip0"
#define COUNT 1000000


int main(int argc, char *argv[]) {
	int fd, ret;
	struct gpiohandle_request rq;
	struct gpiohandle_data data;
	char buf[COUNT];
	size_t iteration = 0;

	fd = open(DEV_NAME, O_RDONLY);
	if (fd < 0) {;
		printf("Device not opened\n");
		return -1;
	}

	rq.lineoffsets[0] = 19;
	rq.lineoffsets[1] = 20;
	rq.flags = GPIOHANDLE_REQUEST_INPUT;
	rq.lines = 2;
	ret = ioctl(fd, GPIO_GET_LINEHANDLE_IOCTL, &rq);
	close(fd);
	if (ret == -1) {
		printf("Cant get handle\n");
		return -1;
	}

	for (iteration = 0; iteration < COUNT; ++iteration) {
		ret = ioctl(rq.fd, GPIOHANDLE_GET_LINE_VALUES_IOCTL, &data);
		buf[iteration] = (data.values[0]) | (data.values[1] << 1);
	}

	fd = open("/tmp/signal.dump", O_CREAT|O_WRONLY|O_TRUNC, 0666);
	if (write(fd, &buf[0], COUNT) != COUNT) {
		printf("Not all written\n");
	}

	return 0;
}
