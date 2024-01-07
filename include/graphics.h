#ifndef GRAPHICS_H
#define GRAPHICS_H

void draw_pixel(int x, int y, int color);
int* offset_to_pos(int offset);
int pos_to_offset(int x, int y);
void clear_screen();
void draw_rectangle(int x, int y, int w, int h, int color);

#endif