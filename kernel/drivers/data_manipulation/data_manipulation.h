#ifndef DATA_MANIPULATION_H
#define DATA_MANIPULATION_H
#include <stdint.h>
#include <stddef.h>

char* uint_32_base_convert(uint32_t value, char *buffer, int base);
int string_length(char input[]);
void append_char(char input[], char c);
bool string_compare(char s1[], char s2[]);
char char_lower(char c);
char char_upper(char c);
int char_is_whitespace(char s1);
char *string_trim(char *s1);
char *string_duplicate(const char *s1, int num_bytes);
char *char_repeat(char c, int iter);
char *string_concat(char *s1, char *s2);

#endif