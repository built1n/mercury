#include <stddef.h>
#include <stdint.h>

struct gdt_entry {
	uint16_t limit_low;
	uint16_t base_low;
	uint8_t base_middle;
	uint8_t access;
	uint8_t granularity;
	uint8_t base_high;
} __attribute__((packed));

struct gdt_ptr {
	uint16_t limit;
	uint32_t base;
} __attribute__((packed));

struct gdt_entry gdt[6];
struct gdt_ptr gp;

/* From assembly */
extern void gdt_flush(void);

void load_gdt() {
	gp.limit = ((sizeof(struct gdt_entry)) * sizeof(gdt)) - 1;
	gp.base = (uint32_t)&gdt;

	/* TODO: Actually build and load the GDT */
}
