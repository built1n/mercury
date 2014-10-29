/* Provides access to the arch-specific (and possibly enviornment-specific) terminal. */
#include "arch/terminal.h"

struct arch_terminal kernel_terminal;

void set_kernel_terminal(struct arch_terminal terminal) {
	kernel_terminal = terminal;
}

void kernel_print_character(char c) {
	kernel_terminal.print_character(c);
}
