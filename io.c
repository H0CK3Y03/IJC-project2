// Adam Veselý | xvesela00
// VUT Fakulta Informačných Technológii
// 2. príklad | io.c
// 23.04.2024

#include <stdio.h>
#include <stdbool.h>
#include <ctype.h>

 int read_word(char *s, int max, FILE *f) {
    if(max == 0) {
        s[0] = '\0';
        return max;
    }
    // the current amount of characters in the string
    int count = 0;
    char c;
    bool reached_max = false;
    // if the user has already been warned about the overflow
    static bool warned = false;

    // if char is a whiteline, skip
    while(((c = getc(f)) != EOF) && isspace(c)) {
        continue;
    }
    // if char is EOF and string is empty, return EOF
    if(c == EOF) {
        return c;
    }

    // if char is not EOF or whiteline, put it into array
    s[0] = c;
    count++;

    while(((c = getc(f)) != EOF) && !isspace(c)) {
        // if the string is full
        if(count >= max) {
            reached_max = true;
            // at the end of the string we put the null terminator
            s[count] = '\0';
            break;
        }

        s[count] = c;
        count++;
    }

    if(reached_max && !warned) {
        fprintf(stderr, "Warning: String overflow detected!\n");
        // to print a waning only once
        // warned is a static variable, that means it will be the same for all the functions
        warned = true;
        return max;
    }

    return count;
 }