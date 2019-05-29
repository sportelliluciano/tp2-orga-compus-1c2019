#ifndef SET_H
#define SET_H
#include "bloque.h"
#include "cola.h"
#include <stdio.h>

struct set {
    cola_t *block_queue;
    bloque_t **blocks;
    uint8_t block_inserted;
};

typedef struct set set_t;

void create_set(set_t *set);

void destroy_set(set_t *set);

void insert_block(set_t *set,bloque_t *block);

bloque_t *get_block_from_set(set_t *set,bloque_t *block);

void reset_set(set_t *set);

#endif