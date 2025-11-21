#include <stdbool.h>

#include "keyboard.h"
#include "../display/display.h"
#include "../port/port.h"
#include "../data_manipulation/data_manipulation.h"
#include "../memory/memory.h"
#include "../../shell/shell.h"

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
    "Exception: Control protection exception"
};

void isr_handler(registers *reg) {

    if (reg->interrupt_number < 22) {
        println_string(exception_messages[reg->interrupt_number]);
    } else if (reg->interrupt_number >= 22 && reg->interrupt_number <= 31) {
        char interrupt_string[11];
        print_string("Exception: Future reservation (interrupt number: ");
        print_string(uint_32_base_convert(reg->interrupt_number, interrupt_string, 10));
        print_string(")\n");
    } else if (reg->interrupt_number > 31 && reg->interrupt_number <= 224) {
        char interrupt_string[11];
        print_string("Exception: External interrupt (0x");
        print_string(uint_32_base_convert(reg->interrupt_number, interrupt_string, 16));
        print_string(")\n");
    } else {
        char interrupt_string[11];
        print_string("Exception: Unrecognised interrupt number (");
        print_string(uint_32_base_convert(reg->interrupt_number, interrupt_string, 10));
        print_string(")\n");
    }
}

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

 idt_register idt_reg;
 idt_gate idt[256];

void load_idt() {
    idt_reg.base = (uint32_t) &idt;
    idt_reg.limit = IDT_ENTRIES * sizeof(idt_gate) - 1;
    asm volatile("lidt (%0)" : : "r" (&idt_reg));
}

