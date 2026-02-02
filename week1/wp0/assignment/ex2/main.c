// (C) Aisha Attar, Vijaykrishnan Gopalakrishnan, Ville Vikingsson, group: 25 (2026)
// Work package 0
// Exercise 3
// Submission code: 569045 (provided by your TA-s)

#include <stdio.h>  // Import standard i/o library

// Main function, the entry-point of the program.
// argc == argument count and argv == argument vector. 
// argv is an array of pointers all pointing to the first character in some array of characters.
int main (int argc, char* argv[]) {
    if (argc == 2) {
        printf("Hello World! - I'm %s\n", argv[1]); // String token replaced with CL argument
    }
}