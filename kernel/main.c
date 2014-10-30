#include <stddef.h>
#include <stdint.h>
#include "arch/terminal.h"
#include "util/log.h"

void kernel_main() {
	kernel_log(L_INFO, "kernel",
		"Hello, "
		"\x1B[1;31m" "k"
		"\x1B[1;32m" "e"
		"\x1B[1;33m" "r"
		"\x1B[1;34m" "n"
		"\x1B[1;35m" "e"
		"\x1B[1;36m" "l"
		"\x1B[0;31m" "!");
}
