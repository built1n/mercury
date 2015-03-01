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

struct gdt_entry gdt[3];
struct gdt_ptr gp;

/* From assembly */
extern void gdt_flush(void);

void gdt_set_gate(size_t index, uint64_t base, uint64_t limit, uint8_t access, uint8_t granularity) {
	gdt[index].base_low = (base & 0xFFFF);
	gdt[index].base_middle = (base >> 16) & 0xFF;
	gdt[index].base_high = (base >> 24) & 0xFF;
	gdt[index].limit_low = limit & 0xFFFF;
	gdt[index].granularity = (limit >> 16) & 0x0F;
	gdt[index].granularity |= granularity & 0xF0;
	gdt[index].access = access;
}

void load_gdt() {
	gp.limit = sizeof(gdt) - 1;
	gp.base = (uint32_t)&gdt;

	/* NULL gate */
	gdt_set_gate(0, 0, 0, 0, 0);
	/* Code segment */
	gdt_set_gate(1, 0, 0xFFFFFFFF, 0x9A, 0xCF);
	/* Data segment */
	gdt_set_gate(2, 0, 0xFFFFFFFF, 0x92, 0xCF);
	gdt_flush();
}
