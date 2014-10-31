mercury-kernel: kernel/arch/$(ARCH)/kernel.ld kernel/arch/$(ARCH)/boot.o ${KERNEL_OBJS}
	$(LD) -o mercury-kernel -T kernel/arch/$(ARCH)/kernel.ld -nostdlib -ffreestanding -O2 kernel/arch/$(ARCH)/boot.o ${KERNEL_OBJS} -lgcc

kernel/arch/$(ARCH)/boot.o: kernel/arch/$(ARCH)/boot.S
	$(AS) kernel/arch/$(ARCH)/boot.S -o kernel/arch/$(ARCH)/boot.o
