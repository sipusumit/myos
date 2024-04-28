#include "font.h"

void fb_putchar(unsigned short int c, int cx, int cy, unsigned int fg, unsigned int bg){
    /* we need to know how many bytes encode one row */
    int bytesperline=(font->width+7)/8;
    /* unicode translation */
    if(unicode != NULL) {
        c = unicode[c];
    }
    /* get the glyph for the character. If there's no
       glyph for a given character, we'll display the first glyph. */
    unsigned char *glyph =
     (unsigned char*)font +
     font->headersize +
     (c>0&&c<font->numglyph?c:0)*font->bytesperglyph;
    /* calculate the upper left corner on screen where we want to display.
       we only do this once, and adjust the offset later. This is faster. */
    void *offs = fb +
        (cy * font->height * mbinfo->framebuffer_pitch) +
        (cx * (font->width + 1) * 4);
    /* finally display pixels according to the bitmap */
    unsigned int x,y;
    unsigned int mask;
    for(y=0;y<font->height;y++){
        /* save the starting position of the line */
        void *line=offs;
        mask=1<<(font->width-1);
        /* display a row */
        for(x=0;x<font->width;x++){
            // *(PIXEL*)(line) = *((unsigned int*)glyph) & mask ? fg : bg;
            *(PIXEL*)(line) = fg | bg;
            /* adjust to the next pixel */
            mask >>= 1;
            line += 4;
        }
        /* adjust to the next line */
        glyph += bytesperline;
        offs  += mbinfo->framebuffer_pitch;
    }
}