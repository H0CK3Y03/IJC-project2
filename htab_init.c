// Adam Veselý | xvesela00
// VUT Fakulta Informačných Technológii
// 2. príklad | htab_init.c
// 22.04.2024

#include <stdlib.h>
// #include "htab.h"
#include "htab_opaque.h"

htab_t *htab_init(const size_t n) {
    // allocates memory for htab_t
    htab_t *t = malloc(sizeof(htab_t));
    if(t == NULL) {
        return NULL;
    }

    // allocates memory for n htab_item_t pointers
    t -> arr = malloc(sizeof(htab_item_t *) * n);
    if(t -> arr == NULL) {
        free(t);
        return NULL;
    }

    // current array size
    t -> arr_size = n;

    // current number of items in the t
    t -> size = 0;

    // initializes all htab_item pointers to NULL
    for(size_t i = 0; i < n; i++) {
        t -> arr[i] = NULL;
    }

    return t;
}