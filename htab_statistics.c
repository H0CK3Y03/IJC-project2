// Adam Veselý | xvesela00
// VUT Fakulta Informačných Technológii
// 2. príklad | htab_statistics.c
// 22.04.2024

#include <stdio.h>
#include "htab.h"
#include "htab_opaque.h"

void htab_statistics(const htab_t *t) {
    if(t == NULL)  {
        fprintf(stderr, "(0, 0, 0)");
        return;
    }
    size_t min = 0;
    size_t max = 0;
    double avg = 0.0;
    // we create a variable to count the number of items in a bucket
    size_t count;
    // we create a variable to count the total number of items in the table
    size_t total_count = 0;
    // we create a variable to count the number of non-empty buckets
    size_t non_empty_bucket_count = 0;

    // we create an item to iterate through all items in a bucket
    htab_item_t *item;

    // iterates through all buckets
    for(size_t i = 0; i < t -> arr_size; i++) {
        item = t -> arr[i];
        // if the bucket is empty, we skip it
        if(item == NULL) {
            continue;
        }
        // if the bucket is not empty, we count it
        non_empty_bucket_count++;

        count = 0;
        // iterates through all items in a bucket
        while(item != NULL) {
            count++;
            item = item -> next;
        }

        if(min > count) {
            min = count;
        }
        if(max < count) {
            max = count;
        }
        total_count += count;
    }
    // finds the average amount of items in a list
    avg = (double) total_count / non_empty_bucket_count;
    // prints the statistics to stderr
    fprintf(stderr, "(%ld, %ld, %lf)\n", min, max, avg);
}
