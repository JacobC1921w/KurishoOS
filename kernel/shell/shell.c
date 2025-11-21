#include "../drivers/keyboard/keyboard.h"
#include "../drivers/memory/memory.h"
#include "../drivers/display/display.h"
#include "../drivers/data_manipulation/data_manipulation.h"

void parse_command(char *s1) {
    s1 = string_trim(s1);

    if (string_compare(s1, "") == 0) {
        // Do nothing, enter has just been pressed with no given input
    } else if (string_compare(s1, "exit") == 0) {
        println_string("Halting system processes...");
        asm volatile("hlt");
    } else if (string_compare(s1, "t-sc") == 0) {
        println_string("Testing string_concat()...");
        println_string(string_concat("A ", string_concat("B ", string_concat("C ", "D "))));
    } else {
        println_string(string_concat("Unknown command: ", s1));
    }

    print_string("> ");
}