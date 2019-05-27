#ifndef BLOQUE_H
#define BLOQUE_H

struct bloque {
    char *tag;
    char *line;
    size_t *valid; //0 invalid 1 valid
};

typedef struct bloque bloque_t;

bloque_t create_block();

void destroy_block(bloque_t block);

bool blocks_are_equal(bloque_t block,bloque_t other); 

void reset_block(bloque_t block);

void set_block_tag(bloque_t block,char* tag);

void set_block_line(bloque_t block, char* line);

void set_block_valid(bloque_t block);

#endif