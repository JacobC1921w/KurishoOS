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