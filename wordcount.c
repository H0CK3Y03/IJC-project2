// Adam Veselý | xvesela00
// VUT Fakulta Informačných Technológii
// 2. príklad | wordcount.c
// 20.04.2024

// Použijte: gcc -O2
// Program počítá četnost slov ve vstupním textu,
// slovo je cokoli oddělené "bílým znakem"

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAX_WORD_LENGTH 333

struct Word *word_ctor();
void word_dtor(struct Word *, int);
void word_check(struct Word **, char *, int *);
struct Word *add_word(struct Word **, char *, int *);

// Struktura pro uložení slova a počtu jeho výskytů
struct Word {
    char *string;
    int count;
};

int main() {
    struct Word *words = word_ctor();
    int word_count = 0; // number of different words
    // allocating memory for the string from stdin
    char *cur_string = malloc(sizeof(char) * MAX_WORD_LENGTH);
    if(cur_string == NULL) {
        fprintf(stderr, "Error: Unable to store string.\n");
        return 1;
    }
    // stdin handling
    while(scanf("%s", cur_string) != EOF) {
        if((strlen(cur_string) == 0) && (word_count == 0)) {
            return 0;
        }
        word_check(&words, cur_string, &word_count);
    }
    // printing words and their counts
    for(int i = 0; i < word_count; i++) {
        printf("%s %d\n", words[i].string, words[i].count);
    }
    // freeing memory
    free(cur_string);
    word_dtor(words, word_count);

    return 0;
}

struct Word *word_ctor() {
    // initial allocation of memory for the structure Word
    struct Word *words = malloc(sizeof(struct Word));
    if(words == NULL) {
        fprintf(stderr, "Error: Word memory allocation failed.\n");
        exit(EXIT_FAILURE);
    }
    return words;
}

void word_dtor(struct Word *words, int word_count) {
    for(int i = 0; i < word_count; i++) {
        free(words[i].string);
    }
    free(words);
}

void word_check(struct Word **words, char *cur_string, int *word_count) {
    // iterates through all existing words
    for(int i = 0; i < (*word_count); i++) {
        if(strcmp((*words)[i].string, cur_string) == 0) {
            // increments the count of the word if it already exists
            (*words)[i].count++;
            return;
        }

    }
    // if the word does not exist, it is added to the array of words
    *words = add_word(words, cur_string, word_count);
}

struct Word *add_word(struct Word **words, char *cur_string, int *word_count) {
    (*word_count)++;
    // allocates memory for the new word
    struct Word *new_words = realloc(*words, (sizeof(struct Word) * (*word_count)));
    if(new_words == NULL) {
        fprintf(stderr, "Error: Unable to allocate memory for new word.\n");
        exit(1);
    }

    // allocates memory for the string in the new word structure
    new_words[(*word_count) - 1].string = malloc(sizeof(char) * MAX_WORD_LENGTH);
    if(new_words[((*word_count) - 1)].string == NULL) {
        fprintf(stderr, "Error: Unable to reallocate memory for string in new word.\n");
        exit(1);
    }

    // initializes the value to 0 in the structure Word
    new_words[(*word_count) - 1].count = 1;
    // copies the string into the new word structure
    strcpy(new_words[(*word_count) - 1].string, cur_string);
    return new_words;
}