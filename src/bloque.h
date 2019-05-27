#ifndef BLOQUE_H
#define BLOQUE_H

struct bloque {
    char *etiqueta;
    char *conjunto;
};

typedef struct bloque bloque_t;

bloque_t create_block();

void destroy_block(bloque_t block);

bool blocks_are_equal(bloque_t block,bloque_t other); 

#endif