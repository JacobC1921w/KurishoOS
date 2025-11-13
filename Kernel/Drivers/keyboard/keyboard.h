#ifndef KEYBOARD_H
#define KEYBOARD_H

#include <stdint.h>

#pragma region Constants

#define idt_entries 256

#define IRQ0 32
#define IRQ1 33
#define IRQ2 34
#define IRQ3 35
#define IRQ4 36
#define IRQ5 37
#define IRQ6 38
#define IRQ7 39
#define IRQ8 40
#define IRQ9 41
#define IRQ10 42
#define IRQ11 43
#define IRQ12 44
#define IRQ13 45
#define IRQ14 46
#define IRQ15 47

#define low_16(address) (uint16_t) ((address) & 0xFFFF)
#define high_16(address) (uint16_t) (((address) >> 16) & 0xFFFF)

#pragma endregion Constants

#pragma region Type definitions

typedef struct {
    uint16_t low_offset;
    uint16_t selector;
    uint8_t always_0;
    uint8_t flags;
    uint16_t high_offset;
} __attribute__((packed)) idt_gate;

typedef struct {
    uint32_t ds;
    uint32_t edi, esi, ebp, esp, ebx, edx, ecx, eax;
    uint32_t interrupt_number, error_code;
    uint32_t eip, cs, eflags, useresp, ss;
} registers;

typedef struct {
    uint16_t limit;
    uint32_t base;
} __attribute__((packed)) idt_register;

typedef void (*isr)(registers *);

#pragma endregion Type definitions

