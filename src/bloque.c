#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <stdlib.h>
#include "bloque.h"
#define BLOCK_LEN 64

//********************************************************

void create_block(bloque_t *block) {
    block->valid = 0;
    block->bytes = calloc(BLOCK_LEN,sizeof(char));
}

//********************************************************

void copy_block(bloque_t *block,bloque_t *other,uint8_t tag) {
    other->tag = tag;
    memcpy(other->bytes,block->bytes,BLOCK_LEN);
    block->valid = 1;
    block->dirty = 0;    
}

//********************************************************

void destroy_block(bloque_t *block) {
    free(block->bytes);
}

//********************************************************

bool blocks_are_equal(bloque_t *block,bloque_t *other) {
    if (!(block_is_valid(block)) || !(block_is_valid(other))) return false;
    return block->tag == other->tag;
}

//********************************************************

void reset_block(bloque_t *block) {
    memset(block->bytes,'\0',BLOCK_LEN);
    block->dirty = 0;
    block->valid = 0;
}

//********************************************************

uint8_t block_is_valid(bloque_t *block) {
    return (block->valid==1);
}

//********************************************************

uint8_t get_block_tag(bloque_t *block) {
    return (block->tag);
}

//********************************************************

unsigned char read_block_byte(bloque_t *block,uint8_t position) {
    return (block->bytes[position]);
}

//********************************************************

void write_block_byte(bloque_t *block,uint8_t position,char value) {
    block->bytes[position] = value;
    //printf("Leo durante el write block:%i\n", block->bytes[position]);
}

//********************************************************

void block_to_valid(bloque_t *block) {
    block->valid=1;
}

