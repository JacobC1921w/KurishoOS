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