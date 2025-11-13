#include <stdint.h>

/* @brief Converts an unsigned 32-bit integer to its string representation 
 * in a specified base (radix).
 *
 * This function implements a standard integer-to-ASCII (itoa) conversion
 * algorithm. It converts the given numerical value into a null-terminated 
 * string using repeated division by the base, and stores the result in 
 * the provided buffer.
 *
 * WARNING: The caller is responsible for ensuring the 'buffer' is large 
 * enough to hold the resulting string and the null terminator. 
 * For base 10 (decimal), 11 bytes are required. For base 2 
 * (binary), 33 bytes are required.
 *
 * @param value The unsigned 32-bit integer to be converted.
 * @param buffer A pointer to the destination character array (buffer) where 
 * the resulting string will be stored.
 * @param base The base (radix) for the conversion (must be between 2 and 36, inclusive).
 * @return char* A pointer to the start of the destination buffer ('buffer'), 
 * which now contains the null-terminated string representation 
 * of the value. Returns the buffer with only a null terminator 
 * if the base is invalid.
 */
char* uint_32_base_convert(uint32_t value, char *buffer, int base) {
    char *ptr = buffer;
    char *ptr1 = buffer;
    char temp_char;
    uint32_t temp_value;

    if (base < 2 || base > 36) {
        *ptr = '\0';
        return ptr;
    }

    do {
        temp_value = value;
        value /= base;
        *ptr++ = "0123456789abcdefghijklmnopqrstuvwxyz"[temp_value % base];
    } while (value != 0);

    *ptr-- = '\0';

    while (ptr1 < ptr) {
        temp_char = *ptr;
        *ptr-- = *ptr1;
        *ptr1++ = temp_char;
    }

    return buffer;
}

/**
 * @brief Calculates the length of a null-terminated string.
 *
 * This function iterates through the input character array until it encounters 
 * the null terminator ('\0'). It implements the equivalent functionality of 
 * the standard library's strlen().
 *
 * @param input The null-terminated character array (string).
 * @return int The number of characters in the string, excluding the 
 * null terminator.
 */
int string_length(char input[]) {
    int i = 0;
    while (input[i] != '\0') {
        ++i;
    }

    return i;
}

/**
 * @brief Appends a single character to the end of a null-terminated string.
 *
 * This function determines the current length of the input string, places the 
 * new character 'n' at the index corresponding to that length, and ensures 
 * the string remains null-terminated by placing '\0' immediately after the 
 * appended character.
 *
 * WARNING: The caller must ensure the 'input' buffer has sufficient space 
 * for the new character plus the null terminator.
 *
 * @param input The null-terminated character array (string) to modify.
 * @param n The single character to append.
 * @return void
 */
void append_char(char input[], char n) {
    int string_len = string_length(input);
    input[string_len] = n;
    input[string_len + 1] = '\0';
}

/**
 * @brief Compares two null-terminated strings lexicographically.
 *
 * This function iterates through both strings, comparing corresponding characters.
 * It implements the equivalent functionality of the standard library's strcmp().
 *
 * @param s1 The first null-terminated string.
 * @param s2 The second null-terminated string.
 * @return int 
 * - 0 if s1 and s2 are identical.
 * - A negative value if the first differing character in s1 is less than 
 * that in s2.
 * - A positive value if the first differing character in s1 is greater than 
 * that in s2.
 */
int string_compare(char s1[], char s2[]) {
    int i;
    for (i = 0; s1[i] == s2[i]; i++) {
        if (s1[i] == '\0') return 0;
    }
    return s1[i] - s2[i];
}

/**
 * @brief Converts an uppercase ASCII character to its lowercase equivalent.
 *
 * This function checks if the input character 'c' is in the range of 
 * uppercase letters ('A' through 'Z'). If it is, it sets the 5th bit (0x20) 
 * using a bitwise OR operation to convert it to lowercase, exploiting the 
 * structure of the ASCII table.
 *
 * @param c The character to be converted.
 * @return char The lowercase equivalent of 'c' if it was uppercase, 
 * otherwise the original character 'c' is returned unchanged.
 */
char char_lower(char c) {
    if (c >= 'A' && c <= 'Z') {
        c = c | 0x20;
    }
    return c;
}

char char_upper(char c) {
    if (c >= 'a' && c <= 'z') {
        c = c & ~0x20;
    }
    return c;
}