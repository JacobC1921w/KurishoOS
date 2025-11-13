#include <stdint.h>

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

typedef struct {
    uint16_t low_offset;
    uint16_t selector;
    uint8_t always_0;
    uint8_t flags;
    uint16_t high_offset;
} __attribute__((packed)) idt_gate;

#define low_16(address) (uint16_t) ((address) & 0xFFFF)
#define high_16(address) (uint16_t) (((address) >> 16) & 0xFFFF)

idt_gate idt[256];

idt_gate set_idt_gate(int n, uint16_t handler) {
    idt[n].low_offset = low_16(handler);
    idt[n].selector = 0x08;
    idt[n].always_0 = 0;
    idt[n].flags = 0x8E;
    idt[n].high_offset = high_16(handler);
}

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

typedef struct {
    uint32_t ds;
    uint32_t edi, esi, ebp, esp, ebx, edx, ecx, eax;
    uint32_t interrupt_number, error_code;
    uint32_t eip, cs, eflags, useresp, ss;
} registers;

void isr_handler(registers *reg) {
    print_string(exception_messages[reg->interrupt_number]);
    print_string("\n");
}

typedef void (*isr)(registers *);
isr interruptHandlers[256];

void register_interrupt_handler(uint8_t n, isr handler) {
    interruptHandlers[n] = handler;
}

void irq_handler(registers *reg) {
    if (interruptHandlers[reg->interrupt_number] != 0) {
        isr handler = interruptHandlers[reg->interrupt_number];
        handler(reg);
    }

    port_byte_out(0x20, 0x20);
    if (reg->interrupt_number < 40) {
        port_byte_out(0xA0, 0x20);
    }
}

typedef struct {
    uint16_t limit;
    uint32_t base;
} __attribute__((packed)) idt_register;

idt_register idt_reg;

void load_idt() {
    idt_reg.base = (uint32_t) &idt;
    idt_reg.limit = idt_entries * sizeof(idt_gate) - 1;
    asm volatile("lidt (%0)" : : "r" (&idt_reg));
}

