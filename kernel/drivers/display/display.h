#ifndef DISPLAY_H
#define DISPLAY_H

#pragma region Constants

// Terminal window settings
#define MAX_ROWS 25
#define MAX_COLS 80
#define WHITE_ON_BLACK 0x0f

#pragma endregion Constants

#pragma region Function prototypes

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
void print_backspace();

#pragma endregion Function prototypes

#endif