#include <stdio.h>
#include <stdbool.h>
#include "conjunto.h"
#include "cola.h"
#include "bloque.h"
#define MAX_BLOCKS 256 //cuentas en hoja(?)

//********************************************************

conjunto_t create_set() {
    conjunto_t set;
    set.block_queue = cola_crear(); //deberia pedir memoria para esto(?)
    set.block_inserted = malloc(sizeof(size_t));
    set.blocks = malloc(sizeof(bloque_t*) * MAX_BLOCKS);
    //if (!(set.is_full) || (!set.block_queue)) return NULL; //tendriamosque revisar (?) ellos ni se gastaban en liberar memoria...
    return set;
}

//********************************************************

void destroy_set(conjunto_t set) {
    free(set.block_inserted);
    //cola_destruir(set.block_queue,); le deberia pasar una funcion que destruya los bloques? despues deberia destruir el resto lo unico que se me ocurre para saber cuals se destruyeron es dejarlos en modo invalido pero nose si estaria bien que algo destruido me pueda seguir dando info
    free(set.blocks);
}

//********************************************************

bool set_is_full(conjunto_t set) {
    return (set.block_inserted == MAX_BLOCKS);
}

//********************************************************

size_t search_block_position(conjunto_t set,bloque_t *block) {
    size_t position = 0;
    for (size_t i=0; i++; i<set.block_inserted) {
        if (blocks_are_equeal(*set.blocks[i],*block)) {
            return i;
        }
    }
    return (MAX_BLOCKS+1); //posicion invalida (?)
}

//********************************************************

void insert_block(conjunto_t set,bloque_t *block) {
    if (set_is_full(set)) {
        bloque_t *invalid_block = cola_desencolar(set.block_queue);
        size_t position = search_block_position(set,invalid_block);
        set.blocks[position] = block;
        cola_encolar(set.block_queue,&block);
    } else {
        cola_encolar(set.block_queue,&block);
        set.block_inserted++;
        block->valid = 1;
    }
}

//********************************************************
