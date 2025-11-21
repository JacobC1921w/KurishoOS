#include "memory.h"
#include <stdbool.h>


void memory_copy(char *source, char *dest, int n_bytes) {
    int i;
    for(i = 0; i < n_bytes; i++) {
        *(dest + i) = *(source + i);
    }
}

void memory_move(void *dest, const void *source, size_t num_bytes) {
    char *d = (char *)dest;
    const char *s = (const char*)source;

    if (d <= s || d >= s + num_bytes) {
        while (num_bytes--) {
            *d++ = *s++;
        }
    } else {
        d += num_bytes;
        s += num_bytes;

        while (num_bytes--) {
            *--d = *--s;
        }
    }
}

static uint8_t dynamic_memory_area[DYNAMIC_MEMORY_SIZE_TOTAL];
static dynamic_memory_node_t *dynamic_memory_start;

void initialize_dynamic_memory() {
    dynamic_memory_start = (dynamic_memory_node_t *) dynamic_memory_area;
    dynamic_memory_start->size = DYNAMIC_MEMORY_SIZE_TOTAL - DYNAMIC_MEMORY_NODE_SIZE;
    dynamic_memory_start->next = NULL_POINTER;
    dynamic_memory_start->previous = NULL_POINTER;
}

void *find_best_memory_block(dynamic_memory_node_t *dynamic_memory, size_t size) {
    dynamic_memory_node_t *best_memory_block = (dynamic_memory_node_t *) NULL_POINTER;
    uint32_t best_memory_block_size = DYNAMIC_MEMORY_SIZE_TOTAL + 1;

    dynamic_memory_node_t *current_memory_block = dynamic_memory;
    while (current_memory_block) {
        if ((!current_memory_block->used) && (current_memory_block->size >= (size + DYNAMIC_MEMORY_NODE_SIZE)) && (current_memory_block->size <= best_memory_block_size)) {
            best_memory_block = current_memory_block;
            best_memory_block_size = current_memory_block->size;
        }

        current_memory_block = current_memory_block->next;
    }

    return best_memory_block;
}

void *memory_allocate(size_t size) {
    dynamic_memory_node_t *best_memory_block = (dynamic_memory_node_t *) find_best_memory_block(dynamic_memory_start, size);

    if (best_memory_block != NULL_POINTER) {
        best_memory_block->size = best_memory_block->size - size - DYNAMIC_MEMORY_NODE_SIZE;

        dynamic_memory_node_t *memory_node_allocate = (dynamic_memory_node_t *) (((uint8_t *) best_memory_block) + DYNAMIC_MEMORY_NODE_SIZE + best_memory_block->size);

        memory_node_allocate->size = size;
        memory_node_allocate->used = true;
        memory_node_allocate->next = best_memory_block->next;
        memory_node_allocate->previous = best_memory_block;

        if (best_memory_block->next != NULL_POINTER) {
            best_memory_block->next->previous = memory_node_allocate;
        }

        best_memory_block->next = memory_node_allocate;

        return (void *) ((uint8_t *) memory_node_allocate + DYNAMIC_MEMORY_NODE_SIZE);
    }

    return NULL_POINTER;
}

void *merge_next_mode_into_current(dynamic_memory_node_t *current_memory_node) {
    dynamic_memory_node_t *next_memory_node = current_memory_node->next;

    if (next_memory_node != NULL_POINTER && !next_memory_node->used) {
        current_memory_node->size += current_memory_node->next->size;
        current_memory_node->size += DYNAMIC_MEMORY_NODE_SIZE;

        current_memory_node->next = current_memory_node->next->next;

        if (current_memory_node->next != NULL_POINTER) {
            current_memory_node->next->previous = current_memory_node;
        }
    }
    return current_memory_node;
}

void *merge_current_mode_into_previous(dynamic_memory_node_t *current_memory_node) {
    dynamic_memory_node_t *previous_memory_node = current_memory_node->previous;

    if (previous_memory_node != NULL_POINTER && !previous_memory_node->used) {
        previous_memory_node->size += current_memory_node->size;
        previous_memory_node->size += DYNAMIC_MEMORY_NODE_SIZE;

        previous_memory_node->next = current_memory_node->next;

        if (current_memory_node->next != NULL_POINTER) {
            current_memory_node->next->previous = previous_memory_node;
        }
    }
}

void memory_free(void *pointer) {
    if (pointer == NULL_POINTER) {
        return;
    }

    dynamic_memory_node_t *current_memory_node = (dynamic_memory_node_t *) ((uint8_t *) pointer - DYNAMIC_MEMORY_NODE_SIZE);

    if (current_memory_node == NULL_POINTER) {
        return;
    }

    current_memory_node->used = false;

    current_memory_node = merge_next_mode_into_current(current_memory_node);
    merge_current_mode_into_previous(current_memory_node);
}