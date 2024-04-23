// Adam Veselý | xvesela00
// VUT Fakulta Informačných Technológii
// 2. príklad | htab_bucket_count.c
// 22.04.2024

#include "htab.h"
#include "htab_opaque.h"

size_t htab_bucket_count(const htab_t *t) {
    if(t == NULL) {
        return 0;
    }
    // return number of items in the table array
    return t -> arr_size;
}