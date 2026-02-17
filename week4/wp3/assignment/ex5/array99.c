#include <stdlib.h> // Standard library
#include <time.h>   // Time library
#include <stdio.h> // Std i/o library

#define SIZE 10 // Set size to 10


void fill_array(int* arr);    // Fills array with random numbers 1-99 and gets the last of these values.
void print_all(int* arr);   // prints all numbers and numbers times two

int main(void) {
    srand(time(NULL));
    int arr[SIZE]; // Create array of size SIZE

    fill_array(arr);  // Fill array and get last value
    printf("The value of the address of the array (pointer) is: %p\n", arr);
    printf("The last integer in the array is %d\n", arr[SIZE-1]);
    printf("The size of an integer (number of bytes) is: %d\n", sizeof(int));
    printf("The size of the whole array in bytes is: %zu\n", sizeof(int) * SIZE);   // %zu is the token for size_t, an unsigned
    // int type that is big enough to hold the max size of any object the system can handle.
    print_all(arr); // Print all numbers and all numbers multiplied by two
    return 0;
}

// Fills the array
void fill_array(int* arr) { 
    for (int i = 0; i < SIZE; i++) {    // Go through array
        arr[i] = (rand() % 99) + 1; // Random number 1-99
    }
}

// For each number, print it and it times two.
void print_all(int* arr) {
    for (int i = 0; i < SIZE; i++) {    // FOr each int in the array
        printf("%d, %d\n", *arr, *arr*2);   // Print number and number times two
        arr++;  // Increment pointer
    }   
}