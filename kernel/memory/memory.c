#include "memory.h"

// Heap simples com alocador tipo "bump pointer"
static uintptr_t heap_start;
static uintptr_t heap_end;
static uintptr_t heap_current;

void memory_init(uintptr_t start, uintptr_t end) {
    heap_start = start;
    heap_current = start;
    heap_end = end;
}

void* malloc(uint32_t size) {
    if (heap_current + size > heap_end)
        return 0; // sem memória
    void* ptr = (void*)heap_current;
    heap_current += size;
    return ptr;
}

void free(void* ptr) {
    // Neste primeiro alocador, free não faz nada
}
