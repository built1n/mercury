#include "main.h"
#include "arch/i686/gdt.h"
#include "arch/i686/vga_term.h"

void i686_main() {
	load_gdt();
	initialize_vga_terminal();
	kernel_main();
}
