#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int main(int argc, char **argv) {

    FILE *file = NULL;
    int line_count = 10; // default amount of lines to be printed
    // argument handling
    if(argc == 2) {
        file = fopen(argv[1], "r");
        if(file == NULL) {
            fprintf(stderr, "Error: Unable to open file.");
        }
    }
    else if(argc == 1){
        file = stdin;
    }
    else if(argc == 4) {
        if(!strcmp(argv[1], "-n")) {
            char *endPtr;
            line_count = strtol(argv[2], &endPtr, 10);
        }
    }
    else {
        fprintf(stderr, "Error: Wrong amount of arguments.");
    }
    
    // file handling
    char c;
    while((c = getc(file)) != EOF) {
        ;
    }
    return 0;
}