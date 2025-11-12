# $@ = target file
# $< = first dependency
# $^ = all dependencies

# First rule is the one executed when no parameters are fed to the Makefile
all: run

# Create kernel size include file before building bootloader
./Build/Intermediate/kernelSize.inc: ./Build/Intermediate/kernel.bin
	@echo "Creating kernel size include file..."
	$(eval kernelsize=$(shell stat -f%z $< 2>/dev/null || stat -c%s $< 2>/dev/null))
	$(eval sectors=$(shell echo "($(kernelsize) + 511) / 512" | bc))
	echo "kernelSectors equ $(sectors)" > $@

./Build/Intermediate/keyboard.o: ./Kernel/Drivers/keyboard.asm
	nasm $< -f elf -o $@

./Build/Intermediate/kernel.bin: ./Build/Intermediate/kernelEntry.o ./Build/Intermediate/kernel.o ./Build/Intermediate/keyboard.o
	ld -m elf_i386 -o $@ -Ttext 0x1000 $^ --oformat binary

./Build/Intermediate/kernelEntry.o: ./Bootloader/kernelEntry.asm
	nasm $< -f elf -o $@

./Build/Intermediate/kernel.o: ./Kernel/kernel.c
	gcc -fno-pie -m32 -ffreestanding -c $< -o $@

./Build/Intermediate/masterBootRecord.bin: ./Bootloader/masterBootRecord.asm ./Build/Intermediate/kernelSize.inc
	nasm $< -f bin -o $@

./Build/Out/os-image.bin: ./Build/Intermediate/masterBootRecord.bin ./Build/Intermediate/kernel.bin
	cat $^ > $@

run: ./Build/Out/os-image.bin
	qemu-system-i386 $<

clean:
	$(RM) -r ./Build/*/*.bin ./Build/*/*.o ./Build/*/*.dis
