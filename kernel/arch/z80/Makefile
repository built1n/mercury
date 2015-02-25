CC:=kcc
AS:=scas
CFLAGS:=-c --std-c99

.PHONY: wabbitemu run knightos-libc

ARCH_ASM_OBJS = $(patsubst %.S,%.o,$(wildcard kernel/arch/$(ARCH)/*.S))
ARCH_ASM_INCL = $(wildcard kernel/arch/$(ARCH)/include/*.inc)

knightos-libc:
	cd kernel/arch/$(ARCH)/libc && { [[ -d .knightos ]] || knightos init; }
	cd kernel/arch/$(ARCH)/libc && make

mercury-kernel: ${ARCH_ASM_OBJS} ${KERNEL_OBJS} knightos-libc
	$(AS) -l -o mercury-kernel kernel/arch/$(ARCH)/boot.o ${KERNEL_OBJS} kernel/arch/$(ARCH)/libc/bin/root/lib/c

kernel/arch/$(ARCH)/%.o: kernel/arch/$(ARCH)/%.S ${ASM_INCLUDE}
	$(AS) -O -Ikernel/arch/$(ARCH)/include/ $< -o $@

wabbitemu: mercury-kernel
	qemu-system-i386 -sdl -kernel mercury-kernel -append "-system qemu"

run: wabbitemu
