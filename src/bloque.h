#ifndef BLOQUE_H
#define BLOQUE_H
#include <stdint.h>
#include <stdbool.h>

struct bloque {
    char *bytes;
    uint8_t tag;
    uint8_t valid;//0 invalid
    uint8_t dirty;//1 dirty
};

typedef struct bloque bloque_t;

void create_block(bloque_t *block);

void destroy_block(bloque_t *block);

bool blocks_are_equal(bloque_t *block,bloque_t *other); 

void reset_block(bloque_t *block);

uint8_t block_is_valid(bloque_t *block); 

void block_to_valid(bloque_t *block);

uint8_t get_block_tag(bloque_t *block);

void copy_block(bloque_t *block,bloque_t *other,uint8_t tag);

unsigned char read_block_byte(bloque_t *block,uint8_t position);

void write_block_byte(bloque_t *block,uint8_t position,char value);

#endif