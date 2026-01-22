// This is the second bonus assignment from the first work package

// Imports
#include <stdio.h> // Standard i/o library
#include <string.h> // string library


// main signature, argument count and an argument vector.
// argv is a pointer to the first element in an array of pointers all pointing to the first char in an array of chars ( "string" )
int main(int argc, char **argv) {
    // Check if there was a CL argument provided
    if (argc == 1) {
        printf("No command line argument provided, please provide a name. ");
    // If an argument was provided, check if it's longer than 50 chars
    } else if (strlen(argv[1]) > 50) {
        printf("Name too long, max 50 characters");
    // If an argument was provided and it is shorter than 51 chars, check if it's shorter than 3 chars.
    } else if (strlen(argv[1]) < 3) {
        printf("Name too short, min 3 characters");
    } else {
        printf("Hello %s, how is your day today?", argv[1]);
    }

    return 0;
}