#ifndef ARCH_TERMINAL_H
#define ARCH_TERMINAL_H

struct arch_terminal {
    void (* print_character)(char);
};

void set_kernel_terminal(struct arch_terminal terminal);
void kernel_print_character(char c);

#endif
