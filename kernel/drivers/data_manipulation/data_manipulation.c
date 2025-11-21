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

void append_char(char input[], char c) {
    int string_len = string_length(input);
    input[string_len] = c;
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

int char_is_whitespace(char c) {
    return (c == ' ' || c == '\t' || c == '\n' || c == '\v' || c == '\f' || c == '\r');
}

char *string_trim(char *s1) {
    if (s1 == NULL || *s1 == '\0') {
        return s1;
    }

    char *start = s1;
    char *end;
    size_t len;

    while (char_is_whitespace(*start)) {
        start++;
    }

    if (*start == '\0') {
        *s1 = '\0';
        return s1;
    }

    len = string_length(start);
    end = start + len - 1;

    while (end > start && char_is_whitespace(*end)) {
        end--;
    }

    *(end + 1) = '\0';

    if (start != s1) {
        memory_move(s1, start, string_length(start) + 1);
    }

    return s1;
}

char *string_duplicate(char *s1, int num_bytes) {
    if (s1 == NULL) {
        return NULL;
    }

    char *new_string = (char *) memory_allocate(num_bytes + 1);
    if (new_string == NULL) {
        return NULL;
    }

    memory_copy(new_string, s1, num_bytes);
    new_string[num_bytes] = '\0';

    memory_free(new_string);
    return new_string;
}

char *char_repeat(char c, int iter) {
    char *return_string = (char *) memory_allocate(iter + 1);
    for (int i = 0; i <= iter; i++) {
        return_string[i] = c;
    }

    return_string[iter] = '\0';
    return return_string;
}

char *string_concat(char *s1, char *s2) {
    int s1_length = string_length(s1);
    int s2_length = string_length(s2);
    char *return_string = (char *) memory_allocate(s1_length + s2_length + 1);

    for (int i = 0; i < s1_length; i++) {
        return_string[i] = s1[i];
    }

    for (int i = 0; i <= s2_length; i++) {
        return_string[s1_length + i] = s2[i];
    }

    return_string[s1_length + s2_length] = '\0';
    return return_string;
}