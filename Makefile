CC = x86_64-linux-gnu-gcc
AS = nasm

CFLAGS = -ffreestanding -O2 -Wall -Wextra -m32 \
         -fno-pic -fno-pie -fno-stack-protector \
         -fno-asynchronous-unwind-tables

LDFLAGS = -T linker.ld -nostdlib -no-pie -m32

ISO_DIR = iso
BOOT_DIR = $(ISO_DIR)/boot
GRUB_DIR = $(BOOT_DIR)/grub

all: kernel.bin iso

kernel.bin:
	$(AS) -f elf32 boot/multiboot2.asm -o multiboot.o
	$(AS) -f elf32 boot/entry.asm -o entry.o
	$(CC) $(CFLAGS) -c kernel/kernel.c -o kernel.o
	$(CC) $(CFLAGS) -c kernel/cpu/gdt.c -o gdt.o
	$(CC) $(CFLAGS) -c kernel/cpu/idt.c -o idt.o
	$(CC) $(CFLAGS) -c kernel/cpu/isr.c -o isr.o
	$(CC) $(CFLAGS) -c kernel/cpu/pic.c -o pic.o
	$(CC) $(CFLAGS) -c kernel/cpu/pit.c -o pit.o
	$(CC) $(CFLAGS) -c kernel/cpu/io.c -o io.o
	$(CC) $(CFLAGS) -c kernel/graph.c -o graph.o
	$(CC) $(CFLAGS) -c kernel/memory/memory.c -o memory.o
	$(CC) $(CFLAGS) -c kernel/task/task.c -o task.o
	$(CC) $(CFLAGS) -c kernel/cpu/keyboard.c -o keyboard.o
	$(AS) -f elf32 kernel/cpu/gdt.asm -o gdt_asm.o
	$(AS) -f elf32 kernel/cpu/isr.asm -o isr_asm.o
	$(AS) -f elf32 kernel/cpu/idt.asm -o idt_asm.o
	$(AS) -f elf32 kernel/cpu/irq.asm -o irq_asm.o
	$(AS) -f elf32 kernel/task/task.asm -o task_asm.o
	$(CC) $(LDFLAGS) multiboot.o entry.o memory.o task_asm.o task.o graph.o keyboard.o irq_asm.o idt_asm.o io.o pit.o pic.o isr.o idt.o isr_asm.o gdt.o gdt_asm.o kernel.o -o kernel.bin

iso: kernel.bin
	mkdir -p $(GRUB_DIR)
	cp kernel.bin $(BOOT_DIR)/kernel.bin
	cp grub.cfg $(GRUB_DIR)/grub.cfg
	grub-mkrescue -o firmware.iso $(ISO_DIR)

run:
	qemu-system-x86_64 -cdrom firmware.iso -vga std

clean:
	rm -rf *.o kernel.bin firmware.iso iso/boot/kernel.bin
