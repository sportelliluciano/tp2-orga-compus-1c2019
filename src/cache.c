#include "cache.h"

void create_cache(mp_t *mp) {
    cache->mp = mp;
    for (int i=0; i<NUMBER_OF_SETS; i++) {
        create_set(cache->sets[i]);
    }
}

void destroy_cache() {
    for (int i=0; i<NUMBER_OF_SETS; i++) {
        destroy_set(cache->sets[i]);
    }
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
    insert_block(cache->sets[set],block,way);
}

void write_tocache(/*unsigned int address, unsigned char value*/) {

}

uint16_t get_tag(unsigned int address) {
    return (address >> 9);
}

unsigned char read_byte(unsigned int address) {
    unsigned int set = find_set(address);
    unsigned int offset = get_offset(address);
    uint16_t tag = get_tag(address);
    if (search_block_position(cache->sets[set],tag) == -1) {
        cache->miss++;
        unsigned int way = select_oldest(set);
        read_tocache(address,way,set);
    } else {
        cache->hits++;
    }
    return read_block(cache->sets[set],tag,offset);
}

void write_byte(/*unsigned int address, unsigned char value*/) {
    
}

float get_miss_rate(cache_t cache) {
    return (float)(cache.miss/(cache.miss+cache.hits));
}
