#include <stddef.h>
#include <stdint.h>
#include "arch/terminal.h"
#include "util/log.h"

void kernel_main() {
	kernel_log(L_INFO, "kernel",
		"Hello, "
		"\x1B[31m" "w"
		"\x1B[32m" "o"
		"\x1B[33m" "r"
		"\x1B[34m" "l"
		"\x1B[35m" "d"
		"\x1B[36m" "!");
}
