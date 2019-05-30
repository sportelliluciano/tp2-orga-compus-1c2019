#include "memoria_principal.h"
#include <stdlib.h>
#define MEMORY_SIZE (1024*64)
#define NUMBER_OF_BLOCKS 1024

void create_mp(mp_t *mp) {
    mp->memory = malloc(sizeof(char) * MEMORY_SIZE);
    for (int i=0; i<NUMBER_OF_BLOCKS; i++) {
        create_block(mp->memory[i],i);
    }
}

void destroy_mp(mp_t *mp) {
    free(mp->memory);
}

bloque_t *get_block(mp_t *mp,unsigned int tag) {
    return mp->memory[tag];
}

void write_to_mp(mp_t *mp, unsigned int tag, unsigned int position, unsigned char value) {
    write_block_byte(mp->memory[tag],position,value);
}

unsigned char read_from_mp(mp_t *mp, unsigned int tag, unsigned int position) {
    return read_block_byte(mp->memory[tag],position);
}