#include <stdint.h>

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

int string_length(char input[]) {
    int i = 0;
    while (input[i] != '\0') {
        ++i;
    }

    return i;
}

void append_char(char input[], char n) {
    int string_len = string_length(input);
    input[string_len] = n;
    input[string_len + 1] = '\0';
}

int string_compare(char s1[], char s2[]) {
    int i;
    for (i = 0; s1[i] == s2[i]; i++) {
        if (s1[i] == '\0') return 0;
    }
    return s1[i] - s2[i];
}

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