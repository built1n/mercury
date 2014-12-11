CC:=i686-elf-gcc
LD:=i686-elf-gcc
AS:=i686-elf-as
BINDIR:=./bin/
ARCH:=i686
INCLUDE:=./include/
CFLAGS:=-c -ffreestanding -std=gnu99 -O2 -Wall -Wextra -Werror -Wno-unused-parameter

KERNEL_OBJS = $(patsubst %.c,%.o,$(wildcard kernel/*.c))
KERNEL_OBJS += $(patsubst %.c,%.o,$(wildcard kernel/*/*.c))
KERNEL_OBJS += $(patsubst %.c,%.o,$(wildcard kernel/arch/$(ARCH)/*.c))
HEADERS = $(patsubst %.c,%.o,$(wildcard include/*.c))
HEADERS += $(patsubst %.c,%.o,$(wildcard include/*/*.c))

.PHONY: all qemu run

include kernel/arch/$(ARCH)/Makefile

kernel/%.o: kernel/%.c $(HEADERS)
	$(CC) $(CFLAGS) -I$(INCLUDE) -o $@ $<

clean:
	find . -name "*.o" -delete
	rm mercury-kernel

qemu: mercury-kernel
	qemu-system-i386 -sdl -kernel mercury-kernel -append "-system qemu"

run: qemu
