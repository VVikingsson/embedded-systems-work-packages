#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

typedef unsigned char byte;

int strLength(char* s, bool countNewLine);
char* binaryStringToHexString(char* bs);
byte fourBitBinaryStringToByte(char*);
char fourBitNumberToHex(byte number);
bool isNumeric(char* s);


int main(int argc, char** argv) {
    char* arg = fgets()
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
    char* hexaDecString = binaryStringToHexString(argv[1]);
    printf("%s", hexaDecString);
    free(hexaDecString);
    hexaDecString = NULL;
}

char* binaryStringToHexString(char* bs) {
    int length = strLength(bs, 0);  // get length of binary string without counting new line
    char* result = (char*) malloc((int) ((length+3) / 4) + 1);   // declare result pointer and allocate memory
    char* ptr = result; // copy to iterate
    int remainder = length % 4;     // calculate remainder

    // Handle remainder
    if (remainder != 0) {
        int sum = 0;    // initialize sum
        for (int i = remainder - 1; i >= 0; i--) {  // for every "excess" binary digit
            // If current char is 1, add corresponding bit value to sum
            if (*bs == '1') {
                sum += 1 << i; // bit shift left
            }
            // Move pointer to next char
            bs++;
        }
        // conditional logic and dereferencing to add correct hexadecimal character to string
        if (sum > 9) *ptr = 'A' + sum - 10;
        else *ptr = '0' + sum;
        ptr++; // Move our iterator because we added a character in the current location
    }

    // Declare a buffer variable
    byte partSum;
    // For every character in the binary string
    while(*bs != '\0') {
        partSum = fourBitBinaryStringToByte(bs);    // Calculate decimal value of next four steps of binary string
        bs += 4;    // Move binarystring pointer 4 steps
        *ptr = fourBitNumberToHex(partSum); // place hexadec char resulting from partSum into current ptr address
        ptr++;  // Move ptr to iterate through binary string (ptr is originally a copy of bs)
    }
    *ptr='\0';

    return result;
}

byte fourBitBinaryStringToByte(char* ptr) {
    int result = 0;
    // for every number 3-0
    for (int i=3; i >= 0; i--) {
        // If current char is 1, add corresponding bit value
        if (*ptr == '1') {
            result += 1 << i;
        }
        // Move pointer to next char
        ptr++;
    }
    return result;
}

char fourBitNumberToHex(byte number) {
    if (number > 9) {
        return 'A' + number - 10;
    } else {
        return '0' + number;
    }
};


int strLength(char* s, bool countNewLine) {
    if (countNewLine != 0 && countNewLine) {
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