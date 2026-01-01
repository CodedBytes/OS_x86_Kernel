#include "task.h"
#include <stddef.h>
#include "../memory/memory.h"

task_t tasks[MAX_TASKS];
int task_count = 0;
int current_task = 0;      
int quantum = 10;           
int task_counter[MAX_TASKS] = {0}; 

extern void context_switch(context_t* old_ctx, context_t* new_ctx);

void task_init() {
    task_count = 0;
    current_task = 0; // Começamos na task 0 (geralmente o kernel/idle)
    for(int i = 0; i < MAX_TASKS; i++) task_counter[i] = 0;
}

int task_create(void (*func)()) {
    if (task_count >= MAX_TASKS || func == NULL) return -1;

    task_t* t = &tasks[task_count];
    t->pid = task_count;
    t->state = TASK_READY;

    // Limpa a stack da task com zeros para evitar lixo
    for (int i = 0; i < STACK_SIZE; i++) t->stack[i] = 0;

    // Aponta para o topo da stack (lembrando que a stack cresce para baixo em x86)
    uint32_t* stack_ptr = (uint32_t*)(t->stack + STACK_SIZE);

    // Preparação da stack (Simula um contexto salvo)
    t->ctx.eip = (uint32_t)func;
    t->ctx.ebp = (uint32_t)stack_ptr;
    t->ctx.esp = (uint32_t)stack_ptr;

    task_count++;
    return task_count - 1;
}

void task_yield() {
    if (task_count <= 1) return;

    int old_idx = current_task;

    // Em uma chamada manual de yield, ignoramos o quantum e trocamos logo
    tasks[old_idx].state = TASK_READY;
    current_task = (current_task + 1) % task_count;
    tasks[current_task].state = TASK_RUNNING;
    
    task_counter[current_task] = 0; // Reseta o contador para a nova task

    context_switch(&tasks[old_idx].ctx, &tasks[current_task].ctx);
}

// Esta função deve ser chamada pelo PIT (Timer) para Multitasking Preemptivo
void schedule() {
    if (task_count <= 1) return;

    task_counter[current_task]++;

    if (task_counter[current_task] >= quantum) {
        task_yield();
    }
}

void semaphore_wait(semaphore_t* sem) {
    // Decrementa o semáforo. Se for 0, bloqueia a tarefa.
    sem->value--;

    if (sem->value < 0) {
        // Adiciona a tarefa à fila de espera
        tasks[current_task].state = TASK_WAITING;
        sem->queue[sem->queue_count++] = &tasks[current_task];
        task_yield();  // Chama task_yield para alternar para outra tarefa
    }
}

void semaphore_signal(semaphore_t* sem) {
    // Incrementa o semáforo. Se houver tarefas esperando, desbloqueia uma.
    sem->value++;

    if (sem->value <= 0) {
        // Desbloqueia uma tarefa da fila de espera
        task_t* task_to_unblock = sem->queue[0];
        for (int i = 0; i < sem->queue_count - 1; i++) {
            sem->queue[i] = sem->queue[i + 1];
        }
        sem->queue_count--;
        
        // Marca a tarefa como pronta e pronta para execução
        task_to_unblock->state = TASK_READY;
    }
}
