
#include "kernel.h"
#include "./drivers/port/port.h"
#include "./drivers/display/display.h"
#include "./drivers/keyboard/keyboard.h"

void main() {
    clear_screen();

    // Print the banner - The dashes should be generated automatically in the future using something like print_string(23+len(BUILD_NUMBER))
    print_string("-------------------------------\n");
    print_string("\n Welcome to Kurisho OS ");
    print_string(BUILD_NUMBER);
    print_string("\n-------------------------------\n");

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

    print_string("> ");
}