idt_gate set_idt_gate(int n, uint16_t handler) {
    idt[n].low_offset = LOW16(handler);
    idt[n].selector = 0x08;
    idt[n].always_0 = 0;
    idt[n].flags = 0x8E;
    idt[n].high_offset = HIGH16(handler);
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

char scan_code_chars[] = {
    '?', '?', '1', '2', '3', '4', '5', '6', 
    '7', '8', '9', '0', '-', '=', '?', '?',
    'Q', 'W', 'E', 'R', 'T', 'Y', 'U', 'I',
    'O', 'P', '[', ']', '?', '?', 'A', 'S',
    'D', 'F', 'G', 'H', 'J', 'K', 'L', ';',
    '\'', '`', '?', '\\', 'Z', 'X', 'C', 'V',
    'B', 'N', 'M', ',', '.', '/', '?', '*',
    '?', ' ', '?', '?', '?', '?', '?', '?',
    '?', '?', '?', '?', '?', '?', '?', '7',
    '?', '?', '-', '?', '5', '?', '+', '1',
    '?', '?', '?', '?', '?', '?'
};

char *scan_code_specials[] = {
    "ERROR", "Escape", "?", "?", "?", "?", "?", "?", 
    "?", "?", "?", "?", "?", "?", "Backspace", "Tab",
    "?", "?", "?", "?", "?", "?", "?", "?",
    "?", "?", "?", "?", "Enter", "Left control", "?", "?",
    "?", "?", "?", "?", "?", "?", "?", "?",
    "?", "?", "Left shift", "?", "?", "?", "?", "?",
    "?", "?", "?", "?", "?", "?", "Right shift", "?",
    "Left alt", "?", "Caps lock", "F1", "F2", "F3", "F4", "F5",
    "F6", "F7", "F8", "F9", "F10", "Num lock", "Scroll lock", "?",
    "Arrow up", "Page up", "?", "Arrow left", "?", "Arrow right", "?", "?",
    "Arrow down", "Page down", "Insert", "Delete", "F11", "F12"
};

char key_buffer[256];

bool backspace(char buffer[]) {
    int string_len = string_length(buffer);
    if (string_len > 0) {
        key_buffer[string_len - 1] = '\0';
        return true;
    } else {
        return false;
    }
}

bool get_lock_status(int lock_bit) {
    uint8_t status_byte;
    uint8_t ack_byte;

    while (port_byte_in(PS2_CMD_PORT) & PS2_STATUS_IBF);
    port_byte_out(PS2_DATA_PORT, KB_CMD_SET_LED); 

    while (!(port_byte_in(PS2_CMD_PORT) & PS2_STATUS_OBF));
    ack_byte = port_byte_in(PS2_DATA_PORT);
    
    if (ack_byte != KB_ACK) {
        return false; 
    }

    while (port_byte_in(PS2_CMD_PORT) & PS2_STATUS_IBF);
    port_byte_out(PS2_DATA_PORT, 0x00);

    while (!(port_byte_in(PS2_CMD_PORT) & PS2_STATUS_OBF));
    port_byte_in(PS2_DATA_PORT); 
    
    while (!(port_byte_in(PS2_CMD_PORT) & PS2_STATUS_OBF));
    status_byte = port_byte_in(PS2_DATA_PORT);

    return (status_byte & lock_bit) != 0;
}

bool set_lock_status(uint8_t lock_bit) {
    uint8_t ack_byte;

    while (port_byte_in(PS2_CMD_PORT) & PS2_STATUS_IBF);
    port_byte_out(PS2_DATA_PORT, KB_CMD_SET_LED); 

    while (!(port_byte_in(PS2_CMD_PORT) & PS2_STATUS_OBF));
    ack_byte = port_byte_in(PS2_DATA_PORT);
    
    if (ack_byte != KB_ACK) {
        return false;
    }

    while (port_byte_in(PS2_CMD_PORT) & PS2_STATUS_IBF);
    port_byte_out(PS2_DATA_PORT, lock_bit);

    while (!(port_byte_in(PS2_CMD_PORT) & PS2_STATUS_OBF));
    ack_byte = port_byte_in(PS2_DATA_PORT);
    
    if (ack_byte != KB_ACK) {
        return false;
    }
    
    return true; 
}

uint8_t current_led_status_byte = 0x00;
bool is_shift_pressed = false;

uint8_t toggle_lock_led(uint8_t lock_bit) {
    current_led_status_byte ^= lock_bit;
    set_lock_status(current_led_status_byte);
    return current_led_status_byte;
}

static void keyboard_callback(registers *reg) {
    uint8_t scan_code = port_byte_in(0x60);
    
    if (scan_code & 0x80) {
        uint8_t make_code = scan_code & 0x7F; 

        if (make_code == 0x2A || make_code == 0x36) {
            is_shift_pressed = false;
        }
        return; 
    }
    

    if (scan_code > SCAN_CODE_MAX) return;

    if (scan_code == 0x2A || scan_code == 0x36) {
        is_shift_pressed = true;
        return;
    }

    if (scan_code_chars[(int) scan_code] == '?') {
        char *scan_code_special = scan_code_specials[(int) scan_code];
        if (scan_code_special == "Backspace") {
            if (backspace(key_buffer)) {
                print_backspace();
            }
        } else if (scan_code_special == "Enter") {
            print_string("\n");
            parse_command(key_buffer);
            key_buffer[0] = '\0';

        } else if (scan_code_special == "Caps lock") {
            toggle_lock_led(CAPS_LOCK_BIT);

        } else if (scan_code_special == "Num lock") {
            toggle_lock_led(NUM_LOCK_BIT);

        } else if (scan_code_special == "Scroll lock") {
            toggle_lock_led(SCROLL_LOCK_BIT);

        }
        return; 
    } else { 
        char letter = scan_code_chars[(int) scan_code];

        if (letter >= 'A' && letter <= 'Z') {
            
            bool caps_on = (current_led_status_byte & CAPS_LOCK_BIT);
            bool shift_on = is_shift_pressed;

            if (caps_on == shift_on) {
                letter = char_lower(letter);
            }
        }
        
        append_char(key_buffer, letter);

        char str[2] = {letter, '\0'};
        print_string(str);
        }
}

void initialize_keyboard() {
    register_interrupt_handler(IRQ1, keyboard_callback);
}