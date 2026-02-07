
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

typedef unsigned char byte;

char* longToBinaryString(long lNumber);
int strLength(char* s, int countNewLine);
bool isNumeric(char* s);
long strToLong(char* s);

int main(int argc, char** argv) {
    // If argc is not 2
    if (argc != 2) {
        // Print with end='\n'
        puts("Argument count must be 2. Enter -h for help.");
        return 2; // return 2 for unsuccessful case as stated in specification
    // If help requested
    } else if (strcmp(argv[1], "-h") == 0) {
        // Print with end='\n'
        puts("Enter a number to convert it to binary.");
        return 0;
    } else if (!isNumeric(argv[1])) {
        // Print with end='\n'
        puts("Argument is NaN. Enter -h for help.");
        return 2; // return 2 for unsuccessful case as stated in specification
    } 
    
    long lNumber = strToLong(argv[1]);
    char* sBinary = longToBinaryString(lNumber);
    printf("%s", sBinary);

    free(sBinary);
    sBinary = NULL;
}

char* longToBinaryString(long lNumber) {
    // Rewrite this to calculate the string size before hand, allocate space too.
    // Should be either 8, 16, 24, 32.
    char* sBinary;
    int size;
    if (lNumber > 0xFFFFFFFF) {
        size = 64;
    } else if (lNumber > 0xFFFF) {
        size = 32;
    } else if (lNumber > 0xFF) {
        size = 16;
    } else {
        size = 8;
    }

    sBinary = (char*) malloc(size + 1);

    int bOneFound = 0;

    char* ptr = sBinary;
    
    for (int i = 0; i < size; i++) {
        if ((lNumber & (1 << (size-i-1))) == 1 << (size-i-1)) {
            *ptr = '1';
        } else {
            *ptr = '0';
        }
        ptr++;
    }

    *ptr = '\0';
    return sBinary;
}

int strLength(char* s, int countNewLine) {
    if (countNewLine != 0 && countNewLine != 1) {
        // fprintf allows us to choose the stream to send output to
        fprintf(stderr, "Error in strLength(): countNewLine must be 0 or 1.\n");
        // return -1 for faulty input
        return -1;
    }
    // declare variable
    int length = 0;

    // Iterate through string
    while(*s != '\0') {
        // Handle new lines
        if (*s == '\n') {
            length += countNewLine;
        // Increment length
        } else {
            length++;
        }
        // Move pointer
        s++;
    }
    return length;
}

bool isNumeric(char* s) {
    // While s has not reached the null terminator
    while (*s) {
        // If the the value s points to (dereferencing) is not a digit
        if (!(*s >= '0' && *s <= '9')) {
            return false; // return false
        }
        s++; // move s siz'\0'(char), effectively pointing to the next char in the string
    }
    return true; // return true
}

long strToLong(char* s) {
    // Check that string contains only numbers
    if (!isNumeric(s)) {
        // fprintf allows us to choose the stream to send output to
        fprintf(stderr, "Error in strToLong(): countNewLine must be 0 or 1.\n");
        return -1; // faulty input
    }
    long result = 0;

    // Get length of s without \n
    int remainingLen = strLength(s, 0);
    // While s does not point to null terminator and remainingLen is greater than 0
    while(*s != '\0' && remainingLen > 0) {
        // Multiply by then, effectively shifting the number to the left, then add the 10^0 value
        if (*s >= '0' && *s <= '9') {
            result = (result * 10) + (*s - '0');
        }
        // Decrement remaining length
        remainingLen--;
        // Move pointer
        s++;
    }
    return result;
}

// Takes x to the power of y,  both integers and only positive y.
int xToThePowerOfY(int x, int y) {
    // Initialize result
    int result = 1;
    // Repeat y times
    for (int i = 0; i < y; i++) {
        // Multiply result with x
        result = result * x;
    }
    // Return result
    return result;
}