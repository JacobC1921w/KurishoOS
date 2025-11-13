#include "./Drivers/display.h"
#include "./Drivers/keyboard.h"

void main() {
    clear_screen();

    print_string("-------------------------------\n");
    print_string("\n Welcome to Kurisho OS ");
    print_string(BUILD_NUMBER);
    print_string("\n-------------------------------\n");

    print_string("Installing interrupt service routines (ISRs)...");
    isr_install();
    print_string(" DONE!\n");

    print_string("Enabling external interrupts...");
    asm volatile("sti");
    print_string(" DONE!\n");

    print_string("Initializing keyboard (IRQ 1)...");
    initialize_keyboard();
    print_string(" DONE!\n");
}