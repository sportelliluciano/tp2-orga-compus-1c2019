#ifndef CONJUNTO_H
#define CONJUNTO_H
#include "bloque.h"
#include "cola.h"
#include <stdio.h>

struct conjunto {
    cola_t *block_queue;
    size_t *block_inserted;
    bloque_t **blocks;
};

typedef struct conjunto conjunto_t;

conjunto_t create_set();

void destroy_set(conjunto_t set);

void insert_block(conjunto_t set,bloque_t *block);

#endif