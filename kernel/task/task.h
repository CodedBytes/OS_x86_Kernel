#ifndef TASK_H
#define TASK_H

#include <stdint.h>

#define MAX_TASKS 8
#define STACK_SIZE 0x4000 // 16 KB por task
#define INT_MAX 65555


typedef enum {
    TASK_READY,
    TASK_RUNNING,
    TASK_WAITING
} task_state_t;

// Contexto salvo/restaurado no context switch
typedef struct {
    uint32_t edi, esi, ebp, ebx, edx, ecx, eax;
    uint32_t eip;
    uint32_t esp;
} context_t;

typedef struct task {
    uint64_t rsp;       // stack pointer
    uint64_t rip;       // instruction pointer
    uint64_t pid;
    context_t ctx;
    task_state_t state;
    uint8_t stack[STACK_SIZE];
    int priority;       // Adicionando prioridade à task
} task_t;

typedef struct semaphore {
    int value;
    task_t* queue[MAX_TASKS];  // Queue of tasks waiting on the semaphore
    int queue_count;
} semaphore_t;

// Globais
extern task_t tasks[MAX_TASKS];
extern int current_task;

// Funções
void task_init();
int task_create(void (*func)());
void task_yield();
void schedule();

#endif
