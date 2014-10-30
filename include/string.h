#ifndef STRING_H
#define STRING_H
#include <stddef.h>

size_t strlen(const char *s);
int atoi(const char *s);
void *memset(void *s, int c, size_t n);
void *memchr(const void *s, int c, size_t n);

#endif
