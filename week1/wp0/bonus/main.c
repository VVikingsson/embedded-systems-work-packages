// This is the first bonus point WP of embedded systems.
// This file is overly commented and engineered for learning purposes.
// https://www.geeksforgeeks.org/c/structure-of-c-program/
// Geeks for geeks was referenced to understand the structure of a typical C file

// ------------ Preprocessor part of the code -----------------
// Preprocessor directives start with "#" (geeksforgeeks)
#include <stdio.h> // Standard input/output library
#include <stdlib.h> // Standard library. Contains many utility functions.
#include <time.h> // Well, time library. Contains time-related stuff.

// Define constants
// Anytime GREETING is referenced, it is replaced with the literal followed by it on the next line.
#define GREETING "hello world"

// ------------- Global declarations --------------------
void greet(); // Unless we declare greet() before main, main will not know about its existence.

// In C, there is no native string type. Instead, we can define an array of characters as below.
char greeting[] = "hello world";
// Another option would be to use a pointer to the first char in the "string".
// This creates a string literal (read only).
char *other_greeting = "hello world";

// ------------ Main program (access point) ---------------------------
int main() {
    // Initialize the randomizer with the current time as seed
    srand(time(NULL)); 
    // Call greet function
    greet();
    return 0; // return 0 indicating successful execution of the program
}

// ----------- sub-programs -----------------------------
void greet() {
    int num = rand() % 4; // Generate a random number in [1, 4)

    // This is of course a block of if and else statements. I hope no further comments are necessary about them.
    if (num == 1) {
        printf(GREETING);
        
    } else if (num == 2) {
        printf("%s", greeting); // printf takes a format string, which can include tokens to be replaced by optional arguments.
    } else {
        printf(other_greeting);
    }
}