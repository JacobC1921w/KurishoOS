#ifndef DISPLAY_H
#define DISPLAY_H

#define VGA_CTRL_REGISTER 0x3d4
#define VGA_DATA_REGISTER 0x3d5
#define VGA_OFFSET_LOW 0x0f
#define VGA_OFFSET_HIGH 0x0e

#define VIDEO_ADDRESS 0xb8000
#define MAX_ROWS 25
#define MAX_COLS 80
#define WHITE_ON_BLACK 0x0f

unsigned char portByteIn(unsigned short port) {
    unsigned char result;
    __asm__("in %%dx, %%al" : "=a" (result) : "d" (port));
    return result;
}

void portByteOut(unsigned short port, unsigned char data) {
    __asm__("out %%al, %%dx" : : "a" (data), "d" (port));
}

void setCursor(int offset) {
    offset /= 2;
    portByteOut(VGA_CTRL_REGISTER, VGA_OFFSET_HIGH);
    portByteOut(VGA_DATA_REGISTER, (unsigned char) (offset >> 8));
    portByteOut(VGA_CTRL_REGISTER, VGA_OFFSET_LOW);
    portByteOut(VGA_DATA_REGISTER, (unsigned char) (offset & 0xff));
}

int getCursor() {
    portByteOut(VGA_CTRL_REGISTER, VGA_OFFSET_HIGH);
    int offset = portByteIn(VGA_DATA_REGISTER) << 8;
    portByteOut(VGA_CTRL_REGISTER, VGA_OFFSET_LOW);
    offset += portByteIn(VGA_DATA_REGISTER);
    return offset * 2;
}

void setCharAtVideoMemory(char character, int offset) {
    unsigned char *videoMemory = (unsigned char *) VIDEO_ADDRESS;
    videoMemory[offset] = character;
    videoMemory[offset + 1] = WHITE_ON_BLACK;
}

int getRowFromOffset(int offset) {
    return offset / (2 * MAX_COLS);
}

int getOffset(int col, int row) {
    return 2 * (row * MAX_COLS + col);
}

int moveOffsetToNewLine(int offset) {
    return getOffset(0, getRowFromOffset(offset) + 1);
}

void memoryCopy(char *source, char *dest, int nBytes) {
    int i;
    for(i = 0; i < nBytes; i++) {
        *(dest + i) = *(source + i);
    }
}

int scrollLine(int offset) {
    memoryCopy(
        (char *) (getOffset(0, 1) + VIDEO_ADDRESS),
        (char *) (getOffset(0, 0) + VIDEO_ADDRESS),
        MAX_COLS * (MAX_ROWS - 1) * 2
    );

    for (int col = 0; col < MAX_COLS; col++) {
        setCharAtVideoMemory(' ', getOffset(col, MAX_ROWS - 1));
    }

    return offset - 2 * MAX_COLS;
}

void printString(char *string) {
    int offset = getCursor();
    int i = 0;
    while (string[i] != 0) {
        if (offset >= MAX_ROWS * MAX_COLS * 2) {
            offset = scrollLine(offset);
        }
        if (string[i] == '\n') {
            offset = moveOffsetToNewLine(offset);
        } else {
            setCharAtVideoMemory(string[i], offset);
            offset += 2;
        }
        i++;
    }

    setCursor(offset);
}

void clearScreen() {
    for (int i = 0; i < MAX_COLS * MAX_ROWS; i++) {
        setCharAtVideoMemory(' ', i * 2);
    }
    setCursor(getOffset(0, 0));
}

#endif // DISPLAY_H