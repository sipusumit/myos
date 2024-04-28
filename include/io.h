#ifndef INCLUDE_IO_H
#define INCLUDE_IO_H

#define FB_COMMAND_PORT 0x3d4
#define FB_DATA_PORT 0x3d5

#define FB_HIGH_BYTE 14
#define FB_LOW_BYTE 15

#define VGA_MAX_ROW 25
#define VGA_MAX_COL 80

#define ATTRIBUTE 7
#define CHECK_FLAG(flags,bit)   ((flags) & (1 << (bit)))

char *vga;
void *fb;
int position;
int xpos;
int ypos;

extern void outb(unsigned short port, unsigned char data);
extern unsigned char inb(unsigned short port);

void set_fb_cursor(int p);
void clear_screen(char color);
void print(char* str);
void itoa (char *buf, int base, int d);
void putchar (int c);
void printf (const char *format, ...);

#endif