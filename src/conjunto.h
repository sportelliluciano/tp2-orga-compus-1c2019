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

void insert_block(set_t *set,bloque_t *block, unsigned int way,unsigned int tag);

void reset_set(set_t *set);

int get_via_last_block(set_t *set); 

int search_block_position(set_t *set,uint8_t tag);

unsigned char read_block(set_t *set, unsigned int tag,unsigned int offset); 

void write_block(set_t *set, unsigned int way,unsigned int offset,char value);

#endif