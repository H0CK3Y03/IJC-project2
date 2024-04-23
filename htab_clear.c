// Adam Veselý | xvesela00
// VUT Fakulta Informačných Technológii
// 2. príklad | htab_clear.c
// 22.04.2024

#include "htab.h"
#include "htab_opaque.h"

void htab_clear(htab_t *t) {
    if(t == NULL) {
        return;
    }
    // create pointers to items to help with iteration/moving to the next item
    htab_item_t *item;
    htab_item_t *next_item;
    for(size_t i = 0; i < (t -> arr_size); i++) {
        // store the current item pointer into item
        item = t -> arr[i];
        // iterate through the linked list that item is pointing to
        while(item != NULL) {
            // points to the next item in the list
            next_item = item -> next;
            // free the item's key
            free(item -> pair.key);
            // free the item
            free(item);

            // set item to the next item in the list
            item = next_item;
            // free the item
        }
    }

    // set the size of the hash table to 0 (clear the size)
    t -> size = 0;
}