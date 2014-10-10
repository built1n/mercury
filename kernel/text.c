#include <stddef.h>
#include "text.h"

struct text_hook hooks;

void init_text(struct text_hook hook) {
	hooks = hook;
}

void put_char(char c) {
	hooks.put_char(c);
}

void put_string(const char *s) {
	while (*s) {
		put_char(*s++);
	}
}
