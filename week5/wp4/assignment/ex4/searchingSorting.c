// (C) Aisha Attar, Vijaykrishnan Gopalakrishnan, Ville Vikingsson, group: 25 (2026)
// Work package 4
// Exercise 1
// Submission code: sCnaU7

#include <stdio.h>

int search_number(int number, int tab[], int size); // O(n) search
void swap(int* p, int* q);  // Swaps two integers
void sort (int number, int tab []); // O(n^2) sort

// Main function
int main(void) {
    int test[] = {1,2,34,5,67,3,23,12,13,10};   // initialize test array

    int i = search_number(67, test, sizeof(test) / sizeof(int));    // search for 67
    printf("%d\n", i);

    sort(sizeof(test) / sizeof(test[0]), test); // sort test

    for (int i = 0; i < sizeof(test) / sizeof(int); i++) {  // print all elements
        printf("%d, ", test[i]);
    }
}

// search number in array
int search_number(int number, int tab[], int size) {
    for (int i = 0; i < size; i++) {    // iterate
        if (tab[i] == number) { // if found
            return i;   
        }
    }

    return -1;
}

// sort array slowly
void sort(int number, int arr[]) {
    for (int i = 0; i<number-1; i++) {  // for almost each number
        int smallest = i;   // initializze smallest idx
        for (int j = i+1; j<number; j++) {  // for each number > i
            if (arr[j] < arr[smallest]) {   // if current number smaller than smallest
                smallest = j;   // new smallest
            }
        }
        swap(&arr[i], &arr[smallest]);  // swap them
    }
}

// Swaps two int pointers
void swap(int* p, int* q) {
    int temp = *p;  // temp variable
    *p = *q;        // swap
    *q = temp;      // swap
}