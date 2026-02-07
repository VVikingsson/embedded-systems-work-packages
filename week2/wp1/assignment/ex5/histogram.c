#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#define RANGE_LIMIT 15 // Defines the maximum value for each bin in the histogram
#define ITEMS 20 // Defines the number of items in the table


// ------ Function declarations ----------
// This function generates a set of random numbers
// and fills the table *table with these numbers
void seed_table(int *table );
// This function takes the *table of random numbers
// and creates a table with the frequency counts for these numbers
void count_frequency(int *table, int *freq );
// This function takes the frequency count table
// and draws a histogram of the values in that frequency table
void draw_histogram(int *freq);

// Prints every item in an array
void print_array(int* arr);
// ------ Main --------------------------
// The main entry point for the program
//
// If you choose to go for the optional part
// Please modify it accordingly
int main(void) {
    // Initialize randomizer
    srand(time(NULL));
    int table[ITEMS+1];
    int frequency[RANGE_LIMIT + 1] = {0};

    seed_table(table);
    count_frequency(table, frequency);

    draw_histogram(frequency);
}

// ------ Function definitions ----------
void seed_table(int *table) {
    int* ptr = table;   // For iterating through table
    for (int i = 0; i < ITEMS; i++) {  // While pointer does not point to null terminator
        *ptr = rand() % (RANGE_LIMIT + 1);  // Set every item in the table to a randomm number 1-15
        ptr++;  // Move pointer one int size
    }
}

void print_array(int* arr) {
    int* ptr = arr;
    printf("[");

    for (int i = 0; i < ITEMS; i++) {
        printf("%d, ", *ptr);
        ptr++;
    }
    printf("]");
}
 
void count_frequency(int* table, int* freq) {
    int curr = 0;
    int* iterator = table;
    int* currFreq = freq;

    for (int i = 0; i < ITEMS; i++) {
        int diff = *iterator - curr;
        curr += diff;
        currFreq += diff; // Move to corresponding index in histogram
        *currFreq += 1;
        iterator++;
    }
}

void draw_histogram(int *freq) {
    for (int i = 0; i < RANGE_LIMIT+1; i++) {
        if (*freq > 0) {
            printf("%-3d", i);
            for (int j=0; j<*freq;j++) {
                printf("x");
            }
            printf("\n");
        }
        freq++;
    }
}