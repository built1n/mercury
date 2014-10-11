#include <stddef.h>
#include <stdint.h>
#include <text.h>
#include <gdt.h>
#include <tty/vga.h>

void kernel_main() {
	load_gdt();

	init_text(terminal_initialize());
	put_string("Hello, world!\n");
}
