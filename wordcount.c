#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_WORD_LENGTH 256

typedef struct {
    char *word;
    int count;
} WordCount;

char *my_strdup(const char *str) {
    size_t len = strlen(str) + 1;
    char *dup = malloc(len);
    if (dup != NULL) {
        strcpy(dup, str);
    }
    return dup;
}

void incrementWordCount(WordCount *wordCounts, int *numWords, char *word) {
    int i;
    for (i = 0; i < *numWords; i++) {
        if (strcmp(wordCounts[i].word, word) == 0) {
            wordCounts[i].count++;
            return;
        }
    }
    wordCounts[*numWords].word = my_strdup(word);
    wordCounts[*numWords].count = 1;
    (*numWords)++;
}

int main() {
    WordCount *wordCounts = malloc(sizeof(WordCount) * MAX_WORD_LENGTH);
    if (wordCounts == NULL) {
        fprintf(stderr, "Chyba při alokaci paměti.\n");
        return 1;
    }
    int numWords = 0;
    char word[MAX_WORD_LENGTH];

    while (scanf(" %s", word) != EOF) {
        incrementWordCount(wordCounts, &numWords, word);
    }

    int i;
    for (i = 0; i < numWords; i++) {
        printf("%s\t%d\n", wordCounts[i].word, wordCounts[i].count);
        free(wordCounts[i].word);
    }
    free(wordCounts);

    return 0;
}