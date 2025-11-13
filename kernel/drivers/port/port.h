#ifndef PORT_H
#define PORT_H

#pragma region Constants

// Video graphics array offsets
#define VGA_CTRL_REGISTER 0x3d4
#define VGA_DATA_REGISTER 0x3d5
#define VGA_OFFSET_LOW 0x0f
#define VGA_OFFSET_HIGH 0x0e 
#define VIDEO_ADDRESS 0xb8000

#pragma endregion Constants

#pragma region Function prototypes

unsigned char port_byte_in(unsigned short port);
void port_byte_out(unsigned short port, unsigned char data);

#pragma endregion Function prototypes

#endif