#pragma region Variables
char *exception_messages[] = {
    "Exception: Divide error",
    "Exception: Debug exception",
    "Exception: NMI interrupt",
    "Exception: Breakpoint",
    "Exception: Overflow",
    "Exception: BOUND range exceeded",
    "Exception: Invalid opcode",
    "Exception: Device not available",
    "Exception: Double fault",
    "Exception: Coprocessor segment overrun",
    "Exception: Invalid TSS",
    "Exception: Segment not present",
    "Exception: Stack-segment fault",
    "Exception: General protection",
    "Exception: Page fault",
    "Exception: Intel reserved...",
    "Exception: x87 floating point error",
    "Exception: Alignment check",
    "Exception: Machine check",
    "Exception: SIMD floating-point exception",
    "Exception: Virtualization exception",
    "Exception: Control protection exception",
    "Exception: Future reservation", "Exception: Future reservation", "Exception: Future reservation", "Exception: Future reservation", "Exception: Future reservation", "Exception: Future reservation", "Exception: Future reservation", "Exception: Future reservation", "Exception: Future reservation", "Exception: Future reservation",
    "Exception: External interrupt (0x20)", "Exception: External interrupt (0x21)", "Exception: External interrupt (0x22)", "Exception: External interrupt (0x23)", "Exception: External interrupt (0x24)", "Exception: External interrupt (0x25)", "Exception: External interrupt (0x26)", "Exception: External interrupt (0x27)", "Exception: External interrupt (0x28)", "Exception: External interrupt (0x29)", "Exception: External interrupt (0x2a)", "Exception: External interrupt (0x2b)", "Exception: External interrupt (0x2c)", "Exception: External interrupt (0x2d)", "Exception: External interrupt (0x2e)", "Exception: External interrupt (0x2f)", "Exception: External interrupt (0x30)", "Exception: External interrupt (0x31)", "Exception: External interrupt (0x32)", "Exception: External interrupt (0x33)", "Exception: External interrupt (0x34)", "Exception: External interrupt (0x35)", "Exception: External interrupt (0x36)", "Exception: External interrupt (0x37)", "Exception: External interrupt (0x38)", "Exception: External interrupt (0x39)", "Exception: External interrupt (0x3a)", "Exception: External interrupt (0x3b)", "Exception: External interrupt (0x3c)", "Exception: External interrupt (0x3d)", "Exception: External interrupt (0x3e)", "Exception: External interrupt (0x3f)", "Exception: External interrupt (0x40)", "Exception: External interrupt (0x41)", "Exception: External interrupt (0x42)", "Exception: External interrupt (0x43)", "Exception: External interrupt (0x44)", "Exception: External interrupt (0x45)", "Exception: External interrupt (0x46)", "Exception: External interrupt (0x47)", "Exception: External interrupt (0x48)", "Exception: External interrupt (0x49)", "Exception: External interrupt (0x4a)", "Exception: External interrupt (0x4b)", "Exception: External interrupt (0x4c)", "Exception: External interrupt (0x4d)", "Exception: External interrupt (0x4e)", "Exception: External interrupt (0x4f)", "Exception: External interrupt (0x50)", "Exception: External interrupt (0x51)", "Exception: External interrupt (0x52)", "Exception: External interrupt (0x53)", "Exception: External interrupt (0x54)", "Exception: External interrupt (0x55)", "Exception: External interrupt (0x56)", "Exception: External interrupt (0x57)", "Exception: External interrupt (0x58)", "Exception: External interrupt (0x59)", "Exception: External interrupt (0x5a)", "Exception: External interrupt (0x5b)", "Exception: External interrupt (0x5c)", "Exception: External interrupt (0x5d)", "Exception: External interrupt (0x5e)", "Exception: External interrupt (0x5f)", "Exception: External interrupt (0x60)", "Exception: External interrupt (0x61)", "Exception: External interrupt (0x62)", "Exception: External interrupt (0x63)", "Exception: External interrupt (0x64)", "Exception: External interrupt (0x65)", "Exception: External interrupt (0x66)", "Exception: External interrupt (0x67)", "Exception: External interrupt (0x68)", "Exception: External interrupt (0x69)", "Exception: External interrupt (0x6a)", "Exception: External interrupt (0x6b)", "Exception: External interrupt (0x6c)", "Exception: External interrupt (0x6d)", "Exception: External interrupt (0x6e)", "Exception: External interrupt (0x6f)", "Exception: External interrupt (0x70)", "Exception: External interrupt (0x71)", "Exception: External interrupt (0x72)", "Exception: External interrupt (0x73)", "Exception: External interrupt (0x74)", "Exception: External interrupt (0x75)", "Exception: External interrupt (0x76)", "Exception: External interrupt (0x77)", "Exception: External interrupt (0x78)", "Exception: External interrupt (0x79)", "Exception: External interrupt (0x7a)", "Exception: External interrupt (0x7b)", "Exception: External interrupt (0x7c)", "Exception: External interrupt (0x7d)", "Exception: External interrupt (0x7e)", "Exception: External interrupt (0x7f)", "Exception: External interrupt (0x80)", "Exception: External interrupt (0x81)", "Exception: External interrupt (0x82)", "Exception: External interrupt (0x83)", "Exception: External interrupt (0x84)", "Exception: External interrupt (0x85)", "Exception: External interrupt (0x86)", "Exception: External interrupt (0x87)", "Exception: External interrupt (0x88)", "Exception: External interrupt (0x89)", "Exception: External interrupt (0x8a)", "Exception: External interrupt (0x8b)", "Exception: External interrupt (0x8c)", "Exception: External interrupt (0x8d)", "Exception: External interrupt (0x8e)", "Exception: External interrupt (0x8f)", "Exception: External interrupt (0x90)", "Exception: External interrupt (0x91)", "Exception: External interrupt (0x92)", "Exception: External interrupt (0x93)", "Exception: External interrupt (0x94)", "Exception: External interrupt (0x95)", "Exception: External interrupt (0x96)", "Exception: External interrupt (0x97)", "Exception: External interrupt (0x98)", "Exception: External interrupt (0x99)", "Exception: External interrupt (0x9a)", "Exception: External interrupt (0x9b)", "Exception: External interrupt (0x9c)", "Exception: External interrupt (0x9d)", "Exception: External interrupt (0x9e)", "Exception: External interrupt (0x9f)", "Exception: External interrupt (0xa0)", "Exception: External interrupt (0xa1)", "Exception: External interrupt (0xa2)", "Exception: External interrupt (0xa3)", "Exception: External interrupt (0xa4)", "Exception: External interrupt (0xa5)", "Exception: External interrupt (0xa6)", "Exception: External interrupt (0xa7)", "Exception: External interrupt (0xa8)", "Exception: External interrupt (0xa9)", "Exception: External interrupt (0xaa)", "Exception: External interrupt (0xab)", "Exception: External interrupt (0xac)", "Exception: External interrupt (0xad)", "Exception: External interrupt (0xae)", "Exception: External interrupt (0xaf)", "Exception: External interrupt (0xb0)", "Exception: External interrupt (0xb1)", "Exception: External interrupt (0xb2)", "Exception: External interrupt (0xb3)", "Exception: External interrupt (0xb4)", "Exception: External interrupt (0xb5)", "Exception: External interrupt (0xb6)", "Exception: External interrupt (0xb7)", "Exception: External interrupt (0xb8)", "Exception: External interrupt (0xb9)", "Exception: External interrupt (0xba)", "Exception: External interrupt (0xbb)", "Exception: External interrupt (0xbc)", "Exception: External interrupt (0xbd)", "Exception: External interrupt (0xbe)", "Exception: External interrupt (0xbf)", "Exception: External interrupt (0xc0)", "Exception: External interrupt (0xc1)", "Exception: External interrupt (0xc2)", "Exception: External interrupt (0xc3)", "Exception: External interrupt (0xc4)", "Exception: External interrupt (0xc5)", "Exception: External interrupt (0xc6)", "Exception: External interrupt (0xc7)", "Exception: External interrupt (0xc8)", "Exception: External interrupt (0xc9)", "Exception: External interrupt (0xca)", "Exception: External interrupt (0xcb)", "Exception: External interrupt (0xcc)", "Exception: External interrupt (0xcd)", "Exception: External interrupt (0xce)", "Exception: External interrupt (0xcf)", "Exception: External interrupt (0xd0)", "Exception: External interrupt (0xd1)", "Exception: External interrupt (0xd2)", "Exception: External interrupt (0xd3)", "Exception: External interrupt (0xd4)", "Exception: External interrupt (0xd5)", "Exception: External interrupt (0xd6)", "Exception: External interrupt (0xd7)", "Exception: External interrupt (0xd8)", "Exception: External interrupt (0xd9)", "Exception: External interrupt (0xda)", "Exception: External interrupt (0xdb)", "Exception: External interrupt (0xdc)", "Exception: External interrupt (0xdd)", "Exception: External interrupt (0xde)", "Exception: External interrupt (0xdf)", "Exception: External interrupt (0xe0)", "Exception: External interrupt (0xe1)", "Exception: External interrupt (0xe2)", "Exception: External interrupt (0xe3)", "Exception: External interrupt (0xe4)", "Exception: External interrupt (0xe5)", "Exception: External interrupt (0xe6)", "Exception: External interrupt (0xe7)", "Exception: External interrupt (0xe8)", "Exception: External interrupt (0xe9)", "Exception: External interrupt (0xea)", "Exception: External interrupt (0xeb)", "Exception: External interrupt (0xec)", "Exception: External interrupt (0xed)", "Exception: External interrupt (0xee)", "Exception: External interrupt (0xef)", "Exception: External interrupt (0xf0)", "Exception: External interrupt (0xf1)", "Exception: External interrupt (0xf2)", "Exception: External interrupt (0xf3)", "Exception: External interrupt (0xf4)", "Exception: External interrupt (0xf5)", "Exception: External interrupt (0xf6)", "Exception: External interrupt (0xf7)", "Exception: External interrupt (0xf8)", "Exception: External interrupt (0xf9)", "Exception: External interrupt (0xfa)", "Exception: External interrupt (0xfb)", "Exception: External interrupt (0xfc)", "Exception: External interrupt (0xfd)", "Exception: External interrupt (0xfe)", "Exception: External interrupt (0xff)"
};

