#include <stdio.h>
#include <stdbool.h>
#include "bloque.h"
#define TAG_LEN 5 //cuentas en diagramas/notas.txt
#define BLOCK_LEN 64

//********************************************************

bloque_t create_block() {
    bloque_t block;
    block.line = malloc(sizeof(char) * (BLOCK_LEN -TAG_LEN));
    block.tag = malloc(sizeof(char) * TAG_LEN);
    block.valid = malloc(sizeof(size_t));
    *block.valid = 0;
    //if (!(block.tag) || !(block.line) || !(block.valid)) return NULL;
    return block;
}

//********************************************************

void destroy_block(bloque_t block) {
    free(block.line);
    free(block.tag);
    free(block.valid);
}

//********************************************************

bool blocks_are_equal(bloque_t block,bloque_t other) {
    if ((block.valid == 0) ||(other.valid) == 0) return false;
    if (strncmp(block.tag,other.tag,TAG_LEN) != 0) {
        return false;
    }
    return (strncmp(block.line,other.line,BLOCK_LEN-TAG_LEN) == 0); //No paso el estilo de google :( 
}

//********************************************************

void reset_block(bloque_t block) {
    memset(block.tag,'\0',BLOCK_LEN-TAG_LEN);
    memset(block.line,'\0',TAG_LEN);
    block.valid = 0;
}

//********************************************************

void set_block_tag(bloque_t block,char* tag) {
    memcpy(block.tag,tag,TAG_LEN);
}

//********************************************************

void set_block_line(bloque_t block, char* line) {
    memcpy(block.line,line,BLOCK_LEN-TAG_LEN);
}

//********************************************************

void set_block_valid(bloque_t block) {
    block.valid = 1;
}