void isr_install() {
    set_idt_gate(0, (uint32_t) isr0);
    set_idt_gate(1, (uint32_t) isr1);
    set_idt_gate(2, (uint32_t) isr2);
    set_idt_gate(3, (uint32_t) isr3);
    set_idt_gate(4, (uint32_t) isr4);
    set_idt_gate(5, (uint32_t) isr5);
    set_idt_gate(6, (uint32_t) isr6);
    set_idt_gate(7, (uint32_t) isr7);
    set_idt_gate(8, (uint32_t) isr8);
    set_idt_gate(9, (uint32_t) isr9);
    set_idt_gate(10, (uint32_t) isr10);
    set_idt_gate(11, (uint32_t) isr11);
    set_idt_gate(12, (uint32_t) isr12);
    set_idt_gate(13, (uint32_t) isr13);
    set_idt_gate(14, (uint32_t) isr14);
    set_idt_gate(15, (uint32_t) isr15);
    set_idt_gate(16, (uint32_t) isr16);
    set_idt_gate(17, (uint32_t) isr17);
    set_idt_gate(18, (uint32_t) isr18);
    set_idt_gate(19, (uint32_t) isr19);
    set_idt_gate(20, (uint32_t) isr20);
    set_idt_gate(21, (uint32_t) isr21);
    set_idt_gate(22, (uint32_t) isr22);
    set_idt_gate(23, (uint32_t) isr23);
    set_idt_gate(24, (uint32_t) isr24);
    set_idt_gate(25, (uint32_t) isr25);
    set_idt_gate(26, (uint32_t) isr26);
    set_idt_gate(27, (uint32_t) isr27);
    set_idt_gate(28, (uint32_t) isr28);
    set_idt_gate(29, (uint32_t) isr29);
    set_idt_gate(30, (uint32_t) isr30);
    set_idt_gate(31, (uint32_t) isr31);

    port_byte_out(0x20, 0x11);
    port_byte_out(0xA0, 0x11);

    port_byte_out(0x21, 0x20);
    port_byte_out(0xA1, 0x28);

    port_byte_out(0x21, 0x04);
    port_byte_out(0xA1, 0x02);

    port_byte_out(0x21, 0x01);
    port_byte_out(0xA1, 0x01);

    port_byte_out(0x21, 0x0);
    port_byte_out(0xA1, 0x0);

    set_idt_gate(32, (uint32_t) irq0);
    set_idt_gate(33, (uint32_t) irq1);
    set_idt_gate(34, (uint32_t) irq2);
    set_idt_gate(35, (uint32_t) irq3);
    set_idt_gate(36, (uint32_t) irq4);
    set_idt_gate(37, (uint32_t) irq5);
    set_idt_gate(38, (uint32_t) irq6);
    set_idt_gate(39, (uint32_t) irq7);

    set_idt_gate(40, (uint32_t) irq8);
    set_idt_gate(41, (uint32_t) irq9);
    set_idt_gate(42, (uint32_t) irq10);
    set_idt_gate(43, (uint32_t) irq11);
    set_idt_gate(44, (uint32_t) irq12);
    set_idt_gate(45, (uint32_t) irq13);
    set_idt_gate(46, (uint32_t) irq14);
    set_idt_gate(47, (uint32_t) irq15);

    load_idt();
};
void print_letter(uint8_t scan_code) {
    switch (scan_code) {
        case 0x0:
            print_string("Key down: ERROR");
            break;
        case 0x01:
            print_string("Key down: escape");
            break;
        case 0x02:
            print_string("Key down: 1");
            break;
        case 0x03:
            print_string("Key down: 2");
            break;
        case 0x04:
            print_string("Key down: 3");
            break;
        case 0x05:
            print_string("Key down: 4");
            break;
        case 0x06:
            print_string("Key down: 5");
            break;
        case 0x07:
            print_string("Key down: 6");
            break;
        case 0x08:
            print_string("Key down: 7");
            break;
        case 0x09:
            print_string("Key down: 8");
            break;
        case 0x0A:
            print_string("Key down: 9");
            break;
        case 0x0B:
            print_string("Key down: 0");
            break;
        case 0x0C:
            print_string("Key down: -");
            break;
        case 0x0D:
            print_string("Key down: =");
            break;
        case 0x0E:
            print_string("Key down: backspace");
            break;
        case 0x0F:
            print_string("Key down: tab");
            break;
        case 0x10:
            print_string("Key down: Q");
            break;
        case 0x11:
            print_string("Key down: W");
            break;
        case 0x12:
            print_string("Key down: E");
            break;
        case 0x13:
            print_string("Key down: R");
            break;
        case 0x14:
            print_string("Key down: T");
            break;
        case 0x15:
            print_string("Key down: Y");
            break;
        case 0x16:
            print_string("Key down: U");
            break;
        case 0x17:
            print_string("Key down: I");
            break;
        case 0x18:
            print_string("Key down: O");
            break;
        case 0x19:
            print_string("Key down: P");
            break;
        case 0x1A:
            print_string("Key down: [");
            break;
        case 0x1B:
            print_string("Key down: ]");
            break;
        case 0x1C:
            print_string("Key down: enter");
            break;
        case 0x1D:
            print_string("Key down: left control");
            break;
        case 0x1E:
            print_string("Key down: A");
            break;
        case 0x1F:
            print_string("Key down: S");
            break;
        case 0x20:
            print_string("Key down: D");
            break;
        case 0x21:
            print_string("Key down: F");
            break;
        case 0x22:
            print_string("Key down: G");
            break;
        case 0x23:
            print_string("Key down: H");
            break;
        case 0x24:
            print_string("Key down: J");
            break;
        case 0x25:
            print_string("Key down: K");
            break;
        case 0x26:
            print_string("Key down: L");
            break;
        case 0x27:
            print_string("Key down: ;");
            break;
        case 0x28:
            print_string("Key down: '");
            break;
        case 0x29:
            print_string("Key down: `");
            break;
        case 0x2A:
            print_string("Key down: left shift");
            break;
        case 0x2B:
            print_string("Key down: \\");
            break;
        case 0x2C:
            print_string("Key down: Z");
            break;
        case 0x2D:
            print_string("Key down: X");
            break;
        case 0x2E:
            print_string("Key down: C");
            break;
        case 0x2F:
            print_string("Key down: V");
            break;
        case 0x30:
            print_string("Key down: B");
            break;
        case 0x31:
            print_string("Key down: N");
            break;
        case 0x32:
            print_string("Key down: M");
            break;
        case 0x33:
            print_string("Key down: ,");
            break;
        case 0x34:
            print_string("Key down: .");
            break;
        case 0x35:
            print_string("Key down: /");
            break;
        case 0x36:
            print_string("Key down: right shift");
            break;
        case 0x37:
            print_string("Key down: (keypad) *");
            break;
        case 0x38:
            print_string("Key down: left alt");
            break;
        case 0x39:
            print_string("Key down: space");
            break;
        case 0x3A:
            print_string("Key down: CapsLock");
            break;
        case 0x3B:
            print_string("Key down: F1");
            break;
        case 0x3C:
            print_string("Key down: F2");
            break;
        case 0x3D:
            print_string("Key down: F3");
            break;
        case 0x3E:
            print_string("Key down: F4");
            break;
        case 0x3F:
            print_string("Key down: F5");
            break;
        case 0x40:
            print_string("Key down: F6");
            break;
        case 0x41:
            print_string("Key down: F7");
            break;
        case 0x42:
            print_string("Key down: F8");
            break;
        case 0x43:
            print_string("Key down: F9");
            break;
        case 0x44:
            print_string("Key down: F10");
            break;
        case 0x45:
            print_string("Key down: NumberLock");
            break;
        case 0x46:
            print_string("Key down: ScrollLock");
            break;
        case 0x47:
            print_string("Key down: (keypad) 7");
            break;
        case 0x48:
            print_string("Key down: arrow up"); //(keypad) 8 ?
            break;
        case 0x49:
            print_string("Key down: page up"); //(keypad) 9 ?
            break;
        case 0x4A:
            print_string("Key down: (keypad) -");
            break;
        case 0x4B:
            print_string("Key down: arrow left"); //(keypad) 4 ?
            break;
        case 0x4C:
            print_string("Key down: (keypad) 5");
            break;
        case 0x4D:
            print_string("Key down: arrow right"); //(keypad) 6 ?
            break;
        case 0x4E:
            print_string("Key down: (keypad) +");
            break;
        case 0x4F:
            print_string("Key down: (keypad) 1");
            break;
        case 0x50:
            print_string("Key down: arrow down"); //(keypad) 2 ?
            break;
        case 0x51:
            print_string("Key down: page down"); //(keypad) 3 ?
            break;
        case 0x52:
            print_string("Key down: insert"); //(keypad) 0 ?
            break;
        case 0x53:
            print_string("Key down: delete"); //(keypad) . ?
            break;
        case 0x57:
            print_string("Key down: F11");
            break;
        case 0x58:
            print_string("Key down: F12");
            break;
        default:
            if (scan_code <= 0x7f) {
            print_string("Key down: Unknown");
            } else if (scan_code <= 0x58 + 0x80) {
            print_string("Key up: ");
                print_letter(scan_code - 0x80);
            } else {
            print_string("Key up: Unknown");
            }
            break;
    }
}

static void keyboard_callback(registers *reg) {
    uint8_t scan_code = port_byte_in(0x60);
    print_letter(scan_code);
    print_string("\n");
}

void initialize_keyboard() {
    register_interrupt_handler(IRQ1, keyboard_callback);
}