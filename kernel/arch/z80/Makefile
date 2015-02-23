CC:=kcc
AS:=scas
CFLAGS:=-c --std-c99

.PHONY: wabbitemu run

ARCH_ASM_OBJS = $(patsubst %.S,%.o,$(wildcard kernel/arch/$(ARCH)/*.S))
ARCH_ASM_INCL = $(wildcard kernel/arch/$(ARCH)/include/*.inc)

mercury-kernel: ${ARCH_ASM_OBJS} ${KERNEL_OBJS}
	echo todo

kernel/arch/$(ARCH)/%.o: kernel/arch/$(ARCH)/%.S ${ASM_INCLUDE}
	$(AS) -O -Ikernel/arch/$(ARCH)/include/ $< -o $@

wabbitemu: mercury-kernel
	qemu-system-i386 -sdl -kernel mercury-kernel -append "-system qemu"

run: wabbitemu
