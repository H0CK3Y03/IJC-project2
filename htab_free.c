// Adam Veselý | xvesela00
// VUT Fakulta Informačných Technológii
// 2. príklad | htab_free.0
// 22.04.2024

#include <stdlib.h>
#include "htab.h"
#include "htab_opaque.h"

void htab_free(htab_t *t) {
    if(t == NULL) {
        return;
    }
    // free all items and their keys
    htab_clear(t);
    // free the array of pointers
    free(t -> arr);
    // free the table itself
    free(t);
}