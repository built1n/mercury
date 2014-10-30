#include "arch/terminal.h"
#include "output.h"

void print_char(char c) {
	kernel_print_character(c);
}

void print_string(const char *string) {
	while (*string) {
		kernel_print_character(*string);
		string++;
	}
}
