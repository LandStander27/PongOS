#pragma GCC diagnostic ignored "-Wuninitialized"
#pragma GCC diagnostic ignored "-Wmaybe-uninitialized"

#include "kernel.h"
#include "bool.h"
#include "types.h"
#include "string.h"
#include "keyboard.h"
#include "graphics.h"
#include "stdio.h"

void get_cmd(char *str, char *cmd) {
	int cmd_len = 0;
	for (int i = 0; i < str_len(str); i++) {
		if (str[i] == ' ') {
			break;
		}
		cmd[cmd_len] = str[i];
		cmd_len++;
	}
	cmd[cmd_len] = '\0';
}

int kernel_main() {

	printf("PongOS\n\n");

	char cmd[100];
	char starting[100];

	while (true) {

		set_color(11);
		printf("> ");
		set_color(15);
		getline(cmd);
		get_cmd(cmd, starting);

		if (str_cmp(starting, "echo")) {
			int len = str_len(cmd);
			if (len > 5) {
				for (int i = 5; i < len; i++) {
					printf("%c", cmd[i]);
				}
			}
		} else if (str_cmp(starting, "help")) {
			printf(
				"echo:      echoes all arguments passed to command\n"
				"clear:     clears the screen\n"
				"help:      display commands built into PongOS\n"
				"start:     start the game\n"
				"keypress:  output information about a keypress (for debugging)"
			);
		} else if (str_cmp(starting, "clear")) {
			clear_screen();
			set_cursor_pos(0, 0);
			printf("PongOS\n");
		} else if (str_cmp(starting, "start")) {
			printf("Starting game\n");
		} else if (str_cmp(starting, "keypress")) {
			printf("Release `enter` to start\n");
			struct Keycode key = get_input();
			while (key.action == Press && key.character == '\n') {
				key = get_input();
			}
			printf("Listening\n");
			while (key.action != Press) {
				key = get_input();
			}
			printf("Keycode: %d\nCharacter: %c", key.code, key.character);
		} else {
			printf("Could not find command\nUse `help` to view available commands");
		}

		printf("\n");

	}

	return 0;
}

void kernel_entry() {
	clear_screen();
	kernel_main();

	while (true) {  }
}
