#ifndef INCLUDE_FONT_H
#define INCLUDE_FONT_H

#include "multiboot.h"


#define PSF_FONT_MAGIC 0x864ab572
#define NULL ((void*)0)

typedef struct {
  unsigned int magic;         /* magic bytes to identify PSF */
  unsigned int version;       /* zero */
  unsigned int headersize;    /* offset of bitmaps in file, 32 */
  unsigned int flags;         /* 0 if there's no unicode table */
  unsigned int numglyph;      /* number of glyphs */
  unsigned int bytesperglyph; /* size of each glyph */
  unsigned int height;        /* height in pixels */
  unsigned int width;         /* width in pixels */
} PSF_font;

// unsigned int *_binary_font_psf_start;
// unsigned int *_binary_font_psf_end;
PSF_font *font;

unsigned short *unicode;

 
#define PIXEL unsigned int   /* pixel pointer */

extern multiboot_info_t *mbinfo;
extern void *fb;

void fb_putchar(unsigned short int c, int cx, int cy, unsigned int fg, unsigned int bg);

#endif