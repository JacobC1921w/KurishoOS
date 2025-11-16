#include <stdint.h>
#include "../display/display.h"
#include "../memory/memory.h"

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

char char_lower(char input) {
    if (input >= 'A' && input <= 'Z') {
        input = input | 0x20;
    }
    return input;
}

char char_upper(char input) {
    if (input >= 'a' && input <= 'z') {
        input = input & ~0x20;
    }
    return input;
}

int char_is_whitespace(char input) {
    return (input == ' ' || input == '\t' || input == '\n' || input == '\v' || input == '\f' || input == '\r');
}

char *string_trim(char *input) {
    if (input == NULL || *input == '\0') {
        return input;
    }

    char *start = input;
    char *end;
    size_t len;

    while (char_is_whitespace(*start)) {
        start++;
    }

    if (*start == '\0') {
        *input = '\0';
        return input;
    }

    len = string_length(start);
    end = start + len - 1;

    while (end > start && char_is_whitespace(*end)) {
        end--;
    }

    *(end + 1) = '\0';

    if (start != input) {
        memory_move(input, start, string_length(start) + 1);
    }

    return input;
}

char *string_duplicate(char *input, int num_bytes) {
    if (input == NULL) {
        return NULL;
    }

    char *new_string = (char *) memory_allocate(num_bytes + 1);
    if (new_string == NULL) {
        return NULL;
    }

    memory_copy(new_string, input, num_bytes);
    new_string[num_bytes] = '\0';

    return new_string;
}