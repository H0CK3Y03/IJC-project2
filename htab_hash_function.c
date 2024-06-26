// Adam Veselý | xvesela00
// VUT Fakulta Informačných Technológii
// 2. príklad | htab_hash_function.c
// 22.04.2024

// #include "htab.h"
#include <stdlib.h> // for size_t
#include <stdint.h> // for uint32_t

size_t htab_hash_function(const char *str) {
    uint32_t h=0;     // musí mít 32 bitů
    const unsigned char *p;
    for(p=(const unsigned char*)str; *p!='\0'; p++)
        h = 65599*h + *p;
    return h;
}