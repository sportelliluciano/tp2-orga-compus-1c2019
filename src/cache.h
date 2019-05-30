#ifndef _CACHE_H_
#define _CACHE_H_
#include <stdio.h>
#include <stdint.h>
#include "conjunto.h"
#include "memoria_principal.h"
#define BLOCK_SIZE 64
#define NUMBER_OF_SETS 8

/**
 * Memoria caché simulada.
 * 
 * Simula un sistema de memoria principal de 64KB con caché asociativa por
 * conjuntoss de 4 vías, 2KB de capacidad, bloques de 64 bytes, política de
 * reemplazo FIFO y política de escritura WT/¬WA.
 * Se asume que el espacio de direcciones es de 16 bits.
 * 
 * La memoria se simula como un singleton, todos los llamados a funciones de
 * este módulo modificarán la misma y única memoria.
 */

struct cache {
    set_t **sets;
    size_t miss;
    size_t hits;
    mp_t *mp;
};

typedef struct cache cache_t;

cache_t *cache;

void create_cache(mp_t *mp);

/**
 * Inicializa la memoria principal simulada en 0, los bloques de caché como
 * inválidos y la tasa de misses a 0.
 * 
 * Llamar a este método nuevamente provocará que se reinicie la memoria al 
 * estado inicial (memoria en 0, bloques inválidos y tasa de misses en 0).
 */
void init();

/**
 * Devuelve el offset del byte del bloque de memoria al que mapea la dirección
 * address.
 */
unsigned int get_offset(unsigned int address);

/**
 * Devuelve el el via de caché al que mapea la dirección address.
 */
unsigned int find_set(unsigned int address);

/**
 * Devuelve la vı́a en la que está el bloque más "viejo" dentro de un conjunto, 
 * utilizando el campo correspondiente de los metadatos de los bloques del 
 * conjunto.
 */
unsigned int select_oldest(unsigned int setnum);

/**
 * Lee el bloque blocknum de memoria y lo guarda en el conjunto y vı́a indicados 
 * en la memoria caché.
 */
void read_tocache(unsigned int blocknum, unsigned int way, unsigned int set);

/**
 */
void write_tocache(unsigned int address, unsigned char c);

/**
 * Busca el valor del byte correspondiente a la posición address en la caché; 
 * si éste no se encuentra en la caché carga ese bloque. 
 * 
 * Devuelve el valor del byte almacenado en la dirección indicada.
 */
unsigned char read_byte(unsigned int address);

/**
 * Escribe el valor value en la posición address de la memoria, y en la posición
 * correcta del bloque que corresponde a address, si el bloque se encuentra en 
 * la caché. 
 * Si no se encuentra, escribe el valor solamente en la memoria.
 */
void write_byte(unsigned int address, unsigned char value);

/**
 * Devuelve el porcentaje de misses desde que se inicializó la caché.
 */
float get_miss_rate();

void destroy_cache();


#endif // _CACHE_H_
