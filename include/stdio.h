#ifndef STDIO_H
#define STDIO_H

void printf(const char* restrict format, ...);
void left(int amount);
void right(int amount);
void down(int amount);
void up(int amount);
void getline(char *str);
void set_cursor_pos(int x, int y);
int* get_cursor_pos();
void set_color(int color);

#endif