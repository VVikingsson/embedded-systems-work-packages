#include <ctype.h> // character library

// This function verifies that a string is numeric
/**
 * @brief Checks that a string is numeric
 *
 * @param s The string to be checked
 * @return 1 or 0, true or false.
 */
int isNumeric(char* s) {
    // While s has not reached the null terminator
    while (*s) {
        // If the the value s points to (dereferencing) is not a digit
        if (!(*s >= '0' && *s <= '9')) {
            return 0; // return false
        }
        s++; // move s siz'\0'(char), effectively pointing to the next char in the string
    }
    return 1; // return true
}

/**
 * @brief Converts a numeric string to a long
 *
 * @param s The string to be converted.
 * @return Long, -1 if error
 */
long strToLong(char* s) {
    // Check that string contains only numbers
    if (!isNumeric(s)) {
        // fprintf allows us to choose the stream to send output to
        fprintf(stderr, "Error in strToLong(): countNewLine must be 0 or 1.\n");
        return -1; // faulty input
    }
    long result = 0;

    // Get lenght of s without \n
    int remainingLen = strLength(s, 0);
    // While s does not point to null terminator and remainingLen is greater than 0
    while(*s != '\0' && remainingLen > 0) {
        // Add the character in the string * it's position in base 10 respective
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

/**
 * @brief Converts a char to an int
 *
 * @param c the character to be converted
 * @return resulting int from conversion.
 */
int numericCharToInt(char c) {
    return (int) (c - '0');
} 

/**
 * @brief Gets the length of a string
 *
 * @param s The string to be measured
 * @param countNewLine 1 or 0, to count new lines or not
 * @return The length of the string, or -1 on error
 */
int strLength(char* s, int countNewLine) {
    if (countNewLine != 0 && countNewLine != 1) {
        //
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

/**
 * @brief Returns x to the power of y
 *
 * @param x int base
 * @param y int exponent
 * @return double
 */

char* concatenateStrings(char* s, char* z) {
    // Allocate memory the heap (+1 for null terminator)
    char* newString = (char*) malloc(strLength(s, 1) + strLength(z, 1) + 1); 
    // Pointer for populating string
    char* pointer = newString;

    // Go through s and add each character to the new string
    while (*s != '\0') {
        // Dereference to access values which pointers point to
        *pointer = *s;
        // Increment pointers
        s++;
        pointer++;
    }

    // Go through z and add eah character to the new string
    while (*z != '\0') {
        // Dereference to access values which pointers point to
        *pointer = *z;
        // Increment pointers
        z++;
        pointer++;
    }

    *pointer = '\0';
    return newString;
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