#ifndef HEADERFILE_H
#define HEADERFILE_H

// This function verifies that a string is numeric
/**
 * @brief Checks that a string is numeric
 *
 * @param s The string to be checked
 * @return 1 or 0, true or false.
 */
int isNumeric(char* s);

/**
 * @brief Converts a numeric string to a long
 *
 * @param s The string to be converted.
 * @return Long, null if error
 */
long strToLong(char* s);


/**
 * @brief Converts a char to an int
 *
 * @param c the character to be converted
 * @return resulting int from conversion.
 */
int numericCharToInt(char c);

/**
 * @brief Returns x to the power of y
 *
 * @param x int base
 * @param y int exponent
 * @return double
 */
double xPowerOfY(int x, int y);

/**
 * @brief Gets the length of a string
 *
 * @param s The string to be measured
 * @param countNewLine 1 or 0, to count new lines or not
 * @return The length of the string, or null on error
 */
int strLength(char* s, int countNewLine);

/**
 * @brief Returns s appended with z
 *
 * @param s The prefix string
 * @param z The suffix string
 * @return A new heap-allocated concatenated string. Remember to free()!
 */
char* concatenateString(char* s, char* z);

#endif