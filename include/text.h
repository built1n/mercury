#ifndef _TEXT_H
#define _TEXT_H
#include <stddef.h>

struct text_hook {
	void (*put_char)(char c);
};

void init_text(struct text_hook hook);
void put_char(char c);
void put_string(const char *c);

#endif
