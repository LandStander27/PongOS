#include "string.h"
#include "stdarg.h"
#include "graphics.h"
#include "keyboard.h"
#include "bool.h"

int cursor_pos = 0;
int text_color = 15;

int putchar(int pos, char c) {
	volatile char *video = (volatile char*)0xB8000;

	if (pos >= 3840 && c == '\n') {
		for (int i = 160; i < 4000; i += 160) {
			for (int j = i; j < i+160; j++) {
				video[j-160] = video[j];
			}
		}

		for (int i = 3840; i < 4000; i += 2) {
			video[i] = ' ';
			video[i+1] = 15;
		}

		return 3840;
	}

	if (pos >= 4000) {
		return 4000;
	}

	if (c == '\n') {
		return (160-(pos%160))+pos;
	}

	video += pos;
	*video++ = c;
	*video++ = text_color;
	return pos+2;
}

void set_color(int color) {
	text_color = color;
}

int putstr(int pos, const char *str, int len) {
	for (int i = 0; i < len; i++) {
		pos = putchar(pos, str[i]);
	}
	return pos;
}

void printf(const char* restrict format, ...) {

	va_list pars;
	va_start(pars, format);

	while (*format != '\0') {
		if (format[0] != '%' || format[1] == '%') {
			if (format[0] == '%') {
				format++;
			}
			int amount = 1;
			while (format[amount] && format[amount] != '%') {
				amount++;
			}

			cursor_pos = putstr(cursor_pos, format, amount);

			format += amount;
			continue;
		}

		const char* format_began = format++;

		if (*format == 'c') {
			format++;
			char c = (char)(va_arg(pars, int));

			cursor_pos = putchar(cursor_pos, c);

		} else if (*format == 's') {
			format++;
			const char* str = va_arg(pars, const char*);

			int len = str_len(str);
			cursor_pos = putstr(cursor_pos, str, len);
		} else if (*format == 'd') {
			format++;
			int num = va_arg(pars, int);

			char str[10];
			int_to_string(num, str);
			cursor_pos = putstr(cursor_pos, str, str_len(str));

		} else {
			format = format_began;
			int len = str_len(format);
			cursor_pos = putstr(cursor_pos, format, len);

			format += len;
		}

	}

	va_end(pars);

}

void left(int amount) {
	cursor_pos -= 2*amount;
}

void right(int amount) {
	cursor_pos += 2*amount;
}

void down(int amount) {
	cursor_pos += 160*amount;
}

void up(int amount) {
	cursor_pos -= 160*amount;
}

void set_cursor_pos(int x, int y) {
	cursor_pos = pos_to_offset(x, y);
}

int* get_cursor_pos() {
	return offset_to_pos(cursor_pos);
}

void getline(char *str) {
	printf("_");
	left(1);

	{
		struct Keycode key = get_input_instant();
		while (key.character == '\n') {
			key = get_input_instant();
		}
	}

	int last_key = -1;
	int line_len = 0;

	while (true) {

		bool valid_press = false;

		struct Keycode key = get_input();

		if (key.action == Press) {
			if (last_key == -1) {
				last_key = key.code;
				valid_press = true;
			} else {
				if (last_key != key.code) {
					last_key = key.code;
					valid_press = true;
				}
			}
		} else {
			last_key = -1;
		}

		if (key.character == '\n') {
			printf(" \n");
			str[line_len] = '\0';
			return;
		}

		if (key.character == 0x3 && key.code != 0x0E) {
			valid_press = false;
		}

		if (valid_press) {
			if (key.code == 0x0E) {
				if (line_len != 0) {
					left(1);
					printf("_ ");
					left(2);

					str[line_len-1] = '\0';
					line_len--;
				}
			} else {
				printf("%c_", key.character);
				left(1);

				str[line_len] = key.character;
				line_len++;
			}
		}
	}
}
