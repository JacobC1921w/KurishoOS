#include "port.h"

/**
 * @brief Reads a single byte of data from a specified I/O port.
 *
 * This function uses inline assembly to execute the x86 'in' instruction,
 * which is a low-level operation used for communicating with hardware
 * devices (such as a keyboard controller or timer) via their respective
 * I/O port addresses.
 *
 * @param port The 16-bit address of the I/O port to read from.
 * @return unsigned char The 8-bit data byte read from the I/O port.
 */
unsigned char port_byte_in(unsigned short port) {
    unsigned char result;
    __asm__("in %%dx, %%al" : "=a" (result) : "d" (port));
    return result;
}

/**
 * @brief Writes a single byte of data to a specified I/O port.
 *
 * This function uses inline assembly to execute the x86 'out' instruction,
 * which is a low-level operation used for sending data to a hardware
 * device (such as a keyboard controller or timer) via its respective
 * I/O port address.
 *
 * @param port The 16-bit address of the I/O port to write to.
 * @param data The 8-bit data byte to be sent to the I/O port.
 * @return void This function does not return a value.
 */
void port_byte_out(unsigned short port, unsigned char data) {
    __asm__("out %%al, %%dx" : : "a" (data), "d" (port));
}