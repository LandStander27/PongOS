#pragma GCC diagnostic ignored "-Wuninitialized"
#pragma GCC diagnostic ignored "-Wmaybe-uninitialized"

#include "kernel.h"
#include "bool.h"
#include "types.h"
#include "string.h"
#include "keyboard.h"
#include "graphics.h"
#include "stdio.h"

int kernel_main() {

	printf("PongOS\n\n");

	char cmd[100];

	while (true) {

		printf("> ");
		char cmd[100];
		getline(cmd);

		if (starts_with(cmd, "echo")) {
			int len = str_len(cmd);
			if (len > 5) {
				if (cmd[4] == ' ') {
					for (int i = 5; i < len; i++) {
						printf("%c", cmd[i]);
					}
				}
			}
		} else if (starts_with(cmd, "help ")) {
			printf(
				"echo:   echoes all arguments passed to command\n"
				"clear:  clears the screen\n"
				"help:   display commands built into PongOS\n"
				"start:  start the game"
			);
		} else if (starts_with(cmd, "clear ")) {
			clear_screen();
			set_cursor_pos(0, 0);
			printf("PongOS\n");
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
