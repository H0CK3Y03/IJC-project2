// Adam Veselý | xvesela00
// VUT Fakulta Informačných Technológii
// 2. príklad | wordcount.c
// 23.04.2024

#include <stdio.h>
#include <stdlib.h>
#include "htab.h"
#include "io.h"
// #define STATISTICS
#define MAX_WORD_LENGTH 333 // 332 characters + 1 for the null terminator '\0'
#define HASH_TABLE_SIZE 28657
/*
Veľkost hash tabuľky je 28657. Vybral som toto číslo,
pretože priemerný Slovák pozná okolo 20000 slov,
vynásobil som to číslom 1,3 (toto je odporúčané) a dostal som 26000,
potom som hľadal najbližšie prvočíslo, ale rozhodol som sa použiť 28657,
pretože to je 23. čislo z fibonacciho postupnosti,
a zároveň je to 6. prvočíslo z fibonnaciho postupnosti.
Prvočísla sú odporúčané, aby sme zamedzili kolíziam.
*/

// interchangeable hash function
#ifdef MY_HASH_FUN_TEST
// http://www.cse.yorku.ca/~oz/hash.html - varianta djb2):
size_t htab_hash_function(const char* str) {
    unsigned long hash = 5381;
    int c;

    while ((c = *str++))
        hash = ((hash << 5) + hash) + c; /* hash * 33 + c */

    return hash;
}
#endif // MY_HASH_FUN_TEST

// prints all item keys and their values in the hash table
void print_table(htab_pair_t *data) {
    printf("%s %d\n", data->key, data->value);
}

int main() {
    // create the hash table
    htab_t *t = htab_init(HASH_TABLE_SIZE);
    if(t == NULL) {
        fprintf(stderr, "Error: failed to allocate memory for hash table.\n");
        return 1;
    }
    int word_length = 0;
    char word[MAX_WORD_LENGTH] = {0};
        // read words from stdin
    while((word_length = read_word(word, MAX_WORD_LENGTH, stdin)) > 0) {
        // printf("----%s----\n", word);
        // add word to hash table
        htab_pair_t *pair;
        if((pair = htab_lookup_add(t, word)) == NULL) {
            fprintf(stderr, "Error: Unable to add word to hash table.\n");
            htab_free(t);
            return 1;
        }
        // increment value of the word (it's count)
        pair -> value++;
        // clear the word array (otherwise the characters persist in the next iteration)
        for(int i = 0; i < MAX_WORD_LENGTH; i++) {
            word[i] = '\0';
            if(word[i + 1] == '\0') {
                break;
            }
        }
    }

    // print words and their values (all pairs)
    htab_for_each(t, print_table);

    // hash table statistics
    #ifdef STATISTICS
    htab_statistics(t);
    #endif // STATISTICS

    // free memory
    htab_free(t);

    return 0;
}