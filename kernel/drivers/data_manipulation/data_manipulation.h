#ifndef DATA_MANIPULATION_H
#define DATA_MANIPULATION_H
#include <stdint.h>
#include <stddef.h>

char* uint_32_base_convert(uint32_t value, char *buffer, int base);
void custom_hex_conversion(uint32_t value, char *buffer);

#endif