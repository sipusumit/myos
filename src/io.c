#include "io.h"

void set_fb_cursor(int p){
  outb(FB_COMMAND_PORT, FB_HIGH_BYTE);
  outb(FB_DATA_PORT, ((p >> 8) & 0x00FF));
  outb(FB_COMMAND_PORT, FB_LOW_BYTE);
  outb(FB_DATA_PORT, (p & 0x00FF));
}

void clear_screen(char color){
  int i = 0;
  while(i < (VGA_MAX_ROW * VGA_MAX_COL * 2)){
    vga[i] = ' ';
    i++;
    vga[i] = color;
    i++;
  }
  set_fb_cursor(0);
  position = 0;
}

void print(char *str){
  int i =0;
  while (str[i] != '\0')
  {
    vga[position++ *2] = str[i++];
  }
  set_fb_cursor(position);
}

void itoa (char *buf, int base, int d){
  char *p = buf;
  char *p1, *p2;
  unsigned long ud = d;
  int divisor = 10;
  
  /* If %d is specified and D is minus, put ‘-’ in the head. */
  if (base == 'd' && d < 0)
    {
      *p++ = '-';
      buf++;
      ud = -d;
    }
  else if (base == 'x')
    divisor = 16;

  /* Divide UD by DIVISOR until UD == 0. */
  do
    {
      int remainder = ud % divisor;
      
      *p++ = (remainder < 10) ? remainder + '0' : remainder + 'a' - 10;
    }
  while (ud /= divisor);

  /* Terminate BUF. */
  *p = 0;
  
  /* Reverse BUF. */
  p1 = buf;
  p2 = p - 1;
  while (p1 < p2)
    {
      char tmp = *p1;
      *p1 = *p2;
      *p2 = tmp;
      p1++;
      p2--;
    }
}

void putchar (int c){
  if (c == '\n' || c == '\r'){
    xpos = 0;
    ypos++;
    if (ypos >= VGA_MAX_ROW)
      ypos = 0;
    return;
  }

  *(vga + (xpos + ypos * VGA_MAX_COL) * 2) = c & 0xFF;
  *(vga + (xpos + ypos * VGA_MAX_COL) * 2 + 1) = ATTRIBUTE;
  // vga[(xpos + ypos * VGA_MAX_COL)*2] = c;

  xpos++;
  if (xpos >= VGA_MAX_COL){
    xpos = 0;
    ypos++;
    if (ypos >= VGA_MAX_ROW)
      ypos = 0;
  }
  position = ypos * VGA_MAX_COL + xpos;
}

void printf (const char *format, ...){
  char **arg = (char **) &format;
  int c;
  char buf[20];

  arg++;
  
  while ((c = *format++) != 0)
    {
      if (c != '%')
        putchar (c);
      else
        {
          char *p, *p2;
          int pad0 = 0, pad = 0;
          
          c = *format++;
          if (c == '0')
            {
              pad0 = 1;
              c = *format++;
            }

          if (c >= '0' && c <= '9')
            {
              pad = c - '0';
              c = *format++;
            }

          switch (c)
            {
            case 'd':
            case 'u':
            case 'x':
              itoa (buf, c, *((int *) arg++));
              p = buf;
              goto string;
              break;

            case 's':
              p = *arg++;
              if (! p)
                p = "(null)";

            string:
              for (p2 = p; *p2; p2++);
              for (; p2 < p + pad; p2++)
                putchar (pad0 ? '0' : ' ');
              while (*p)
                putchar (*p++);
              break;

            default:
              putchar (*((int *) arg++));
              break;
            }
        }
    }
  set_fb_cursor(position);
}