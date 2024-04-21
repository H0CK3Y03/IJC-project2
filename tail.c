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
void cbuf_put(char **, char *); // puts a line at the end of the buffer
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
        file = stdin;
        if(!strcmp(argv[1], "-n")) {
            char *endptr;
            line_count = strtol(argv[2], &endptr, 10);
            if(endptr == argv[2]) { // checks if the conversion was successful
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
            char *endptr;
            line_count = strtol(argv[2], &endptr, 10);

            if(endptr == argv[2]) { // checks if the conversion was successful
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
            char *endptr;
            line_count = strtol(argv[3], &endptr, 10);

            if(endptr == argv[3]) { // checks if the conversion was successful
            // endPtr should be a null terminator '\0' after a successful conversion
                fprintf(stderr, "Error: Wrong number value.\n");
                return 1;
            }

            if(line_count < 0) {
                line_count *= -1;
            }

            file = fopen(argv[1], "r");
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

    if(line_count == 0) {
        if(file != NULL) {
            fclose(file);
        }
        return 0;
    }

    // if LINE_SIZE is 1, then don't print anything, 1 is only enough space for the null terminator '\n'
    if(LINE_SIZE == 1) {
        if(file != NULL) {
            fclose(file);
        }
        return 0;
    }

    // if the buffer size is bigger than allowed
    if(line_count > BUFFER_SIZE) {
        line_count = BUFFER_SIZE;
        fprintf(stderr, "Warning: Buffer size is bigger than the max allowed size.\n");
        fprintf(stderr, "Warning: Buffer size is now set to the max allowed size.\n");
    }

    // circular buffer creation
    char **cb = cbuf_create(line_count);
    
    // circular buffer implementation
    char *line = malloc(LINE_SIZE * sizeof(char)); // current line
    if(line == NULL) {
        fprintf(stderr, "Error: Failed to allocate memory for the current line");
        return 1;
    }
    int overflow_flag = 0; // a flag that determines whether a line is bigger than allowed
    // reads entire file/stdin
    while(fgets(line, LINE_SIZE, file) != NULL) {
        cbuf_put(cb, line);
        // printf("%ld\n", strlen(line));

        // if current line is longer than is allowed
        if((strlen(line) == (LINE_SIZE - 1)) && (line[strlen(line) - 1] != '\n')) {
            // LINE_SIZE - 1 to accomadate for the null terminator '\0'
            if(!overflow_flag) {
                fprintf(stderr, "Warning: Line is bigger than the max allowed size.\n");
                overflow_flag = 1;
            }
            while((fgets(line, LINE_SIZE, file) != NULL) && (line[strlen(line) - 1] != '\n')) {
                // reads the rest of the line if the line is bigger than the max allowed size
                ;                
            }
        }
    }

    // prints the circular buffer
    for(int i = 0; i < line_count; i++) {
        printf("%s", cbuf_get(cb));
    }

    // circular buffer free
    free(line);
    cbuf_free(cb);
    if(file != NULL) {
        fclose(file);
    }

    return 0;
}

char **cbuf_create(int n) { // n -> number of lines in the circular buffer
    char **cb = NULL;
    cb = malloc(n * sizeof(char*));
    if(cb == NULL) {
        fprintf(stderr, "Error: Memory allocation for circular buffer failed.\n");
        exit(EXIT_FAILURE);
    }
    for(int i = 0; i < n; i++) {
        cb[i] = malloc(LINE_SIZE * sizeof(char));
        if(cb[i] == NULL) {
            fprintf(stderr, "Error: Memory allocation for circular buffer failed.\n");
            exit(EXIT_FAILURE);
        }
    }
    return cb;
}

void cbuf_put(char **cb, char *line) {
    strcpy(cb[end_index], line);
    // moves the start index to the oldest item in the circular buffer
    if(start_index == end_index && cb[start_index + 1] != "") {
        start_index++;
        start_index %= line_count;
    }
    end_index++;
    end_index %= line_count;
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
    for(int i = 0; i < line_count; i++) {
        free(cb[i]);
    }
    free(cb);
}