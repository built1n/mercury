#include <stddef.h>
#include <stdint.h>
#include "arch/terminal.h"
#include "output.h"

void kernel_main() {
	print_string("Hello, world!");
}
