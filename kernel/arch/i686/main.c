#include "main.h"
#include "output.h"
#include "arch/i686/gdt.h"
#include "arch/i686/vga_term.h"
#include "arch/i686/multiboot.h"

void i686_main(struct multiboot *multiboot, uint32_t multiboot_magic) {
	initialize_vga_terminal();
	/* TODO: Logging subsystem */
	print_string("Booting Mercury kernel from i686\n");
	if (multiboot_magic != 0x2BADB002) {
		print_string("Not booted from multiboot, what's going on?\n");
	}
	if (multiboot->flags & MULTIBOOT_FLAG_BOOTLOADER) {
		/* TODO: Update this once we've got printf */
		print_string("Thanks, ");
		print_string((char *)multiboot->bootloader_name);
		print_string(", we'll take it from here.\n");
	}
	if (multiboot->flags & MULTIBOOT_FLAG_CMDLINE) {
		print_string("Got kernel command line via multiboot:\n\t");
		print_string((char *)multiboot->cmdline);
		print_string("\n");
	}
	load_gdt();
	print_string("i686 is good to go, handing control off to kernel.\n");
	kernel_main();
	(void)(multiboot); /* Squash this, we aren't handling multiboot yet */
}
