#include "../../include/types.h"

extern void* isr_stub_table[];
extern void irq0_handler(void);

struct idt_entry {
    u16 offset_low;
    u16 selector;
    u8  zero;
    u8  type_attr;
    u16 offset_high;
} __attribute__((packed));

struct idt_ptr {
    u16 limit;
    u32 base;
} __attribute__((packed));

static struct idt_entry idt[256];
static struct idt_ptr idt_descriptor;

static void idt_set_gate(int n, u32 handler) {
    idt[n].offset_low  = handler & 0xFFFF;
    idt[n].selector    = 0x08; // code segment
    idt[n].zero        = 0;
    idt[n].type_attr   = 0x8E; // present, ring 0, interrupt gate
    idt[n].offset_high = (handler >> 16) & 0xFFFF;
}

void idt_init(void) {
    for (int i = 0; i < 256; i++) {
        idt_set_gate(i, (u32)isr_stub_table[i]);
    }

    idt_set_gate(32, (u32)irq0_handler);

    idt_descriptor.limit = sizeof(idt) - 1;
    idt_descriptor.base  = (u32)&idt;

    __asm__ volatile ("lidt %0" : : "m"(idt_descriptor));
}
