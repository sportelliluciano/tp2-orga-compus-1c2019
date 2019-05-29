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