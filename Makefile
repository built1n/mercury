ARCH:=i686

BINDIR:=./bin/
INCLUDE:=./include/
INTERM_FORMAT:=c

KERNEL_OBJS = $(patsubst %.c,%.o,$(wildcard kernel/*.c))
KERNEL_OBJS += $(patsubst %.c,%.o,$(wildcard kernel/*/*.c))
KERNEL_OBJS += $(patsubst %.c,%.o,$(wildcard kernel/arch/$(ARCH)/*.c))
HEADERS = $(patsubst %.c,%.h,$(wildcard include/*.c))
HEADERS += $(patsubst %.c,%.h,$(wildcard include/*/*.c))

.PHONY: all

include kernel/arch/$(ARCH)/Makefile

all: mercury-kernel

kernel/%.o: kernel/%.c $(HEADERS)
	$(CC) $(CFLAGS) -I$(INCLUDE) -I$(INCLUDE)arch/$(ARCH)/ -o $@ $<

clean:
	find . -name "*.o" -delete
	find . -maxdepth 3 -name "*.asm" -delete
	rm mercury-kernel
