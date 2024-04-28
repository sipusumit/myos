#include "io.h"
#include "multiboot.h"
#include "font.h"

multiboot_info_t *mbinfo;

void kmain(unsigned int ebx){
  mbinfo = (multiboot_info_t *)ebx;
  position = 0;
  xpos = 0;
  ypos = 0;
  vga = (char *)0xb8000;
  clear_screen(0x0F);

  set_fb_cursor(position);

  outb(FB_COMMAND_PORT, FB_HIGH_BYTE);
  position = inb(FB_DATA_PORT) <<  8;
  outb(FB_COMMAND_PORT, FB_LOW_BYTE);
  position += inb(FB_DATA_PORT);

  printf("Hello From Kernel!\n");
  printf("Screen Size: %dx%d\n", mbinfo->framebuffer_width, mbinfo->framebuffer_height);
  if(CHECK_FLAG(mbinfo->flags, 12)){
  //   printf("true");
    fb = (void *) (unsigned long) mbinfo->framebuffer_addr;
  //   multiboot_uint32_t color = rgb(255, 0, 255);
  //   fillrect(10, 10, mbinfo->framebuffer_width -20, mbinfo->framebuffer_height-10 , color);
  //   fillrect(25, 50, 100, 150 , rgb(255,0,0));
  }
  printf("Modules loaded: %d \nAddr: 0x%x \n", mbinfo->mods_count, mbinfo->mods_addr);
  // for(unsigned int i = 0; i < mbinfo->mods_count; i++){
  // if(mbinfo->mods_count > 0){
  //   multiboot_module_t *mod  = (multiboot_module_t *)(mbinfo->mods_addr);
  //   font = (PSF_font *)mod->mod_start;
  //   // _binary_font_psf_start = mod->mod_start;
  //   // _binary_font_psf_end = mod->mod_end;
  //   printf("Header: 0x%x\n"
  //          "Version: %d\n"
  //          "Header Size: %d\n"
  //          "Flags: 0b%u\n"
  //          "Gylphs: %d\n"
  //          "Gylph Size: %d\n"
  //          "Height: %d\n"
  //          "Width: %d\n",
  //          font->magic, font->version, font->headersize, font->flags, font->numglyph, font->bytesperglyph, font->height, font->width);
  //   unsigned short glyph = 0;
  //   char *s = (char *)((unsigned char *)font + font->headersize + font->numglyph * font->bytesperglyph);
  //   while(s> (char *)mod->mod_end) {
  //       unsigned short uc = (unsigned short)(s[0]);
  //       if(uc == 0xFF) {
  //           glyph++;
  //           s++;
  //           continue;
  //       } else if(uc & 128) {
  //           /* UTF-8 to unicode */
  //           if((uc & 32) == 0 ) {
  //               uc = ((s[0] & 0x1F)<<6)+(s[1] & 0x3F);
  //               s++;
  //           } else
  //           if((uc & 16) == 0 ) {
  //               uc = ((((s[0] & 0xF)<<6)+(s[1] & 0x3F))<<6)+(s[2] & 0x3F);
  //               s+=2;
  //           } else
  //           if((uc & 8) == 0 ) {
  //               uc = ((((((s[0] & 0x7)<<6)+(s[1] & 0x3F))<<6)+(s[2] & 0x3F))<<6)+(s[3] & 0x3F);
  //               s+=3;
  //           } else
  //               uc = 0;
  //       }
  //       /* save translation */
  //       unicode[uc] = glyph;
  //       s++;
  //   }
    
  //   fb_putchar('A', 0, 0, 0xFFFFFF, 0x000000);
  //   fb_putchar('B', 2, 0, 0xFFFFFF, 0x000000);
  // }


  while(1);
}