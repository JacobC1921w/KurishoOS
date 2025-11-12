#include "./Drivers/display.h"
#include "./Drivers/keyboard.h"

void main() {
    clearScreen();
    printString("Installing interrupt service routines (ISRs).\n");
    ISRInstall();

    printString("Enabling external interrupts.\n");
    asm volatile("sti");

    printString("Initializing keyboard (IRQ 1).\n");
    initKeyboard();
}