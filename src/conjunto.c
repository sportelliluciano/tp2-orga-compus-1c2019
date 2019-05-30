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

int search_block_position(set_t *set,uint8_t tag) {
    for (int i=0; i<MAX_BLOCKS;i++) {
        if (!block_is_valid(set->blocks[i])) continue;
        if (get_block_tag(set->blocks[i]) != tag) continue;
        return i;
    }
    return -1; //posicion invalida (?)
}

//********************************************************

void insert_block(set_t *set,bloque_t *block, unsigned int way) {
    copy_block(block,set->blocks[way]);
    cola_encolar(set->block_queue,&block);
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
    return search_block_position(set,get_block_tag(last));
}

//********************************************************

unsigned char read_block(set_t *set, unsigned int way,unsigned int offset) {
    return read_block_byte(set->blocks[way],offset);
}

//********************************************************

bool block_set_is_valid(set_t *set,unsigned int way) {
    return block_is_valid(set->blocks[way]);
}