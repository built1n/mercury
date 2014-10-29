CC:=i686-elf-gcc
LD:=i686-elf-gcc
AS:=i686-elf-as
BINDIR:=./bin/
ARCH:=i686
INCLUDE:=./include/
CFLAGS:=-c -ffreestanding -std=gnu99 -O2 -Wall -Wextra -Werror

KERNEL_OBJS = $(patsubst %.c,%.o,$(wildcard kernel/*.c))
KERNEL_OBJS += $(patsubst %.c,%.o,$(wildcard kernel/*/*.c))
KERNEL_OBJS += $(patsubst %.c,%.o,$(wildcard kernel/arch/$(ARCH)/*.c))
HEADERS = $(patsubst %.c,%.o,$(wildcard include/*.c))
HEADERS += $(patsubst %.c,%.o,$(wildcard include/*/*.c))

.PHONY: all qemu

mercury-kernel: kernel/arch/$(ARCH)/kernel.ld kernel/arch/$(ARCH)/boot.o ${KERNEL_OBJS}
	$(LD) -o mercury-kernel -T kernel/arch/$(ARCH)/kernel.ld -nostdlib -ffreestanding -O2 kernel/arch/$(ARCH)/boot.o ${KERNEL_OBJS} -lgcc

kernel/arch/$(ARCH)/boot.o: kernel/arch/$(ARCH)/boot.S
	$(AS) kernel/arch/$(ARCH)/boot.S -o kernel/arch/$(ARCH)/boot.o

kernel/%.o: kernel/%.c $(HEADERS)
	$(CC) $(CFLAGS) -I$(INCLUDE) -o $@ $<

clean:
	find . -name "*.o" -delete
	rm mercury-kernel

qemu: mercury-kernel
	qemu-system-i386 -sdl -kernel mercury-kernel
