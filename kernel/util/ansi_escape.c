#include <stdint.h>
#include <stddef.h>
#include <stdbool.h>
#include "output.h"
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
	int control = atoi(state->buffer + 2);
	if (control >= 30 && control <= 37) {
		if (state->hooks.set_foreground_ansi != NULL) {
			state->hooks.set_foreground_ansi(control - 30);
		}
	} else if (control >= 40 && control <= 47) {
		if (state->hooks.set_background_ansi != NULL) {
			state->hooks.set_background_ansi(control - 40);
		}
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
			handle_control_sequence(state);
		}
		return true;
	}
	return false;
}
