#ifndef DATA_MANIPULATION_H
#define DATA_MANIPULATION_H
#include <stdint.h>
#include <stddef.h>

char* uint_32_base_convert(uint32_t value, char *buffer, int base);
int string_length(char input[]);
void append_char(char input[], char n);
int string_compare(char s1[], char s2[]);
char char_lower(char c);
char char_upper(char c);

#endif