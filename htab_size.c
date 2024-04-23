// Adam Veselý | xvesela00
// VUT Fakulta Informačných Technológii
// 2. príklad | htab_size.c
// 22.04.2024

#include "htab.h"
#include "htab_opaque.h"

size_t htab_size(const htab_t *t) {
    if(t == NULL) {
        // returns 0 if the table is NULL
        return 0;
    }

    return t -> size;
}