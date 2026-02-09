#include <stdio.h>

#define ENGINE_BIT      0b10000000
#define GEAR_POS_BITS   0b01110000
#define KEY_POS_BITS    0b00001100
#define BRAKE1_BIT      0b00000010
#define BRAKE2_BIT      0b00000001
#define FALSE 0
#define TRUE 1

// Takes a byte sized hexadecimal and transforms to number format
unsigned char hexadecimal_to_byte(char* hxs);
// Takes a byte and parses it to print the status of the imaginary car
void print_car_state(unsigned char byte);
// Checks if a string contains only hexadecimal characters
int is_hexadecimal(char* s);
// Gets the length of a string
int string_length(char* s);

// Main function, entry point
int main(int argc, char** argv) {
    if (argc != 2) {    // If number of arguments is not 1
        printf("Must provide exactly 1 argument.");
        return 1;
    } else if (!is_hexadecimal(argv[1])) {  // If argument is not hexadecimal
        printf("Argument must be hexadecimal.");
        return 1;
    } else if (string_length(argv[1]) != 2) {   // If argument length is not 2
        printf("Hexadecimal string must be of length 2 (one byte).");
        return 1;
    }

    // Get byte
    unsigned char byte = hexadecimal_to_byte(argv[1]);

    print_car_state(byte);
}


// Checks if string is hexadecimal
int is_hexadecimal(char* s) {
    while (*s != '\0') {    // For each char in string, until null terminator
        // Check if current char is hexadecimal
        if (!( (*s >= '0' && *s <= '9') || (*s >= 'A' && *s <= 'F') ) ) {
            return FALSE;   // string is not hexadecimal
        }
        s++;
    }

    return TRUE;    // string is hexadecimal
}

// Takes a byte sized hexadecimal and transforms to number format.
// Assumes previous error handling.
unsigned char hexadecimal_to_byte(char* hxs) {
    unsigned char byte = 0; // Initialize byte to 0b00000000
    
    if (hxs[0] <= '9') { // if hexadec digit is <= 9
        byte += (hxs[0] - '0') * 16; // Simple ASCII arithmetic
    } else {    // else it is >= A
        byte += (hxs[0] - 'A' + 10) * 16; // A=10, B=11, C=12, D=13, E=14, F=15.
    }

    if (hxs[1] <= '9') {    // if hexadec digit is <= 9
        byte += (hxs[1] - '0'); // Simple ASCII arithmetic
    } else {    // else it is >= A
        byte += (hxs[1] - 'A' + 10);    // A=10, B=11, C=12, D=13, E=14, F=15.
    }
    printf("%0x", byte);
    return byte;
}

void print_car_state(unsigned char byte) {
    int engine_on = (byte & ENGINE_BIT) >> 7;
    int gear_pos = (byte & GEAR_POS_BITS) >> 4;
    int key_pos = (byte & KEY_POS_BITS) >> 2;
    int brake1 = (byte & BRAKE1_BIT) >> 1;
    int brake2 = byte & BRAKE2_BIT;



    printf( "%-15s%s\n"
            "-----------------------------\n"
            "%-15s%d\n"
            "%-15s%d\n"
            "%-15s%d\n"
            "%-15s%d\n"
            "%-15s%d",
            "Name", "Value",
            "engine_on", engine_on,
            "gear_pos", gear_pos,
            "key_pos", key_pos,
            "brake1", brake1,
            "brake2", brake2);
}

int string_length(char* s) {
    int count = 0;
    while(*s != '\0') {
        count++;
        s++;
    }

    return count;
}