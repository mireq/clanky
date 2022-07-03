#include <fcntl.h>
#include <gpiod.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#define COUNT 1000000

const char *NAME = "logger";


int main(int argc, char *argv[])
{
	struct gpiod_chip *chip;
	struct gpiod_line_bulk lines;

	int dump_file;
	unsigned int offsets[2] = {19, 20};
	unsigned int values[2];
	size_t iteration = 0;
	char buf[COUNT];
	int ret;

	dump_file = open("/tmp/signal.dump", O_CREAT|O_WRONLY|O_TRUNC, 0666);
	if (dump_file < 0) {
		printf("Cant dump\n");
		return -1;
	}

	chip = gpiod_chip_open("/dev/gpiochip0");
	if (!chip) {
		printf("GPIO not opened\n");
		return -1;
	}

	ret = gpiod_chip_get_lines(chip, &offsets[0], 2, &lines);
	if (ret < 0) {
		printf("Lines not opened\n");
		return -1;
	}

	gpiod_line_request_input(lines.lines[0], NAME);
	gpiod_line_request_input(lines.lines[1], NAME);
	gpiod_line_set_flags(lines.lines[0], GPIOD_LINE_REQUEST_FLAG_ACTIVE_LOW | GPIOD_LINE_REQUEST_FLAG_OPEN_DRAIN);
	gpiod_line_set_flags(lines.lines[1], GPIOD_LINE_REQUEST_FLAG_ACTIVE_LOW | GPIOD_LINE_REQUEST_FLAG_OPEN_DRAIN);

	while (true) {
		ret = gpiod_line_get_value_bulk(&lines, values);
		//values[0] = gpiod_line_get_value(lines.lines[0]);
		//values[1] = gpiod_line_get_value(lines.lines[1]);
		if (ret < 0) {
			printf("Failed to get values\n");
			return -1;
		}

		buf[iteration] = (values[0]) | (values[1]) << 1;
		iteration++;
		if (iteration == COUNT) {
			break;
		}
	}

	if (write(dump_file, &buf[0], COUNT) != COUNT) {
		printf("Not all written\n");
	}

	return 0;
}
