#include "memoria_principal.h"
#include <stdlib.h>
#define MEMORY_SIZE (1024*64)
#define NUMBER_OF_BLOCKS 1024

void create_mp(mp_t *mp) {
    mp->memory = malloc(sizeof(char) * MEMORY_SIZE);
    for (int i=0; i<NUMBER_OF_BLOCKS; i++) {
        mp->memory[i] = calloc(1,sizeof(bloque_t));
        create_block(mp->memory[i]);
    }
}

void destroy_mp(mp_t *mp) {
    for (int i=0; i<NUMBER_OF_BLOCKS; i++) {
        destroy_block(mp->memory[i]);
        free(mp->memory[i]);
    }
    free(mp->memory);
}

uint16_t get_block_number(unsigned int address) {
    return (address >> 6);
}

uint16_t get_block_offset(unsigned int address) {
    uint16_t offset = (address << 10);
    return offset >> 10;
}

bloque_t *get_block(mp_t *mp,unsigned int blocknum) {
    return mp->memory[blocknum];
}

void write_to_mp(mp_t *mp, unsigned int address, unsigned char value) {
    uint16_t block_num = get_block_number(address);
    uint16_t offset = get_block_offset(address);
    write_block_byte(mp->memory[block_num],offset,value);
}

unsigned char read_from_mp(mp_t *mp, unsigned int blocknum, unsigned int position) {
    return read_block_byte(mp->memory[blocknum],position);
}