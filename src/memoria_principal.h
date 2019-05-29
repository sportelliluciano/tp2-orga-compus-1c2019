#define CAPACITY (1024*64)
#include <stdio.h>
#include "bloque.h"

struct mp {
    bloque_t **memory;
};

typedef struct mp mp_t;

void create_mp(mp_t* mp);

 