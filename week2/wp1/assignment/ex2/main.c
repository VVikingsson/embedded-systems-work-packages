// This is the second exercise of Work Package 1. 
// The task is to create a simple encryption program. 
// The program should take any string as input and ouput the encrypted result until the user enters EOF.
// Encryption is simple moving the letters 13 steps "up" in ASCII values.
// Unfortunately, the specification on Canvas provides no instructions on what will happen when an input
// contains a character less than 13 steps away from 255, the upper limit to ASCII. I will assume we should wrap around.

#include <stdio.h> // Standard i/o library
#include <stdlib.h>// Standard library
#include <ctype.h> // char library

#define STRING_SIZE 31 // define constant for size of string
#define ALPHABET_SIZE 26

void printEncryptedString(char* s, int toShift); // declare function signatures
int isNumeric(char* s);

// main function, takes argument count and argument vector, a pointer to the first pointer in
// an array of pointers all pointing to the first character in an array of characters. (2D array)
int main(int argc, char** argv) {
    // Check argc == 2
    if (argc != 2) {
        // print error message
        puts("Error: Must provide one argument");
        // return unsuccessful
        return 1;
        // check argument is numeric
    } else if (!isNumeric(argv[1])) {
        // print error message
        puts("Error: argument must be integer");
        // return unsuccessful
        return 1;
    }

    // Cast argument to int
    int toShift = atoi(argv[1]);
    // Allocate memory for input
    char* sInput = (char*) malloc(STRING_SIZE);

    // Get input as long as it is not EOF (ctrl+Z on windows)
    while (fgets(sInput, STRING_SIZE, stdin) != NULL) {
        // Call function with two arguments
        printEncryptedString(sInput, toShift);
    }

    // Print "Bye"
    puts("Bye");
    // Return successful
    return 0;
}

// Takes a character pointer (string) and shifts the whole string in the ascii table by toShift characters up.
// Assumes that s contains only upper case letters
void printEncryptedString(char* s, int toShift) {
    // While s is not pointing to \0 null terminator
    while(*s) {
        // Shift the character and have it wrap around. Only works for upper case.
        // 1. Normalize the range back to starting from 0
        // 2. Apply modulo in normalized range
        // 3. Add 'A' afterward to shift resulting value back up to original range
        // Check tp handle uppercase and avoid \n
        if (*s >= 'A' && *s <= 'Z') {
            // print
            printf("%c", (*s + toShift - 'A') % ('Z' + 1 - 'A') + 'A'); // or (*s + toShift - 65) % 26 + 65
            // check to handle lower case and avoid \n
        } else if (*s >= 'a' && *s <= 'z') {
            // print
            printf("%c", (*s + toShift - 'a') % ('z' + 1 - 'a') + 'a'); // or (*s + toShift - 97) % 26 + 97
            // Another case for digits
        } else if (*s >= '0' && *s <= '9') {
            // print
            printf("%c", (*s + toShift - '0') % 10 + '0'); // Note that it is '0', not 0.
            // In codegrade, the dash has special treatment. That is the reason for this case.
        } else if (*s == '-') {
            // print
            printf("%c", '-');
        }
        s++; // Move pointer to next char in the string
    }
    puts(""); // new line for readability
}

// This function verifies that a string is numeric
int isNumeric(char* s) {
    // While s has not reached the null terminator
    while (*s) {
        // If the the value s points to (dereferencing) is not a digit
        if (!isdigit(*s)) {
            return 0; // return false
        }
        s++; // move s sizeof(char), effectively pointing to the next char in the string
    }
    return 1; // return true
}