#include <stdint.h>
#include <stddef.h>
#include "string.h"

size_t strlen(const char *s) {
	size_t len = 0;
	while (*s++) {
		len++;
	}
	return len;
}

int atoi(const char *s) {
	const char *digits = "0123456789";
	const char *x;
	int a = 0;
	char sign = '+';
	while (*s == ' ') ++s;

	if (*s == '+') {
		++s;
	} else if (*s == '-') {
		sign = *s;
	}

	while ((x = memchr(digits, *(s++), 10)) != NULL) {
		a = a * 10 + (x - digits);
	}

	return (sign == '+') ? a : -a;
}

void *memchr(const void *s, int c, size_t n) {
	const unsigned char *p  = (const unsigned char *)s;
	while (n--) {
		if (*p == (unsigned char)c) {
			return (void *)p;
		}
		++p;
	}
	return NULL;
}

void *memset(void *s, int c, size_t n) {
	unsigned char *p = (unsigned char*)s;
	while (n--) {
		*p++ = (unsigned char)c;
	}
	return s;
}
