CC:=i686-elf-gcc
LD:=i686-elf-gcc
AS:=i686-elf-as
CFLAGS:=-c -ffreestanding -std=gnu99 -O2 -Wall -Wextra -Werror -Wno-unused-parameter

.PHONY: qemu run

mercury-kernel: kernel/arch/$(ARCH)/kernel.ld kernel/arch/$(ARCH)/boot.o ${KERNEL_OBJS}
	$(LD) -o mercury-kernel -T kernel/arch/$(ARCH)/kernel.ld -nostdlib -ffreestanding -O2 kernel/arch/$(ARCH)/boot.o ${KERNEL_OBJS} -lgcc

kernel/arch/$(ARCH)/boot.o: kernel/arch/$(ARCH)/boot.S
	$(AS) kernel/arch/$(ARCH)/boot.S -o kernel/arch/$(ARCH)/boot.o

qemu: mercury-kernel
	qemu-system-i386 -sdl -kernel mercury-kernel -append "-system qemu"

run: qemu
