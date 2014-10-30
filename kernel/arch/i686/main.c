#include "main.h"
#include "output.h"
#include "util/log.h"
#include "arch/i686/gdt.h"
#include "arch/i686/vga_term.h"
#include "arch/i686/multiboot.h"

void i686_main(struct multiboot *multiboot, uint32_t multiboot_magic) {
	initialize_vga_terminal();
	kernel_log(L_INFO, "i686", "Booting Mercury kernel for i686");
	if (multiboot_magic != 0x2BADB002) {
		kernel_log(L_WARN, "i686", "Not booted from multiboot, what's going on?");
	}
	if (multiboot->flags & MULTIBOOT_FLAG_BOOTLOADER) {
		/* TODO: Update this once we've got printf */
		kernel_log(L_INFO, "i686", "Started from bootloader: ");
		print_string("\t\t");
		print_string((char *)multiboot->bootloader_name);
		print_string("\n");
	}
	if (multiboot->flags & MULTIBOOT_FLAG_CMDLINE) {
		kernel_log(L_INFO, "i686", "Got kernel command line via multiboot:");
		print_string("\t\t");
		print_string((char *)multiboot->cmdline);
		print_string("\n");
	}
	load_gdt();
	kernel_log(L_INFO, "i686", "i686 is good to go, handing control off to kernel.");
	kernel_main();
}
