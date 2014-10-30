#ifndef UTIL_ANSI_ESCAPE_H
#define UTIL_ANSI_ESCAPE_H
#include <stdint.h>
#include <stddef.h>
#include <stdbool.h>

enum {
    ANSI_ERASE_CURSOR_TO_END,
    ANSI_ERASE_CURSOR_TO_START,
    ANSI_ERASE_ALL
};

struct ansi_hooks {
    void (*reset)();
    void (*erase_display)(uint8_t);
    void (*bold)();
    void (*light)();
    void (*set_foreground_ansi)(uint8_t);
    void (*set_background_ansi)(uint8_t);
    void (*set_foreground_rgb)(uint8_t, uint8_t, uint8_t);
    void (*set_background_rgb)(uint8_t, uint8_t, uint8_t);
};

struct ansi_state {
    struct ansi_hooks hooks;
    char buffer[512];
    size_t index;
};

void ansi_init(struct ansi_state *state);
bool ansi_add_character(struct ansi_state *state, char c);

#endif
