#ifndef MP_H
#define MP_H
#define CAPACITY (1024*64)
#include <stdio.h>
#include "bloque.h"

struct mp {
    bloque_t **memory;
};

typedef struct mp mp_t;

void create_mp(mp_t* mp);

void write_to_mp(mp_t *mp, unsigned int tag, unsigned int position, unsigned char value);

unsigned char read_from_mp(mp_t *mp, unsigned int tag, unsigned int position);

bloque_t *get_block(mp_t *mp,unsigned int tag);

#endif
