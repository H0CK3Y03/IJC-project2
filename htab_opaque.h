// Adam Veselý | xvesela00
// VUT Fakulta Informačných Technológii
// 2. príklad | htab_opaque.h
// 22.04.2024

#ifndef HTAB_OPAQUE_H
#define HTAB_OPAQUE_H

#include "htab.h"

typedef struct htab_item {
    htab_pair_t pair;
    struct htab_item *next;
} htab_item_t;

struct htab {
    size_t size;
    size_t arr_size;
    htab_item_t **arr; // points to [pair, next] <==> [(key, value), next]
};

#endif // HTAB_OPAQUE_H