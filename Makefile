# $@ = target file
# $< = first dependency
# $^ = all dependencies

COMMIT_AMOUNT = $(shell git rev-list --count --all)
BUILD_NUMBER = v0.0.${COMMIT_AMOUNT}

# First rule is the one executed when no parameters are fed to the Makefile
all: run

# Create kernel size include file before building bootloader
./Build/Intermediate/kernel_size.inc: ./Build/Intermediate/kernel.bin
	@echo "Creating kernel size include file..."
	$(eval kernel_size=$(shell stat -f%z $< 2>/dev/null || stat -c%s $< 2>/dev/null))
	$(eval sectors=$(shell echo "($(kernel_size) + 511) / 512" | bc))
	echo "kernel_sectors equ $(sectors)" > $@

./Build/Intermediate/keyboard.o: ./Kernel/Drivers/keyboard.asm
	nasm $< -f elf -o $@

./Build/Intermediate/kernel.bin: ./Build/Intermediate/kernel_entry.o ./Build/Intermediate/kernel.o ./Build/Intermediate/keyboard.o
	ld -m elf_i386 -o $@ -Ttext 0x1000 $^ --oformat binary

./Build/Intermediate/kernel_entry.o: ./Bootloader/kernel_entry.asm
	nasm $< -f elf -o $@

./Build/Intermediate/kernel.o: ./Kernel/kernel.c
	gcc -fno-pie -m32 -ffreestanding -D BUILD_NUMBER=\"$(BUILD_NUMBER)\" -c $< -o $@

./Build/Intermediate/mbr.bin: ./Bootloader/mbr.asm ./Build/Intermediate/kernel_size.inc
	nasm $< -f bin -o $@

./Build/Out/os_image.bin: ./Build/Intermediate/mbr.bin ./Build/Intermediate/kernel.bin
	cat $^ > $@

run: ./Build/Out/os_image.bin
	qemu-system-i386 $<

clean:
	$(RM) -r ./Build/*/*.bin ./Build/*/*.o ./Build/*/*.dis
