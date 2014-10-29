#include <stddef.h>
#include <stdint.h>
#include "arch/terminal.h"
#include "arch/i686/vga_term.h"

size_t text_row;
size_t text_column;
uint8_t text_color;
uint16_t* vga_buffer;

uint8_t make_color(uint8_t foreground, uint8_t background) {
	return foreground | background << 4;
}

uint16_t make_vgaentry(char c, uint8_t color) {
	uint16_t c16 = c;
	uint16_t color16 = color;
	return c16 | color16 << 8;
}

void terminal_putcharat(char c, uint8_t color, size_t x, size_t y) {
	const size_t index = y * VGA_WIDTH + x;
	vga_buffer[index] = make_vgaentry(c, color);
}

void print_character(char c) {
	terminal_putcharat(c, text_color, text_column, text_row);
	text_column++;
}

void initialize_vga_terminal() {
	struct arch_terminal term = {
		&print_character
	};
	set_kernel_terminal(term);
	vga_buffer = (uint16_t*)0xB8000;
	text_row = text_column = 0;
	text_color = make_color(COLOR_LIGHT_GREY, COLOR_BLACK);
	for (size_t y = 0; y < VGA_HEIGHT; y++) {
		for (size_t x = 0; x < VGA_WIDTH; x++) {
			const size_t index = y * VGA_WIDTH + x;
			vga_buffer[index] = make_vgaentry(' ', text_color);
		}
	}
}
