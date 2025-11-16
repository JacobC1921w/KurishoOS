#ifndef MEMORY_H
#define MEMORY_H

#include <stdint.h>
#include <stddef.h>

#define NULL_POINTER ((void *) 0)
#define DYNAMIC_MEMORY_SIZE_TOTAL 4096
#define DYNAMIC_MEMORY_NODE_SIZE sizeof(dynamic_memory_node_t)

typedef struct dynamic_memory_node {
    uint32_t size;
    bool used;
    struct dynamic_memory_node *next;
    struct dynamic_memory_node *previous;
} dynamic_memory_node_t;

void memory_move(void *dest, const void *source, size_t num_bytes);
void memory_copy(char *source, char *dest, int n_bytes);
void initialize_dynamic_memory();
void *find_best_memory_block(dynamic_memory_node_t *dynamic_memory, size_t size);
void *memory_allocate(size_t size);
void *merge_next_mode_into_current(dynamic_memory_node_t *current_memory_node);
void *merge_current_mode_into_previous(dynamic_memory_node_t *current_memory_node);
void memory_free(void *pointer);

#endif