// (C) Aisha Attar, Vijaykrishnan Gopalakrishnan, Ville Vikingsson, group: 25 (2026)
// Work package 1
// Exercise 1
// Submission code: xxxxx (provided by your TA-s)

// read 5 different sentences, max 30 chars long

#include <stdio.h> // standard input/output library
#include <stdlib.h> // standard library
#include <string.h> // for strlen

void readSentences(); // declare function signatures before main
void printSentences();
void flushStdin();

// main function, takes argument count and argument vector from CLI.
int main(int argc, char* argv[]) {
    // Allocate memory for 5 pointers, all of which will point to the first character of respective sentence
    char** sentences = (char**) malloc(5 * sizeof(char*));
    // Allocate memory for the 5 strings, 30 characters each (don't forget about null terminator)
    for (int i = 0; i < 5; i++) {
        sentences[i] = (char*) malloc(31 * sizeof(char));
    }
    // Reads 5 sentences from stdin and stores them in sentences
    readSentences(sentences);
    // Prints sentences until the user exits a loop
    printSentences(sentences);
    // Free all allocated memory for the 5 strings
    for (int i = 0; i < 5; i++) free(sentences[i]);
    // Free the allocated memory for the 5 pointers
    free(sentences);
    // Set dangling pointer to null
    sentences = NULL;
    // bye bye
    printf("Exiting program");
    return 0;
}

// This function reads 5 sentences of max length 30 and stores them in the sentences array.
void readSentences(char **sentences) {
    // loop 5 times
    for (int i = 0; i < 5; i++) {
        // Conditionally assign suffix
        char* suffix = i == 0 ? "st" : i == 1 ? "nd" : i == 2 ? "rd" : "th";
        // prompt user
        //printf("Please enter the %d%s sentence\n", i+1, suffix);
        // fgets reads 30 characters from the std in stream and stores them in the address located at sentences[i]
        fgets(sentences[i], 31 * sizeof(char), stdin); 
        // Clear the stdin in case user inputs more than 30 characters.
        if (sentences[i][strlen(sentences[i])-1] != '\n') {
            // Clear the stdin buffer in case user entered more than 30 characters
            flushStdin();
        }
    }
}

void flushStdin() {
    // Declare a character and call it c
    char c;
    // Continually gets characters from stdin, untill there are none to get.
    // Effectively flushes stdin. Thanks stackoverflow: https://stackoverflow.com/a/2187514
    while ((c = getchar()) != '\n' && c != EOF);
}

void printSentences(char **sentences) {
    // Initialize index variable
    int idx = 1;
    // While the user inputs idx to be between 1 and 5:
    while (idx > 0 && idx < 6) {
        // Prompt user for input
        //printf("Please enter a number: ");
        // Scan one number and put it where the address of &idx points
        scanf("%d", &idx);
        // security check to not crash program
        if (idx > 0 && idx < 6) {
            printf("%s", sentences[idx-1]);
        }
    }
}