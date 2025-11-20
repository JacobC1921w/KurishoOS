
#include "kernel.h"
#include "./drivers/port/port.h"
#include "./drivers/display/display.h"
#include "./drivers/keyboard/keyboard.h"
#include "./drivers/data_manipulation/data_manipulation.h"

void main() {
    clear_screen();

    // Install ISR
    print_string("Installing interrupt service routines (ISRs)...");
    isr_install();
    print_string(" DONE!\n");

    // Enable external interrupts
    print_string("Enabling external interrupts...");
    asm volatile("sti");
    print_string(" DONE!\n");

    // Initialize keyboard
    print_string("Initializing keyboard (IRQ 1)...");
    initialize_keyboard();
    print_string(" DONE!\n");
    
    clear_screen();

    // Print the banner
    println_string(char_repeat('-', string_length(BUILD_NUMBER) + 23));
    println_string(string_concat("Welcome to Kurisho OS ", string_concat(BUILD_NUMBER, "\n")));
    println_string(char_repeat('-', string_length(BUILD_NUMBER) + 23));

    print_string("> ")
}