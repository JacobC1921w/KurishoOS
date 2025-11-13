#ifndef DISPLAY_H
#define DISPLAY_H

#pragma region Constants

// Video graphics array offsets
#define VGA_CTRL_REGISTER 0x3d4
#define VGA_DATA_REGISTER 0x3d5
#define VGA_OFFSET_LOW 0x0f
#define VGA_OFFSET_HIGH 0x0e 
#define VIDEO_ADDRESS 0xb8000

// Terminal window settings
#define MAX_ROWS 25
#define MAX_COLS 80
#define WHITE_ON_BLACK 0x0f

#pragma endregion Constants



#pragma region Function prototypes

unsigned char port_byte_in(unsigned short port);
void port_byte_out(unsigned short port, unsigned char data);
void set_cursor(int offset);
int get_cursor();
void set_char_at_memory(char character, int offset);
int get_row_from_offset(int offset);
int get_offset(int col, int row);
int move_offset_to_newline(int offset);
void memory_copy(char *source, char *dest, int n_bytes);
int scroll_line(int offset);
void print_string(char *string);
void clear_screen();

#pragma endregion Function prototypes

#endif