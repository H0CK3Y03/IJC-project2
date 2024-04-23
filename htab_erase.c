// Adam Veselý | xvesela00
// VUT Fakulta Informačných Technológii
// 2. príklad | htab_erase.c
// 22.04.2024

#include "htab.h"
#include "htab_opaque.h"

bool htab_erase(htab_t *t, htab_key_t key) {
    htab_pair_t *pair = htab_find(t, key);
    // pair == NULL means that the key is not in the table, therfore we return false
    if (pair == NULL) {
        return false;
    }

    size_t index = (htab_hash_function(key) % t -> arr_size);
    // stores the item at index for further use
    htab_item_t *item = t -> arr[index];
    // to save the last position if the key is not found at the beginning
    htab_item_t *prev_item = NULL;

    while(item != NULL) {
        if(!strcmp((item -> pair).key, key)) {
            // if the item is the first index
            if(prev_item == NULL) {
                // redirect the pointer to the next item
                t -> arr[index] = item -> next;
            }
            else {
                // if the item is not the first index
                // move the pointer to before the end of the list
                while((item -> next) != NULL) {
                    item = item -> next;
                }
                // redirect the pointer to the next item (skip the current item)
                prev_item -> next = item -> next;
            }

            // free the memory
            free((item -> pair).key);
            free(item -> pair);
            free(item);

            // decrement the size of the hash table
            t -> size--;

            // return success
            return true;
        }

        // move the pointers forward (towards the end of the hash table)
        prev_item = item;
        item = item -> next;
    }

    // return failure if we don't find/free anything
    return false;
}