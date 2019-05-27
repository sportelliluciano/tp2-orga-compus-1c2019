#include <stdio.h>
#include <stdbool.h>
#include "conjunto.h"
#include "cola.h"
#include "bloque.h"
#define MAX_BLOCKS 32 //2048byte (2kb) / 64byte (cada bloque) = 32 (?)

//********************************************************

conjunto_t create_set() {
    conjunto_t set;
    //set.block_queue = malloc(sizeof(cola_t*));
    set.block_queue = cola_crear();
    set.block_inserted = malloc(sizeof(size_t));
    set.blocks = malloc(sizeof(bloque_t*) * 32);
    //if (!(set.is_full) || (!set.block_queue)) return NULL;
    return set;
}

//********************************************************

void destroy_set(conjunto_t set) {
    free(set.block_inserted);
    //free(set.block_queue);
    free(set.blocks);
}

//********************************************************

bool set_is_full(conjunto_t set) {
    return (set.block_inserted == MAX_BLOCKS);
}

//********************************************************

size_t search_block_position(conjunto_t set,bloque_t block) {
    size_t position = 0;
    for (size_t i=0; i++; i<set.block_inserted) {
        if (blocks_are_equeal(set.blocks[i],block));
    }
    return (MAX_BLOCKS+1); //posicion invalida (?)
}

//********************************************************

void insert_block(conjunto_t set,bloque_t block) {
    if (set_is_full(set)) {
        bloque_t *delete_block = cola_desencolar(set.block_queue);
        size_t position = search_block_position(set,*delete_block);
        set.blocks[position] = &block;
        cola_encolar(set.block_queue,&block);
    } else {
        cola_encolar(set.block_queue,&block);
        set.block_inserted++;
    }
}

//********************************************************
