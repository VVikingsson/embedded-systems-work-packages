#include <ctype.h> // For isdigit()
#include <stdio.h> // std i/o library
#include <stdlib.h> // For malloc

#define TRUE 1  // Constant for semantics
#define FALSE 0 // Constant for semantics

int is_numeric(char* s);    // Checks that a string is numeric
char* byte_to_hexadec(unsigned char byte);
int char_to_int(char* c);

// Main function
int main(int argc, char** argv) {
    // Error handling
    if (argc != 6) {    // Number of arguments provided is not 6
        printf("Number of arguments must be 5.");
        return 0;
    } else {    // Number of arguments provided is 6
        char** ptr = argv + 1;  // Copy argv ptr to iterate
        while (*ptr != NULL) {  // For all CL arguments
            if (!is_numeric(*ptr)) {    // Check string is numeric
                printf("Arguments must be numeric.");   
                return 0;   // Return fail
            }
            ptr++;  // Increment pointer
        }
    }

    int args[5];    // Declare array of int args
    unsigned char byte = 0b00000000; // Declare byte

    for (int i = 1; i<=5; i++) {    // for i 1-5
        args[i-1] = char_to_int(argv[i]);  // populate args
    }

    // Add args to byte, shift them all according to specification
    byte += args[0] << 7;   // Shift 7 steps
    byte += args[1] << 4;   // Shift 4 steps
    byte += args[2] << 2;   // Shift 2 steps
    byte += args[3] << 1;   // Shift 1 step
    byte += args[4];        // Shift 0 steps, already correct

    char* hexadec = byte_to_hexadec(byte);
    printf("%s", hexadec);
    free(hexadec);
    hexadec = NULL;
}


// Checks a string is made up of digits
int is_numeric(char* s) {
    while(*s != '\0') { // For every character in the string, until null terminator
        if (!isdigit(*s)) return FALSE; // if it is not digit, return false
        s++;    // Increment pointer
    }
    return TRUE;    // Return true
}

// Simple char to int conversion
int char_to_int(char* c) {
    return *c - '0';    // ASCII arithmetic
}

char* byte_to_hexadec(unsigned char byte) {
    char* hexadec = malloc(3); // Declare char array with room for null term.
    hexadec[2] = '\0';
    int left_half  = byte / 16; // Get worth of left hexa value
    int right_half = byte % 16; // Get worth of right hexa value

    if (left_half < 10) hexadec[0] = '0' + left_half; // ASCII arithmetic to find correct hexadec character
    else hexadec[0] = 'A' + (left_half - 10);         // ASCII arithmetic to find correct hexadec character

    if (right_half < 10) hexadec[1] = '0' + right_half; // ASCII arithmetic to find correct hexadec character
    else hexadec[1] = 'A' + (right_half - 10);          // ASCII arithmetic to find correct hexadec character

    return hexadec;
}