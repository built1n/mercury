#ifndef UTIL_LOG_H
#define UTIL_LOG_H

typedef enum {
    L_DEBUG,
    L_INFO,
    L_WARN,
    L_ERROR
} LOG_SEVERITY_T;

/* TODO: stdarg and printf */
void kernel_log(LOG_SEVERITY_T severity, const char *from, const char *message);

#endif
