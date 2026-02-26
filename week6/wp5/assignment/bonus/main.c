// The program should take 5 numbers as input. 
// These numbers should fit in one byte as follows: 1st: 1bit, 2nd: 3bits, 3rd: 2bits, 4th: 1bit, 5th: 1bit. 
// The output should be the byte converted to hexadecimal.

#include <ctype.h>  // isdigit
#include <stdio.h>  // std i/o library

// Macros for booleans
#define true 1;
#define false 0;

int ctoi(char c);   // Converts a char to an int
int isNumeric(char* s); // Checks that a string is numeric
int combinationValid(char** argv);  // Checks that bit combination is valid
int allLengthEqualOne(char** argv);  // Checks if any of the arguments have length > 1
int length(char* s); // Get string length

int main(int argc, char** argv) {
    if (argc != 6) {   // Check if we have 5 numbers
        printf("invalid\n");    // error message enforced by codegrade, suboptimal
        return 0;
    }

    unsigned char byte = 0; // Initialize byte to 0

    for (int i = 1; i < argc; i++) {    // For all 5 args
        if (!isNumeric(argv[i])) {  // Verify they are numeric
            return 0;
        }
    }

    if (!combinationValid(argv)) {  // Check if bit combination is invalid for "elevator"
        printf("invalid"); // error message enforced by codegrade, suboptimal
        return 0;
    }
    byte = byte | ctoi(*argv[1]) << 7;    // Bitwise OR to add value to byte
    byte = byte | ctoi(*argv[2]) << 4;    // Bitwise OR to add value to byte
    byte = byte | ctoi(*argv[3]) << 2;    // Bitwise OR to add value to byte
    byte = byte | ctoi(*argv[4]) << 1;    // Bitwise OR to add value to byte
    byte = byte | ctoi(*argv[5]);    // Bitwise OR to add value to byte


    printf("0x%X", byte);   // Print hexadecimal string

    return 0;
}

// Check all chars are numeric in string
int isNumeric(char* s) {
    while(*s != '\0') { // While we have not encountered null terminator
        if (!isdigit(*s)) { // if character at current dereferenced pointer is not a digit
            return false;
        }
        s++;    // Increment pointer
    }
    return true;
}

int ctoi(char c) {
    return c - '0'; // Convert char to int
}

// Check valid bit combination for elevator
int combinationValid(char** argv) {
    // Check arguments are not too long
    if (!allLengthEqualOne(argv)) {
        return false;
    }
    // Check arguments are not too great
    if (*argv[1] > '1' || *argv[2] > '7' || *argv[3] > '3' || *argv[4] > '1' || *argv[5] > '1') {
        return false;
    }
    return true;
}

// check that all strings length is one
int allLengthEqualOne(char** argv) {
    for (int i = 1; i < 6; i++) {   // For each argument
        if (length(argv[i]) != 1) { // if length of string is not 1
            return false;
        }
    }
    return true;
}

// gets string length
int length(char* s) {
    int len = 0;    // initialize len to 0
    while(*s != '\0') { // as long as we dont reach null pointer
        len++;  // increment len
        s++;    // move pointer
    }
    return len;
}