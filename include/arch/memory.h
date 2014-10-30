#ifndef ARCH_MEMORY_H
#define ARCH_MEMORY_H
#include <stddef.h>

void kernel_memory_init();
void kernel_add_memory_bucket(void *start, size_t length);

#endif
