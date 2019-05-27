#include <stdio.h>
#include <stdbool.h>
#include "bloque.h"
#define LARGO_ETIQUETA 2 //por lo que lei la etiqueta sirve para identificar el conjunto y como habra 4 con 2 alcanza (?)
#define LARGO_BLOQUE 64

struct bloque {
    char *etiqueta;
    char *conjunto;
};

//********************************************************

bloque_t create_block() {
    bloque_t block;
    block.conjunto = malloc(sizeof(char) * (LARGO_BLOQUE -LARGO_ETIQUETA));
    block.etiqueta = malloc(sizeof(char) * LARGO_ETIQUETA);
    //if (!(block.etiqueta) || !(block.conjunto)) return NULL;
    return block;
}

//********************************************************

void destroy_block(bloque_t block) {
    free(block.conjunto);
    free(block.etiqueta);
}

//********************************************************

bool blocks_are_equal(bloque_t block,bloque_t other) {
    if (strncmp(block.etiqueta,other.etiqueta,LARGO_ETIQUETA) != 0) {
        return false;
    }
    return (strncmp(block.conjunto,other.conjunto,LARGO_BLOQUE-LARGO_ETIQUETA) == 0); //No paso el estilo de google :( 
}

//********************************************************
