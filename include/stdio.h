#ifndef INCLUDE_STDIO_H
#define INCLUDE_STDIO_H

#include "multiboot.h"
#include "io.h"

extern multiboot_info_t *mbinfo;

multiboot_uint32_t rgb(int r, int g, int b){
  r = ((1 << mbinfo->framebuffer_red_mask_size) - (256 - r)) 
            << mbinfo->framebuffer_red_field_position;
  g = ((1 << mbinfo->framebuffer_green_mask_size) - (256 - g)) 
            << mbinfo->framebuffer_green_field_position;
  b = ((1 << mbinfo->framebuffer_blue_mask_size) - (256 - b)) 
            << mbinfo->framebuffer_blue_field_position;
  return r | g | b;
}

void fillrect(unsigned int x, unsigned int y, unsigned int w, unsigned int h, multiboot_uint32_t color) {
  void *where = fb + mbinfo->framebuffer_pitch * y + 4 * x;
  unsigned int i, j;

  for (i = 0; i < h && i < mbinfo->framebuffer_height - 2*y; i++) {
    void *line = where;
    for (j = 0; j < w && j < mbinfo->framebuffer_width - 2*x; j++) {
      *(multiboot_uint32_t *)(line + j*4) = color;
    }
    where+=  mbinfo->framebuffer_pitch;
  }
}


#endif