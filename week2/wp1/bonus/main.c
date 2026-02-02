// This is the bonus assignment of work package 1.
// The task is cited down below. This was really challenging!

// Task:
//Write a program that counts the number of 0s and 1s in the binary representation of a decimal number. 

//Your program should take a decimal number as argument. Then it should print the decimal number, its binary representation and then count the number of 0s and 1s.

//In this task, you must use bit operations. You are not allowed to convert the number to strings or arrays of any sort. Leading //0s should not be counted (e.g., 0b0011 should return "Number of 0s: 0; Number of 1s: 2"). 

//Please remember that the program should handle errors:
//When the argument is empty
//When the argument is not a number (e.g., 0x11)

#include <stdio.h> // Standard input/output library
#include <string.h> // for strcat
#include <stdbool.h> // for bool
#include <stdlib.h> // for atoi() - ASCII to integer
#include <ctype.h> // for isDigit and other character functions

// bit definitions, note how they are just shifted to the left every time.
#define bit1 1; //0b1 0x1
#define bit2 2; //0b10 0x2
#define bit3 4; //0b100 0x4
#define bit4 8; //0b1000 0x8
#define bit5 16;//0b10000 0x10
#define bit6 32;//0b100000 0x20
#define bit7 64;//0b1000000 0x40
#define bit8 128; //0b10000000 0x80

// declare signature of isNumeric function
bool isNumeric(char* s);

// main function, argument count and argument vector
// argv is a pointer to the first element in an array of pointers 
// all pointing to the first character in an array of characters (CL arguments)
int main(int argc, char * argv[]) {
    // if argument count is not 2 or the string argument is not numeric
    if (argc != 2) {
        puts("Error: No number provided. Please provide a number as a command line argument.");
        return 0;
    } else if ((!isNumeric(argv[1]))) {
        puts("Error: Invalid number.");
    }
    // Get the command line argument
    int iNumber = atoi(argv[1]);
    // initialize a string to manually build the binary
    char sBinary[sizeof(iNumber)*8+1] = "";
    // Flag for whether we've found the leading one or not
    bool bFoundLeadingOne = 0;
    // Counter: 1's
    int iOnes = 0;
    // Counter: 0's
    int iZeroes = 0;

    // Repeat for every bit in the integer
    for (int i = sizeof(iNumber) * 8 - 1; i >= 0; i--) {
        // If the ith bit is 1:
        if ( (iNumber & (1 << i) ) == (1 << i) ) { // 0b000000001
            // Extend the string with a 1
            strcat(sBinary, "1");
            // Change flag to true
            bFoundLeadingOne = 1;
            // Increment 1's counter
            iOnes++;
        // If the ith bit is 0 and we have found the leading 1
        } else if (bFoundLeadingOne) {
            // Extend the string with a 0
            strcat(sBinary, "0");
            // Increment 0's counter
            iZeroes++;
        }
    }
    // Print everything using format string tokens
    printf("Number: %d\nBinary: 0b%s\nNumber of 0s: %d\nNumber of 1s: %d",iNumber, sBinary, iZeroes, iOnes);
}

// This function verifies that a string is numeric
bool isNumeric(char* s) {
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

//Number: 3
//Binary: 0b11
//Number of 0s: 0
//Number of 1s: 2