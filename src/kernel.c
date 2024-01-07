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
		printf("%s\n", cmd);

	}

	return 0;
}

void kernel_entry() {
	clear_screen();
	kernel_main();

	while (true) {  }
}