isr interruptHandlers[256];

idt_register idt_reg;

idt_gate idt[256];

#pragma endregion Variables

#pragma region External assembly functions

extern void isr0();
extern void isr1();
extern void isr2();
extern void isr3();
extern void isr4();
extern void isr5();
extern void isr6();
extern void isr7();
extern void isr8();
extern void isr9();
extern void isr10();
extern void isr11();
extern void isr12();
extern void isr13();
extern void isr14();
extern void isr15();
extern void isr16();
extern void isr17();
extern void isr18();
extern void isr19();
extern void isr20();
extern void isr21();
extern void isr22();
extern void isr23();
extern void isr24();
extern void isr25();
extern void isr26();
extern void isr27();
extern void isr28();
extern void isr29();
extern void isr30();
extern void isr31();

extern void irq0();
extern void irq1();
extern void irq2();
extern void irq3();
extern void irq4();
extern void irq5();
extern void irq6();
extern void irq7();
extern void irq8();
extern void irq9();
extern void irq10();
extern void irq11();
extern void irq12();
extern void irq13();
extern void irq14();
extern void irq15();

#pragma endregion External assembly functions

#pragma region Function prototypes

void isr_handler(registers *reg);
void register_interrupt_handler(uint8_t n, isr handler);
void irq_handler(registers *reg);
void load_idt();
void isr_install();
void print_letter(uint8_t scan_code);
static void keyboard_callback(registers *reg);
void initialize_keyboard();

#pragma endregion Function prototypes

#endif