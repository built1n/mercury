#include <stdint.h>
#include <stddef.h>
#include <stdbool.h>
#include "string.h"
#include "util/ansi_escape.h"

void ansi_init(struct ansi_state *state) {
	memset(state, sizeof(state), 0);
}

void handle_control_sequence(struct ansi_state *state) {
	if (state->index < 3) {
		/* Non-CSI sequences are unsupported */
		state->index = 0;
		return;
	}
	char *code = state->buffer;
	code += 2;
	while (*code) {
		int control = atoi(code);
		switch (control) {
			case 0:
				if (state->hooks.reset != NULL) {
					state->hooks.reset();
				}
				break;
			case 1:
				if (state->hooks.bold != NULL) {
					state->hooks.bold();
				}
				break;
			case 2:
				if (state->hooks.light != NULL) {
					state->hooks.light();
				}
				break;
			case 30:
			case 31:
			case 32:
			case 33:
			case 34:
			case 35:
			case 36:
			case 37:
				if (state->hooks.set_foreground_ansi != NULL) {
					state->hooks.set_foreground_ansi(control - 30);
				}
				break;
			case 40:
			case 41:
			case 42:
			case 43:
			case 44:
			case 45:
			case 46:
			case 47:
				if (state->hooks.set_background_ansi != NULL) {
					state->hooks.set_background_ansi(control - 40);
				}
				break;
		}
		while (*code && *code++ != ';');
	}
	state->index = 0;
}

bool ansi_add_character(struct ansi_state *state, char c) {
	/* TODO: This is not complete, it needs to handle */
	if (state->index == 0) {
		if (c == 0x1B /* ESC */) {
			/* Start of escape sequence */
			state->buffer[state->index++] = c;
			return true;
		}
	} else {
		state->buffer[state->index++] = c;
		if (state->index == 1) {
			if (c < 64 || c > 95) {
				/* Two-character escape sequence, unsupported */
				state->index = 0;
			}
		} else if (c == '[') {
			/* CSI */
		} else if (c >= 64 && c <= 126) {
			state->buffer[state->index] = '\0';
			handle_control_sequence(state);
		}
		return true;
	}
	return false;
}
