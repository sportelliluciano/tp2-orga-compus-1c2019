#include <stdio.h>
#include <stdbool.h>
#include "bloque.h"
#include <string.h>
#define BLOCK_LEN 64

//********************************************************

void create_block(bloque_t *block,uint8_t tag) {
    block->valid = 0;
    block->tag = tag;
}

//********************************************************

void copy_block(bloque_t *block,bloque_t *other) {
    other->tag = block->tag;
    memcpy(other->bytes,block->bytes,BLOCK_LEN);
    block->valid = 1;
    block->dirty = 0;    
}

//********************************************************

//void destroy_block(bloque_t *block) {
//}

//********************************************************

bool blocks_are_equal(bloque_t *block,bloque_t *other) {
    if (!(block_is_valid(block)) || !(block_is_valid(other))) return false;
    return block->tag == other->tag;
}

//********************************************************

void reset_block(bloque_t *block) {
    memset(block->bytes,'\0',BLOCK_LEN);
}

//********************************************************

uint8_t block_is_valid(bloque_t *block) {
    return (block->valid==1);
}

//********************************************************

char read_block_byte(bloque_t *block,uint8_t position) {
    return (block->bytes[position]);
}

//********************************************************

void write_block_byte(bloque_t *block,uint8_t position,char value) {
    block->bytes[position] = value;
}
