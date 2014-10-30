#include "util/log.h"
#include "io.h"
#include "string.h"
#include <stdint.h>
#include <stddef.h>

void set_color_from(const char *from) {
	uint8_t v = 0;
	int bright = 0;
	while (*from) {
		v += *from;
		v %= 5;
		bright += *from;
		bright %= 2;
		++from;
	}
	print_string("\x1B[");
	print_char('0' + bright);
	print_string(";3");
	print_char('1' + v);
	print_char('m');
}

void kernel_log(LOG_SEVERITY_T severity, const char *from, const char *message) {
	/* TODO: Let users customize log level */
	/* TODO: printf */
	if (severity >= L_INFO) {
		int spaces = 8 - strlen(from);
		if (spaces < 1) spaces = 1;

		print_char('[');
		set_color_from(from);
		print_string(from);
		print_string("\x1B[0m]");
		while (spaces--) print_char(' ');
		print_string(message);
		print_char('\n');
	}
}
