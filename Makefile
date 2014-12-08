CC:=i686-elf-gcc
LD:=i686-elf-gcc
AS:=i686-elf-as
RS=rustc
BINDIR:=./bin/
ARCH:=i686
INCLUDE:=./include/
CFLAGS:=-c -ffreestanding -std=gnu99 -O2 -Wall -Wextra -Werror -Wno-unused-parameter

KERNEL_OBJS =  $(patsubst %.c,%.c.o,$(wildcard kernel/*.c))
KERNEL_OBJS += $(patsubst %.c,%.c.o,$(wildcard kernel/*/*.c))
KERNEL_OBJS += $(patsubst %.c,%.c.o,$(wildcard kernel/arch/$(ARCH)/*.c))

KERNEL_OBJS += $(patsubst %.rs,%.rs.o,$(wildcard kernel/*.rs))
KERNEL_OBJS += $(patsubst %.rs,%.rs.o,$(wildcard kernel/*/*.rs))
KERNEL_OBJS += $(patsubst %.rs,%.rs.o,$(wildcard kernel/arch/$(ARCH)/*.rs))

HEADERS = $(patsubst %.c,%.c.o,$(wildcard include/*.c))
HEADERS += $(patsubst %.c,%.c.o,$(wildcard include/*/*.c))

.PHONY: all qemu run

include kernel/arch/$(ARCH)/Makefile

kernel/%.c.o: kernel/%.c $(HEADERS)
	$(CC) $(CFLAGS) -I$(INCLUDE) -o $@ $<

kernel/%.rs.o: kernel/%.rs
	$(RS) -O --target i386-intel-linux --crate-type lib -o $@ --emit obj $<

clean:
	find . -name "*.o" -delete
	rm -f mercury-kernel

qemu: mercury-kernel
	qemu-system-i386 -sdl -kernel mercury-kernel -append "-system qemu"

run: qemu
