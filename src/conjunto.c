#include <stdio.h>
#include <stdbool.h>
#include "conjunto.h"
#include "cola.h"
#include "bloque.h"
#define MAX_BLOCKS 4

//********************************************************

void create_set(set_t *set) {
    set->block_queue = cola_crear();
    set->block_inserted = 0;
    for (uint8_t i=0; i<MAX_BLOCKS; i++) {
        create_block(set->blocks[i],i);
    }
}

//********************************************************

void destroy_set(set_t *set) {
    cola_destruir(set->block_queue,NULL);
}

//********************************************************

bool set_is_full(set_t *set) {
    return (set->block_inserted == MAX_BLOCKS);
}

//********************************************************

int search_block_position(set_t *set,bloque_t *block) {
    for (int i=0; i<MAX_BLOCKS;i++) {
        if (blocks_are_equal(set->blocks[i],block)) {
            return i;
        }
    }
    return -1; //posicion invalida (?)
}

//********************************************************

void insert_block(set_t *set,bloque_t *block) {
    if (set_is_full(set)) {
        bloque_t *invalid_block = cola_desencolar(set->block_queue);
        size_t position = search_block_position(set,invalid_block);
        set->blocks[position] = block;
    } else {
        set->blocks[set->block_inserted] = block;
    }
    cola_encolar(set->block_queue,&block);
}

//********************************************************

bloque_t *get_block_from_set(set_t *set,bloque_t *block) {
    int position = search_block_position(set,block);
    if (position == -1) return NULL;
    return set->blocks[position];
}

//********************************************************

void reset_set(set_t *set) {
    for (int i=0; i<MAX_BLOCKS; i++) {
        reset_block(set->blocks[i]);
    } 
}

//********************************************************

int get_via_last_block(set_t *set) {
    bloque_t *last = cola_ver_primero(set->block_queue);
    return search_block_position(set,last);
}