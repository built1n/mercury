#![no_std]
#![allow(ctypes)]

#[allow(dead_code)]
enum LogLevel {
    DEBUG,
    INFO,
    WARN,
    ERROR,
}

extern {
    fn kernel_log(severity: LogLevel, area: *const str, message: *const str);
}

#[no_mangle]
#[no_split_stack]
pub extern "C" fn kernel_main() {
    unsafe {
        kernel_log(INFO, "kernel\0",
            "Hello, \
            \x1B[1;31mk \
            \x1B[1;32me \
            \x1B[1;33mr \
            \x1B[1;34mn \
            \x1B[1;35me \
            \x1B[1;36ml \
            \x1B[0m!\0");
    }
}
