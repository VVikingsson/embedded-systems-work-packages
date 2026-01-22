// (C) Aisha Attar, Vijaykrishnan Gopalakrishnan, Ville Vikingsson, group: 25 (2026)
// Work package 0
// Exercise 3
// Submission code: XXXXXX (provided by your TA-s)

#include <stdio.h>  // Import standard i/o library
#include <string.h> // Import string library

// Main function, the entry-point of the program.
// argc == argument count and argv == argument vector. 
// argv is an array of pointers all pointing to the first character in some array of characters.
int main (int argc, char* argv[]) {
    if (argc != 2) { // If argc is not 2
        printf("Error: Must provide exactly one command-line argument. Run the program with -h as argument for help.");
        return 1; // Unsuccessful run
    } else if (strcmp(argv[1], "-h") == 0) { // strcmp compares two strings, if they are the identical it returns 0
        printf("Enter your name as the first command-line argument and the program will have you greet the world! Wow.");
    } else { // If argc == 2 and the first CL argument is not "-h"
        printf("Hello World! - I'm %s\n", argv[1]); // String token replaced with CL argument
    }

    return 0; // Successful run
}