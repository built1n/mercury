#include "strings.h"

size_t strlen(const char *a) {
	size_t len = 0;
	while (*a++) {
		len++;
	}
	return len;
}
