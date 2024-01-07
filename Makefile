build:
	mkdir -p temp
	mkdir -p bin

	as --32 boot/boot.s -o temp/boot.o
	gcc -O2 -m32 -Iinclude -c src/kernel.c -o temp/kernel.o -std=gnu99 -ffreestanding -O2 -Wall -Wextra
	gcc -O2 -m32 -Iinclude -c src/string.c -o temp/string.o -std=gnu99 -ffreestanding -O2 -Wall -Wextra
	gcc -O2 -m32 -Iinclude -c src/port.c -o temp/port.o -std=gnu99 -ffreestanding -O2 -Wall -Wextra
	gcc -O2 -m32 -Iinclude -c src/graphics.c -o temp/graphics.o -std=gnu99 -ffreestanding -O2 -Wall -Wextra
	gcc -O2 -m32 -Iinclude -c src/keyboard.c -o temp/keyboard.o -std=gnu99 -ffreestanding -O2 -Wall -Wextra
	gcc -O2 -m32 -Iinclude -c src/stdio.c -o temp/stdio.o -std=gnu99 -ffreestanding -O2 -Wall -Wextra
	ld -m elf_i386 -T boot/linker.ld temp/kernel.o temp/string.o temp/port.o temp/graphics.o temp/keyboard.o temp/stdio.o temp/boot.o -o bin/Pong.bin -nostdlib
	grub-file --is-x86-multiboot bin/Pong.bin

	mkdir -p temp/isodir/boot/grub
	cp bin/Pong.bin temp/isodir/boot/Pong.bin
	cp boot/grub.cfg temp/isodir/boot/grub/grub.cfg
	grub-mkrescue -o bin/Pong.iso temp/isodir

run:
	mkdir -p temp
	mkdir -p bin

	as --32 boot/boot.s -o temp/boot.o
	gcc -O2 -m32 -Iinclude -c src/kernel.c -o temp/kernel.o -std=gnu99 -ffreestanding -O2 -Wall -Wextra
	gcc -O2 -m32 -Iinclude -c src/string.c -o temp/string.o -std=gnu99 -ffreestanding -O2 -Wall -Wextra
	gcc -O2 -m32 -Iinclude -c src/port.c -o temp/port.o -std=gnu99 -ffreestanding -O2 -Wall -Wextra
	gcc -O2 -m32 -Iinclude -c src/graphics.c -o temp/graphics.o -std=gnu99 -ffreestanding -O2 -Wall -Wextra
	gcc -O2 -m32 -Iinclude -c src/keyboard.c -o temp/keyboard.o -std=gnu99 -ffreestanding -O2 -Wall -Wextra
	gcc -O2 -m32 -Iinclude -c src/stdio.c -o temp/stdio.o -std=gnu99 -ffreestanding -O2 -Wall -Wextra
	ld -m elf_i386 -T boot/linker.ld temp/kernel.o temp/string.o temp/port.o temp/graphics.o temp/keyboard.o temp/stdio.o temp/boot.o -o bin/Pong.bin -nostdlib
	grub-file --is-x86-multiboot bin/Pong.bin

	mkdir -p temp/isodir/boot/grub
	cp bin/Pong.bin temp/isodir/boot/Pong.bin
	cp boot/grub.cfg temp/isodir/boot/grub/grub.cfg
	grub-mkrescue -o bin/Pong.iso temp/isodir

	qemu-system-x86_64 -cdrom bin/Pong.iso

clean:
	rm -rf temp
