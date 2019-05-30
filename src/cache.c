#include <stdlib.h>
#include "cache.h"

void create_cache(mp_t *mp) {
    cache->mp = mp;
    cache->sets = calloc(NUMBER_OF_SETS,sizeof(set_t*));
    for (int i=0; i<NUMBER_OF_SETS; i++) {
        cache->sets[i] = calloc(1,sizeof(set_t));
        create_set(cache->sets[i]);
    }
    cache->hits = 0;
    cache->miss = 0;
}

void destroy_cache() {
    for (int i=0; i<NUMBER_OF_SETS; i++) {
        destroy_set(cache->sets[i]);
        free(cache->sets[i]);
    }
    free(cache->sets);
}

void init() {
    for (int i=0; i<NUMBER_OF_SETS; i++) {
        reset_set(cache->sets[i]);
    }
}

unsigned int get_offset(unsigned int address) {
    uint16_t offset = (address << 10);
    return offset >> 10;
}

unsigned int find_set(unsigned int address) {
    uint16_t set_numb = (address << 7);
    return (set_numb >> 13);
}

unsigned int select_oldest(unsigned int setnum) {
    if (setnum>=8) return -1;
    return get_via_last_block(cache->sets[setnum]);    
}

void read_tocache(unsigned int blocknum, unsigned int way, unsigned int set) {
    if (way>=4 || set>=8) return;
    bloque_t *block = get_block(cache->mp,blocknum);
    unsigned int tag = (blocknum >> 3);
    insert_block(cache->sets[set],block,way,tag);
}

uint16_t get_tag(unsigned int address) {
    return (address >> 9);
}

unsigned int get_block_num(unsigned int address) {
    return (address >> 6);
}

void write_tocache(unsigned int address, unsigned char value) {
    unsigned int set = find_set(address);
    unsigned int offset = get_offset(address);
    uint16_t tag = get_tag(address);
    unsigned int way = search_block_position(cache->sets[set],tag);
    write_block(cache->sets[set],way,offset,value);
}

unsigned char read_byte(unsigned int address) {
    address &= 0xFFFF; // Addresses are 16 bit long
    unsigned int set = find_set(address);
    unsigned int offset = get_offset(address);
    uint16_t tag = get_tag(address);
    if (search_block_position(cache->sets[set],tag) == -1) {
        cache->miss++;
        unsigned int way = select_oldest(set);
        read_tocache(get_block_num(address),way,set);
    } else {
        cache->hits++;
    }
    return read_block(cache->sets[set],tag,offset);
}

void write_byte(unsigned int address, unsigned char value) {
    address &= 0xFFFF; // Addresses are 16 bit long
    unsigned int set = find_set(address);
    uint16_t tag = get_tag(address);
    if (search_block_position(cache->sets[set],tag) == -1) {
        cache->miss++;
    } else {
        write_tocache(address,value);
        cache->hits++;
    }
    write_to_mp(cache->mp,address,value);
}

float get_miss_rate() {
    return (cache->miss/(float)(cache->miss+cache->hits));
}
