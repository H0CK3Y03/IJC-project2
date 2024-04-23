// Adam Veselý | xvesela00
// VUT Fakulta Informačných Technológii
// 2. príklad | htab_find.c
// 22.04.2024

#include "htab.h"
#include "htab_opaque.h"

htab_pair_t *htab_lookup_add(htab_t *t, htab_key_t key) {
    // find key in hash table
    htab_pair_t *pair = htab_find(t, key);
    if(pair != NULL) {
        return pair;
    }

    // if key is not in hash table, add it
    // find index of key
    size_t index = (htab_hash_function(key) % t -> arr_size);
    // create new pair
    htab_pair_t *new_pair = malloc(sizeof(htab_pair_t));
    if(new_pair == NULL) {
        return NULL;
    }
    // set key and value
    new_pair -> key = key;
    new_pair -> value = 0;

    // create new item
    htab_item_t *item = malloc(sizeof(htab_item_t));
    if(item == NULL) {
        free(new_pair);
        return NULL;
    }
    // initialize item
    item -> pair = *(new_pair);
    item -> next = NULL;

    // temporary pointer to htab_item_t to help find the end of the list
    if(t -> arr[index] == NULL) {
        t -> arr[index] = item;
        return new_pair;
    }
    else {
        htab_item_t *temp = t -> arr[index];

        // add to hash table
        while((temp -> next) != NULL) {
            temp = temp -> next;    
        }
        // add item to end of list
        temp -> next = item;        
        // increment size
        t -> size++;
    }
    // return the new pair
    return new_pair;
}