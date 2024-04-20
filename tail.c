// Adam Veselý | xvesela00
// VUT Fakulta Informačných Technológii
// 1. príklad | tail.c
// 20.04.2024


#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define BUFFER_SIZE 1000000
#define LINE_SIZE 2047

int line_count = 10; // default amount of lines to be printed
int start_index = 0; // index of oldest item in circular buffer
int end_index = 0; // index after newest item in circular buffer

// circular buffer function prototypes
char **cbuf_create(int); // creates the circular buffer
char **cbuf_put(char **, char *); // puts a line at the end of the buffer
char *cbuf_get(char **); // gets a line from the beginning of the buffer
void cbuf_free(char **); // frees the circular buffer
// end of prototypes

int main(int argc, char **argv) {

    FILE *file = NULL;

    // argument handling
    if(argc == 1){
        file = stdin;
    }
    else if(argc == 2) {
        file = fopen(argv[1], "r");
        if(file == NULL) {
            fprintf(stderr, "Error: Unable to open file.\n");
            return 1;
        }
    }
    else if(argc == 3) {
        if(!strcmp(argv[1], "-n")) {
            char *endPtr;
            line_count = strtol(argv[2], &endPtr, 10);

            if(endPtr != '\0') { // checks if the conversion was successful
            // endPtr should be a null terminator '\0' after a successful conversion
                fprintf(stderr, "Error: Wrong number value.\n");
                return 1;
            }

            if(line_count < 0) {
                line_count *= -1;
            }
        }
        else {
            fprintf(stderr, "Error: Wrong usage.\n");
            return 1;
        }
    }
    else if(argc == 4) {
        if(!strcmp(argv[1], "-n")) {
            char *endPtr;
            line_count = strtol(argv[2], &endPtr, 10);

            if(endPtr != '\0') { // checks if the conversion was successful
            // endPtr should be a null terminator '\0' after a successful conversion
                fprintf(stderr, "Error: Wrong number value.\n");
                return 1;
            }

            if(line_count < 0) {
                line_count *= -1;
            }

            file = fopen(argv[3], "r");
            if(file == NULL) {
                fprintf(stderr, "Error: Unable to open file.\n");
                return 1;
            }

        }
        else if(!strcmp(argv[2], "-n")) {
            char *endPtr;
            line_count = strtol(argv[3], &endPtr, 10);

            if(endPtr != '\0') { // checks if the conversion was successful
            // endPtr should be a null terminator '\0' after a successful conversion
                fprintf(stderr, "Error: Wrong number value.\n");
                return 1;
            }

            if(line_count < 0) {
                line_count *= -1;
            }

            file = fopen(argv[3], "r");
            if(file == NULL) {
                fprintf(stderr, "Error: Unable to open file.\n");
                return 1;
            }

        }
        else {
            fprintf(stderr, "Error: Wrong usage.\n");
            return 1;
        }
    }
    else {
        fprintf(stderr, "Error: Wrong amount of arguments.\n");
        return 1;
    }

    // circular buffer creation
    char **cb = cbuf_create(line_count);
    
    // circular buffer implementation
    char c; // current character
    // reads entire file/stdin
    while((c = getc(file)) != EOF) {

        int char_index = 0; // current character index in line
        // reads entire line (ends at newline character)
        while((c = getc(file)) != '\n' && char_index < LINE_SIZE - 2) {
        // LINE_SIZE - 2 because we need space for \0 at the end of the string/line (-1 because we start at 0 and another -1 for null terminator '\0')
        // The null terminator gets added to the end of the string automatically, hence we have no need of adding it there ourselves
            cb[end_index][char_index] = c; // puts the current character at the current index
            char_index++;
        }
        cb[end_index][char_index] = c; // puts \n at the end of the string/line

        // handles the circular buffer indices
        end_index++;
        end_index %= line_count; // to be able to get back to the beginning of the circular buffer
        if(start_index == end_index) { // to move the start index to the oldest item in the circular buffer
            start_index++;
            start_index %= line_count; // to be able to get back to the beginning of the circular buffer
        }
    }

    // prints the circular buffer
    for(int line = 0; line < line_count; line++) {
        printf("%s", cbuf_get(cb));
    }

    // circular buffer free
    cbuf_free(cb);

    return 0;
}

char **cbuf_create(int n) { // n -> number of lines in the circular buffer
    char **cb = malloc(n * LINE_SIZE);
    if(cb == NULL) {
        fprintf(stderr, "Error: Memory allocation for circular buffer failed.\n");
        exit(EXIT_FAILURE);
    }
    return cb;
}

char **cbuf_put(char **cb, char *line) {
    cb[end_index] = line;
    if(!strcmp(cb[end_index], line)) {
        fprintf(stderr, "Error: Failed to put line into circular buffer.\n");
        exit(EXIT_FAILURE);
    }
    end_index++;
    end_index %= line_count;
    return cb;
}

char *cbuf_get(char **cb) {
    if(cb[start_index] == NULL) {
        return "";
    }
    else {
        char *line = cb[start_index];
        start_index++;
        start_index %= line_count; // to be able to get back to the beginning of the circular buffer
        return line;
    }
}

void cbuf_free(char **cb) {
    free(cb);
}