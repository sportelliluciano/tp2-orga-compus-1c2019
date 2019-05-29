#include "cache.h"

void create_cache(cache_t *cache){
    for (int i=0; i<NUMBER_OF_SETS; i++) {
        create_set(cache->sets[i]);
    }
}

void destroy_cache(cache_t *cache) {
    for (int i=0; i<NUMBER_OF_SETS; i++) {
        destroy_set(cache->sets[i]);
    }
}

void init() {

}

unsigned int get_offset (unsigned int address) {
    return 0;
}

unsigned int find_set(unsigned int address) {
    return 0;
}

unsigned int select_oldest(unsigned int setnum) {
    return 0;
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
