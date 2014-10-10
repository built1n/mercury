#include <stddef.h>
#include <stdint.h>
#include <text.h>
#include "tty/vga.h"

void kernel_main() {
	init_text(terminal_initialize());
	put_string("Hello, world!\n");
}
