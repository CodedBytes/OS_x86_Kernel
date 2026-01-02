CC = x86_64-linux-gnu-gcc
AS = nasm
CFLAGS = -ffreestanding -O2 -Wall -Wextra -m32 -fno-pic -fno-pie -fno-stack-protector -fno-asynchronous-unwind-tables
LDFLAGS = -T linker.ld -nostdlib -m32

OBJS = \
    arch/x86/boot.o \
    arch/x86/cpu.o \
    arch/x86/gdt.o \
    arch/x86/idt.o \
    arch/x86/idt_stubs.o \
    arch/x86/irq.o \
    arch/x86/pic.o \
    core/kernel.o \
    core/log.o \
    core/panic.o \
    drivers/vga.o \
    drivers/timer.o

ISO_DIR = iso
BOOT_DIR = $(ISO_DIR)/boot
GRUB_DIR = $(BOOT_DIR)/grub

all: kernel.iso

kernel.bin: $(OBJS)
	$(CC) $(LDFLAGS) -o $@ $(OBJS)

kernel.iso: kernel.bin
	mkdir -p $(GRUB_DIR)
	cp kernel.bin $(BOOT_DIR)/kernel.bin
	cp grub.cfg $(GRUB_DIR)/grub.cfg
	grub-mkrescue -o kernel.iso $(ISO_DIR)

%.o: %.asm
	$(AS) -f elf32 $< -o $@

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

run: kernel.iso
	qemu-system-x86_64 -cdrom kernel.iso -vga vmware

clean:
	rm -rf $(OBJS) kernel.bin kernel.iso 
