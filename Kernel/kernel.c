#include "./Drivers/display.h"
#include "./Drivers/keyboard.h"

void main() {
    clear_screen();

    print_string("-------------------------------\n");
    print_string("\n Welcome to Kurisho OS ");
    print_string(BUILD_NUMBER);
    print_string("-------------------------------\n");

    print_string("Installing interrupt service routines (ISRs).\n");
    isr_install();

    print_string("Enabling external interrupts.\n");
    asm volatile("sti");

    print_string("Initializing keyboard (IRQ 1).\n");
    initialize_keyboard();
}