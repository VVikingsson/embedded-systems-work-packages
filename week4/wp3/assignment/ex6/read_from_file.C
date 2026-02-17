#include <stdio.h>  // Std i/o library
#include <string.h> // String library

#define SIZE 20 // Set size 20

// Copies a string from from to to.
void copy_string(char* from, char* to);

int main(void) {
    char str[SIZE + 1]; // Declare str
    str[SIZE] = '\0';   // Set null terminator

    fgets(str, SIZE+1, stdin);  // Get input

    char first_copy[SIZE + 1];  // Declare string
    strcpy(first_copy, str);    // Declare string
    char second_copy[SIZE + 1]; // Declare string
    copy_string(str, second_copy);  // Copies str to second_copy.
    printf("Original string: %s\n", str);
    printf("strcpy copy: %s\n", first_copy);
    printf("Own imp. copy: %s", second_copy);
}


void copy_string(char* from, char* to) {
    while (*from != '\0') { // While not pointing at null terminator
        *to = *from;    // Copy value
        to++;   // Increment pointer
        from++; // Increment pointer
    }
    *to = '\0'; // Add null terminator
}