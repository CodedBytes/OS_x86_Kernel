#ifndef MEMORY_H
#define MEMORY_H

#include <stdint.h>

void memory_init(uintptr_t start, uintptr_t end); // Inicializa heap
void* malloc(uint32_t size);
void free(void* ptr);

#endif
