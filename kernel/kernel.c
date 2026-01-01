#include "cpu/gdt.h"
#include "cpu/idt.h"
#include "cpu/pic.h"
#include "cpu/pit.h"
#include "cpu/keyboard.h"
#include "cpu/isr.h"
#include "graph.h"
#include "kernel.h"
#include <stdint.h>
#include "memory/memory.h"
#include "task/task.h"

// Heap
#define HEAP_START 0x1000000
#define HEAP_END   0x1100000

vesa_mode_info_t vesa_info;

// ---------- Multiboot ----------
void parse_multiboot(uint32_t* mb_info) {
    uint32_t total_size = *mb_info;
    uint8_t* tag_ptr = (uint8_t*)(mb_info + 2);

    while(tag_ptr < (uint8_t*)mb_info + total_size) {
        multiboot_tag_t* tag = (multiboot_tag_t*)tag_ptr;
        if(tag->type == 0) break;

        if(tag->type == 8) {
            mb2_tag_framebuffer_t* fb = (mb2_tag_framebuffer_t*)tag;
            vesa_info.framebuffer = (uint32_t)fb->framebuffer_addr;
            vesa_info.width       = fb->framebuffer_width;
            vesa_info.height      = fb->framebuffer_height;
            vesa_info.bpp         = fb->framebuffer_bpp;
            vesa_info.pitch       = fb->framebuffer_pitch;
            return;
        }
        tag_ptr += (tag->size + 7) & ~7;
    }
}

// ---------- Kernel ----------
semaphore_t sem;

void task1() {
    while (1) {
        vesa_draw_string(50, 90, "Task 1: Waiting", 0xFFFF00);

        // Tenta adquirir o semáforo
        semaphore_wait(&sem);

        // Se conseguiu o semáforo, trabalha por um tempo
        vesa_draw_string(50, 110, "Task 1: Running", 0xFFFF00);
        for (volatile int i = 0; i < 1000000; i++);
        
        // Libera o semáforo
        semaphore_signal(&sem);

        task_yield();
    }
}

void task2() {
    while (1) {
        vesa_draw_string(50, 150, "Task 2: Waiting", 0x00FFFF);

        // Tenta adquirir o semáforo
        semaphore_wait(&sem);

        // Se conseguiu o semáforo, trabalha por um tempo
        vesa_draw_string(50, 170, "Task 2: Running", 0x00FFFF);
        for (volatile int i = 0; i < 1000000; i++);

        // Libera o semáforo
        semaphore_signal(&sem);

        task_yield();
    }
}

void kernel_main(uint32_t* mb_info) {
    // Inicializações de hardware, memória, etc.
    gdt_init();
    idt_init();
    pic_remap();
    pit_init(50);

    parse_multiboot(mb_info);
    vesa_init(vesa_info.framebuffer, vesa_info.width, vesa_info.height, vesa_info.bpp, vesa_info.pitch);
    vesa_clear(0x000000);
    
    // Inicializa o semáforo com valor 1
    sem.value = 1;
    sem.queue_count = 0;

    memory_init(HEAP_START, HEAP_END);
    task_init();

    task_create(task1);
    task_create(task2);

    current_task = 0;
    tasks[0].state = TASK_RUNNING;

    irq_install_handler(1, keyboard_callback);
    __asm__ volatile("sti");

    static context_t kernel_ctx;
    context_switch(&kernel_ctx, &tasks[0].ctx);

    while(1) __asm__ volatile("hlt");
}
