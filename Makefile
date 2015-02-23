BINDIR:=./bin/
INCLUDE:=./include/
ARCH:=i686

KERNEL_OBJS = $(patsubst %.c,%.o,$(wildcard kernel/*.c))
KERNEL_OBJS += $(patsubst %.c,%.o,$(wildcard kernel/*/*.c))
KERNEL_OBJS += $(patsubst %.c,%.o,$(wildcard kernel/arch/$(ARCH)/*.c))
HEADERS = $(patsubst %.c,%.h,$(wildcard include/*.c))
HEADERS += $(patsubst %.c,%.h,$(wildcard include/*/*.c))

.PHONY: all

include kernel/arch/$(ARCH)/Makefile

kernel/%.o: kernel/%.c $(HEADERS)
	$(CC) $(CFLAGS) -I$(INCLUDE) -o $@ $<

clean:
	find . -name "*.o" -delete
	rm mercury-kernel
