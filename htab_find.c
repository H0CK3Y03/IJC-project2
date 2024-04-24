// Adam Veselý | xvesela00
// VUT Fakulta Informačných Technológii
// 2. príklad | htab_find.c
// 22.04.2024

#include <string.h>
#include "htab.h"
#include "htab_opaque.h"

htab_pair_t *htab_find(const htab_t *t, htab_key_t key) {
    if(t == NULL || key == NULL) {
        return NULL;
    }

    // Find the index of the key in the hash table
    size_t index = (htab_hash_function(key) % t -> arr_size);
    htab_item_t *item = t -> arr[index];

    while(item != NULL) {
        // If the key is found, return the pointer to the pair
        if(!strcmp((item -> pair).key, key)) {
            // Return the pointer to the pair
            return &(item -> pair);
        }

        // Go to the next item in the list if key is not found at this index
        item = item -> next;
    }
    // If there is no such key in the hash table
    return NULL;
}