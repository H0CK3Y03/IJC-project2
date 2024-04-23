// Adam Veselý | xvesela00
// VUT Fakulta Informačných Technológii
// 2. príklad | htab_for_each.c
// 22.04.2024

#include "htab.h"
#include "htab_opaque.h"

void htab_for_each(const htab_t *t, void (*f)(htab_pair_t *data)) {
    // Check the passed in arguments
    if(t == NULL || f == NULL) {
        return;
    }
    
    // create an item pointer to help iterate through all items
    htab_item_t *item;
    // iterates through all items
    for(size_t i = 0; i < (t -> arr_size); i++) {
        item = (t -> arr[i]);

        while(item != NULL) {
            // call the function on the pair pointer
            f(&(item -> pair));

            // move to the next item
            item = item -> next;
        }
    }
}

