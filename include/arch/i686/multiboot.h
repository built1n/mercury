#ifndef MULTIBOOT_H
#define MULTIBOOT_H
#include <stdint.h>

#define MULTIBOOT_FLAG_MEMORY           1 << 0
#define MULTIBOOT_FLAG_BOOT_DEVICE      1 << 1
#define MULTIBOOT_FLAG_CMDLINE          1 << 2
#define MULTIBOOT_FLAG_MODULES          1 << 3
#define MULTIBOOT_FLAG_A_OUT            1 << 4
#define MULTIBOOT_FLAG_ELF              1 << 5
#define MULTIBOOT_FLAG_MEM_MAP          1 << 6
#define MULTIBOOT_FLAG_DRIVES           1 << 7
#define MULTIBOOT_FLAG_CONFIG           1 << 8
#define MULTIBOOT_FLAG_BOOTLOADER       1 << 9
#define MULTIBOOT_FLAG_APM_TABLE        1 << 10
#define MULTIBOOT_FLAG_GFX_TABLE        1 << 11

struct multiboot {
    uint32_t flags;
    uint32_t mem_lower;
    uint32_t mem_upper;
    uint32_t boot_device;
    uint32_t cmdline;
    uint32_t mods_count;
    uint32_t mods_addr;
    uint32_t sym_num;
    uint32_t sym_size;
    uint32_t sym_addr;
    uint32_t sym_shndx;
    uint32_t mmap_length;
    uint32_t mmap_address;
    uint32_t drives_length;
    uint32_t drives_addr;
    uint32_t config_table;
    uint32_t bootloader_name;
    uint32_t apm_table;
    uint32_t vbe_control_info;
    uint32_t vbe_mode_info;
    uint32_t vbe_mode;
    uint32_t vbe_interface_seg;
    uint32_t vbe_interface_off;
    uint32_t vbe_interface_len;
} __attribute__((packed));

struct multiboot_module {
    uint32_t mod_start;
    uint32_t mod_end;
    uint32_t string;
 /* uint32_t reserved */
} __attribute__((packed));

struct multiboot_mmap_entry {
    uint32_t base_addr;
    uint32_t length;
    uint32_t type;
} __attribute__((packed));

#endif
