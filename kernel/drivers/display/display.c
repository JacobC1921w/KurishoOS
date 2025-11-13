#include "display.h"
#include "../port/port.h"

/**
 * @brief Sets the position of the text cursor on the VGA screen.
 *
 * This function communicates directly with the Video Graphics Array (VGA)
 * hardware registers to update the cursor's position on the screen. The
 * position is specified by an offset from the start of the video memory.
 *
 * @param offset The linear offset within the video memory (char index * 2)
 * where the cursor should be placed.
 * @return void This function does not return a value.
 */
void set_cursor(int offset) {
    offset /= 2;
    port_byte_out(VGA_CTRL_REGISTER, VGA_OFFSET_HIGH);
    port_byte_out(VGA_DATA_REGISTER, (unsigned char) (offset >> 8));
    port_byte_out(VGA_CTRL_REGISTER, VGA_OFFSET_LOW);
    port_byte_out(VGA_DATA_REGISTER, (unsigned char) (offset & 0xff));
}

/**
 * @brief Retrieves the current position of the text cursor from the VGA screen.
 *
 * This function reads from the Video Graphics Array (VGA) hardware registers
 * to determine the cursor's current position, which is returned as a byte
 * offset into the video memory.
 *
 * @return int The byte offset (char index * 2) representing the cursor's
 * current position in video memory.
 */
int get_cursor() {
    port_byte_out(VGA_CTRL_REGISTER, VGA_OFFSET_HIGH);
    int offset = port_byte_in(VGA_DATA_REGISTER) << 8;
    port_byte_out(VGA_CTRL_REGISTER, VGA_OFFSET_LOW);
    offset += port_byte_in(VGA_DATA_REGISTER);
    return offset * 2;
}

/**
 * @brief Writes a character and its color attribute directly to video memory.
 *
 * This function places a specified character at a particular byte offset
 * in the VGA text-mode video memory, using a predefined color attribute
 * (typically white text on a black background). This is a low-level operation
 * for displaying text on the screen without using BIOS or operating system
 * calls.
 *
 * @param character The ASCII character byte to be displayed.
 * @param offset The byte offset in video memory where the character should be written.
 * @return void This function does not return a value.
 */
void set_char_at_memory(char character, int offset) {
    unsigned char *video_memory = (unsigned char *) VIDEO_ADDRESS;
    video_memory[offset] = character;
    video_memory[offset + 1] = WHITE_ON_BLACK;
}

/**
 * @brief Calculates the row number corresponding to a given video memory byte offset.
 *
 * This function determines the current row index (starting from 0) of a character
 * position in the VGA text-mode video memory, based on its linear byte offset.
 *
 * @param offset The byte offset in video memory (i.e., char index * 2) of the character position.
 * @return int The calculated row number (0-indexed).
 */
int get_row_from_offset(int offset) {
    return offset / (2 * MAX_COLS);
}

/**
 * @brief Calculates the byte offset in video memory for a given column and row.
 *
 * This function determines the linear byte offset address within the VGA
 * text-mode video memory corresponding to a specific cursor position
 * defined by its (column, row) coordinates.
 *
 * @param col The column index (x-coordinate, 0-indexed) on the screen.
 * @param row The row index (y-coordinate, 0-indexed) on the screen.
 * @return int The byte offset (char index * 2) in video memory.
 */
int get_offset(int col, int row) {
    return 2 * (row * MAX_COLS + col);
}

/**
 * @brief Calculates the byte offset for the beginning of the next line.
 *
 * This function determines the byte offset in video memory that corresponds to
 * the start of the row immediately following the one containing the given offset.
 * This is typically used to simulate a newline character '\\n' in text output.
 *
 * @param offset The current byte offset in video memory.
 * @return int The byte offset for the first column (column 0) of the next row.
 */
int move_offset_to_newline(int offset) {
    return get_offset(0, get_row_from_offset(offset) + 1);
}

/**
 * @brief Copies a block of memory from a source location to a destination location.
 *
 * This function performs a byte-by-byte copy of data from a source memory address
 * to a destination memory address for a specified number of bytes. It is functionally
 * equivalent to the standard C library function memcpy().
 *
 * @param source A pointer to the starting address of the source memory block.
 * @param dest A pointer to the starting address of the destination memory block.
 * @param n_bytes The total number of bytes to be copied.
 * @return void This function does not return a value.
 */
void memory_copy(char *source, char *dest, int n_bytes) {
    int i;
    for(i = 0; i < n_bytes; i++) {
        *(dest + i) = *(source + i);
    }
}

/**
 * @brief Performs a screen scroll operation, shifting the entire screen content up by one line.
 *
 * This function simulates a vertical scroll by copying all screen content up by one row
 * and then clearing the last row. It is typically called when text output reaches the
 * bottom of the screen.
 *
 * @param offset The current byte offset in video memory.
 * @return int The new byte offset, adjusted to the start of the now-empty last row.
 */
int scroll_line(int offset) {
    memory_copy(
        (char *) (get_offset(0, 1) + VIDEO_ADDRESS),
        (char *) (get_offset(0, 0) + VIDEO_ADDRESS),
        MAX_COLS * (MAX_ROWS - 1) * 2
    );

    for (int col = 0; col < MAX_COLS; col++) {
        set_char_at_memory(' ', get_offset(col, MAX_ROWS - 1));
    }

    return offset - 2 * MAX_COLS;
}

/**
 * @brief Prints a null-terminated string to the VGA text-mode screen.
 *
 * This is the main text output function. It reads the string character by
 * character and handles necessary low-level screen operations, including
 * automatically advancing the cursor, processing newline characters, and
 * scrolling the entire screen content when the bottom is reached.
 *
 * @param string A pointer to the null-terminated string to be displayed.
 * @return void This function does not return a value.
 */
void print_string(char *string) {
    int offset = get_cursor();
    int i = 0;
    while (string[i] != 0) {
        if (offset >= MAX_ROWS * MAX_COLS * 2) {
            offset = scroll_line(offset);
        }
        if (string[i] == '\n') {
            offset = move_offset_to_newline(offset);
        } else {
            set_char_at_memory(string[i], offset);
            offset += 2;
        }
        i++;
    }

    set_cursor(offset);
}

/**
 * @brief Clears the entire VGA text-mode screen and resets the cursor position.
 *
 * This function clears the display by iterating through all character positions
 * in the video memory and setting each cell to a blank space (' '). After
 * clearing the screen content, the hardware cursor is reset to the top-left
 * corner (row 0, column 0).
 *
 * @return void This function does not return a value.
 */
void clear_screen() {
    for (int i = 0; i < MAX_COLS * MAX_ROWS; i++) {
        set_char_at_memory(' ', i * 2);
    }
    set_cursor(get_offset(0, 0));
}

