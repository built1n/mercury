#![no_std]
#![allow(ctypes)]
#![feature(lang_items)]

#[lang="sized"]
trait Sized {}

#[repr(C)]
pub struct Multiboot {
    flags: u32,
    mem_lower: u32,
    mem_upper: u32,
    boot_device: u32,
    cmdline: u32,
    mods_count: u32,
    mods_addr: u32,
    sym_num: u32,
    sym_size: u32,
    sym_addr: u32,
    sym_shndx: u32,
    mmap_length: u32,
    mmap_address: u32,
    drives_length: u32,
    drives_addr: u32,
    config_table: u32,
    bootloader_name: u32,
    apm_table: u32,
    vbe_control_info: u32,
    vbe_mode_info: u32,
    vbe_mode: u32,
    vbe_interface_seg: u32,
    vbe_interface_off: u32,
    vbe_interface_len: u32,
}

extern {
    fn kernel_main();
    fn initialize_vga_terminal();
    fn load_gdt();
}

#[no_mangle]
#[no_split_stack]
pub extern "C" fn i686_main(multiboot: Multiboot, magic: u32) {
    unsafe {
        initialize_vga_terminal();
        load_gdt();
        kernel_main();
    }
}
