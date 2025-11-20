#include "./keyboard.h"
#include "../memory/memory.h"
#include "../display/display.h"
#include "../data_manipulation/data_manipulation.h"

void parse_command(char *s1) {
    s1 = string_trim(s1);

    if (string_compare(s1, "exit") == 0) {
        print_string("Halting system processes...\n");
        asm volatile("hlt");
    }

    print_string("Unknown command: ");
    print_string(s1);
    print_string("\n> ");
}