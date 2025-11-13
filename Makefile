COMMIT_AMOUNT = $(shell git rev-list --count --all)
BUILD_NUMBER = v0.0.$(COMMIT_AMOUNT)

BUILD_DIR := ./build/intermediate
OUT_DIR := ./build/out

KERNEL_DIR := ./kernel
BOOT_DIR := ./bootloader

C_SOURCES := $(shell find $(KERNEL_DIR) -type f -name "*.c")
ASM_SOURCES_TO_LINK := $(shell find $(KERNEL_DIR) -type f -name "*.asm") 

C_OBJECTS := $(patsubst %.c, $(BUILD_DIR)/%.o, $(notdir $(C_SOURCES)))
ASM_OBJECTS := $(patsubst %.asm, $(BUILD_DIR)/%.o, $(notdir $(ASM_SOURCES_TO_LINK)))

KERNEL_ENTRY_OBJ := $(BUILD_DIR)/kernel_entry.o

ALL_KERNEL_OBJS := $(KERNEL_ENTRY_OBJ) $(C_OBJECTS) $(filter-out $(KERNEL_ENTRY_OBJ), $(ASM_OBJECTS))


.PHONY: all run clean
all: run

$(OUT_DIR)/os_image.bin: $(BUILD_DIR)/mbr.bin $(BUILD_DIR)/kernel.bin
	@echo "Creating OS Image: $@"
	@mkdir -p $(OUT_DIR)
	cat $^ > $@

run: ./build/out/os_image.bin
	qemu-system-i386 -drive file=$<,format=raw,if=floppy


$(BUILD_DIR)/kernel.bin: $(ALL_KERNEL_OBJS)
	@echo "Linking kernel binary..."
	@mkdir -p $(BUILD_DIR)
	ld -m elf_i386 -o $@ -Ttext 0x1000 -e main $^ --oformat binary

EXCLUDE_OBJ := $(BUILD_DIR)/kernel_entry.o

.SECONDEXPANSION:
$(filter-out $(EXCLUDE_OBJ), $(BUILD_DIR)/%.o):
	@mkdir -p $(BUILD_DIR)

	$(eval NAME := $(notdir $*))

	$(eval C_SRC := $(filter %/$(NAME).c, $(C_SOURCES)))

	$(eval ASM_SRC := $(filter %/$(NAME).asm, $(ASM_SOURCES_TO_LINK)))

	
	$(if $(C_SRC), \
		@echo "Compiling C: $(C_SRC)" \
		&& gcc -fno-pie -m32 -ffreestanding -D BUILD_NUMBER=\"$(BUILD_NUMBER)\" -c $(C_SRC) -o $@, \
	)

	$(if $(ASM_SRC), \
		@echo "Compiling ASM: $(ASM_SRC)" \
		&& nasm $(ASM_SRC) -f elf -o $@, \
	)

$(KERNEL_ENTRY_OBJ): $(BOOT_DIR)/kernel_entry.asm
	@echo "Assembling entry: $<"
	@mkdir -p $(BUILD_DIR)
	nasm $< -f elf -o $@


$(BUILD_DIR)/kernel_size.inc: $(BUILD_DIR)/kernel.bin
	@echo "Creating kernel size include file..."
	@mkdir -p $(BUILD_DIR)
	$(eval kernel_size=$(shell stat -f%z $< 2>/dev/null || stat -c%s $< 2>/dev/null))
	$(eval sectors=$(shell echo "($(kernel_size) + 511) / 512" | bc))
	echo "kernel_sectors equ $(sectors)" > $@

$(BUILD_DIR)/mbr.bin: $(BOOT_DIR)/mbr.asm $(BUILD_DIR)/kernel_size.inc
	@echo "Assembling MBR: $<"
	@mkdir -p $(BUILD_DIR)
	nasm $< -f bin -o $@

$(BUILD_DIR)/interrupts.o: $(KERNEL_DIR)/interrupts.asm
	@echo "Assembling Interrupts: $<"
	@mkdir -p $(BUILD_DIR)
	nasm $< -f elf -o $@

clean:
	@echo "Cleaning build artifacts..."
	$(RM) -r $(BUILD_DIR)/*
	$(RM) $(OUT_DIR)/os_image.bin