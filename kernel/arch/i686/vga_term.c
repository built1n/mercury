#include <stddef.h>
#include <stdint.h>
#include "arch/terminal.h"
#include "arch/i686/vga_term.h"
#include "util/ansi_escape.h"

#define DEFAULT_BG COLOR_BLACK
#define DEFAULT_FG COLOR_LIGHT_GREY
size_t text_row;
size_t text_column;
uint8_t text_color;
uint16_t* vga_buffer;
struct ansi_state ansi;
uint8_t light_modifier;

const uint8_t ansi_to_vga[] = {
	COLOR_BLACK, COLOR_RED, COLOR_GREEN,
	COLOR_BROWN /* (yellow) */, COLOR_BLUE,
	COLOR_MAGENTA, COLOR_CYAN, COLOR_WHITE,
	/* light colors */
	COLOR_DARK_GREY, COLOR_LIGHT_RED, COLOR_LIGHT_GREEN,
	COLOR_LIGHT_BROWN /* (yellow) */, COLOR_LIGHT_BLUE,
	COLOR_LIGHT_MAGENTA, COLOR_LIGHT_CYAN, COLOR_LIGHT_GREY,
};

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

void ansi_reset() {
	light_modifier = 0;
	text_color = make_color(DEFAULT_FG, DEFAULT_BG);
}

void ansi_bold() {
	light_modifier = 8;
}

void ansi_light() {
	light_modifier = 0;
}

void ansi_set_foreground_ansi(uint8_t foreground) {
	if (foreground > sizeof(ansi_to_vga)) {
		return;
	}
	foreground = ansi_to_vga[foreground + light_modifier];
	text_color = make_color(foreground, text_color >> 4);
}

void ansi_set_background_ansi(uint8_t background) {
	if (background > sizeof(ansi_to_vga)) {
		return;
	}
	background = ansi_to_vga[background + light_modifier];
	text_color = make_color(text_color & 0xF, background << 4);
}

void scroll_one() {
	size_t x, y;
	for (y = 1; y < VGA_HEIGHT; ++y) {
		for (x = 0; x < VGA_WIDTH; ++x) {
			vga_buffer[((y - 1) * VGA_WIDTH) + x] =
				vga_buffer[(y * VGA_WIDTH) + x];
		}
	}
	/* Clear lower row */
	for (x = 0; x < VGA_WIDTH; ++x) {
		vga_buffer[((VGA_HEIGHT - 1) * VGA_WIDTH) + x] =
			make_vgaentry(' ', text_color);
	}
}

void print_control(char c) {
	switch (c) {
		case '\n':
			text_column = 0;
			text_row++;
			if (text_row >= VGA_HEIGHT) {
				scroll_one();
				text_row--;
			}
			break;
		case '\r':
			text_column = 0;
			break;
		case '\t':
			text_column += 8;
			if (text_column >= VGA_WIDTH) {
				print_control('\n');
			}
			break;
	}
}

void print_character(char c) {
	if (!ansi_add_character(&ansi, c)) {
		if (c < ' ') {
			print_control(c);
		} else {
			terminal_putcharat(c, text_color, text_column, text_row);
			text_column++;
			if (text_column >= VGA_WIDTH) {
				print_control('\n');
			}
		}
	}
}

void initialize_vga_terminal() {
	struct arch_terminal term = {
		&print_character
	};
	set_kernel_terminal(term);
	ansi_init(&ansi);
	ansi.hooks.set_foreground_ansi = ansi_set_foreground_ansi;
	ansi.hooks.set_background_ansi = ansi_set_background_ansi;
	ansi.hooks.reset = ansi_reset;
	ansi.hooks.bold = ansi_bold;
	ansi.hooks.light = ansi_light;
	vga_buffer = (uint16_t*)0xB8000;
	text_row = text_column = 0;
	ansi_reset();
	for (size_t y = 0; y < VGA_HEIGHT; y++) {
		for (size_t x = 0; x < VGA_WIDTH; x++) {
			const size_t index = y * VGA_WIDTH + x;
			vga_buffer[index] = make_vgaentry(' ', text_color);
		}
	}
}
