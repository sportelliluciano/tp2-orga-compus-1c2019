#include "cache.h"

void create_cache(){
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

}

void write_tocache(unsigned int address, unsigned char c) {

}

unsigned char read_byte(unsigned int address) {
    return 0;
}

void write_byte(unsigned int address, unsigned char value) {

}

float get_miss_rate(cache_t cache) {
    return (float)(cache.miss/(cache.miss+cache.hits));
}
