#include <stddef.h>
#include <stdint.h>
#include <strings.h>
#include <text.h>
#include "tty/vga.h"

size_t terminal_row;
size_t terminal_column;
uint8_t terminal_color;
uint16_t* terminal_buffer;

uint8_t make_color(enum vga_color fg, enum vga_color bg) {
	return fg | bg << 4;
}

uint16_t make_vgaentry(char c, uint8_t color) {
	uint16_t c16 = c;
	uint16_t color16 = color;
	return c16 | color16 << 8;
}
 
void terminal_putentryat(char c, uint8_t color, size_t x, size_t y) {
	const size_t index = y * VGA_WIDTH + x;
	terminal_buffer[index] = make_vgaentry(c, color);
}

void scroll_one() {
	/* TODO: memmove */
	for (size_t y = 1; y < VGA_HEIGHT; y++) {
		for (size_t x = 0; x < VGA_WIDTH; x++) {
			const size_t from = y * VGA_WIDTH + x;
			const size_t to = (y - 1) * VGA_WIDTH + x;
			terminal_buffer[to] = terminal_buffer[from];
			terminal_buffer[from] = make_vgaentry(' ', terminal_color);
		}
	}
}

void terminal_put_special(char c) {
	switch (c) {
	case '\n':
		terminal_column = 0;
		if (++terminal_row == VGA_HEIGHT) {
			terminal_row--;
			scroll_one();
		}
		break;
	case '\r':
		terminal_column = 0;
		break;
	}
}
 
void terminal_putchar(char c) {
	if (c < ' ') {
		terminal_put_special(c);
		return;
	}
	terminal_putentryat(c, terminal_color, terminal_column, terminal_row);
	if (++terminal_column == VGA_WIDTH) {
		terminal_column = 0;
		if (++terminal_row == VGA_HEIGHT) {
			terminal_row--;
			scroll_one();
		}
	}
}

struct text_hook terminal_initialize() {
	terminal_row = 0;
	terminal_column = 0;
	terminal_color = make_color(COLOR_LIGHT_GREY, COLOR_BLACK);
	terminal_buffer = (uint16_t*)0xB8000;
	for (size_t y = 0; y < VGA_HEIGHT; y++) {
		for (size_t x = 0; x < VGA_WIDTH; x++) {
			const size_t index = y * VGA_WIDTH + x;
			terminal_buffer[index] = make_vgaentry(' ', terminal_color);
		}
	}
	struct text_hook hooks = { terminal_putchar };
	return hooks;
}
