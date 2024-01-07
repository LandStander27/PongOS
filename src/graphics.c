
int* offset_to_pos(int offset) {
	static int pos[2];
	pos[0] = (offset%160)/2;
	pos[1] = offset/160/2;
	return pos;
}

int pos_to_offset(int x, int y) {
	return y*160+x*2;
}

void draw_pixel(int x, int y, int color) {
	volatile char *video = (volatile char*)0xB8000;

	video += pos_to_offset(x, y);

	*video++ = 219;
	*video++ = color;
}

void draw_rectangle(int x, int y, int w, int h, int color) {
	for (int i = x; i < x+w; i++) {
		for (int j = y; j < y+h; j++) {
			draw_pixel(i, j, color);
		}
	}
}

void clear_screen() {
	volatile char *video = (volatile char*)0xB8000;

	for (int i = 0; i < 4000; i++) {
		*video++ = ' ';
		*video++ = 15;
	}
}