#include <idt.h>
#include <macro.h>
#include <serial.h>
#include <timer.h>
#include <kbd.h>
#include <type.h>
#include <pic.h>
indata struct IDTGate IDT[0xFF];
indata struct IDTp    Ip;

extern UPointer irq0();
extern UPointer irq1();
extern UPointer irq2();
extern UPointer irq3();
extern UPointer irq4();
extern UPointer irq5();
extern UPointer irq6();
extern UPointer irq7();
extern UPointer irq8();
extern UPointer irq9();
extern UPointer irq10();
extern UPointer irq11();
extern UPointer irq12();
extern UPointer irq13();
extern UPointer Page();
extern UPointer irq15();
extern UPointer irq16();
extern UPointer irq17();
extern UPointer irq18();
extern UPointer irq19();
extern UPointer irq20();
extern UPointer irq21();
extern UPointer irqres();
extern UPointer IRQ32();
extern UPointer IRQ36();

#define LIDT(p) VASM ("lidt %0" : : "m"(*p) : "memory")

void IDTCreateGate
(Unsig8 vector, Unsig32 handler_addr, Unsig16 sel, Unsig8 flags) {
    struct IDTGate *gate = &IDT[vector]; 

    gate->offset_low = handler_addr & 0xFFFF;
    gate->selector = sel;
    gate->zero = 0;      
    gate->flags = flags; 
    gate->offset_high = (handler_addr >> 16) & 0xFFFF;
}

void IDTLoad
(void) {
    IDTCreateGate(0x00, (Unsig32)irq0, 0x08, 0x8E);
    IDTCreateGate(0x01, (Unsig32)irq1, 0x08, 0x8E);
    IDTCreateGate(0x02, (Unsig32)irq2, 0x08, 0x8E);
    IDTCreateGate(0x03, (Unsig32)irq3, 0x08, 0x8E);
    IDTCreateGate(0x04, (Unsig32)irq4, 0x08, 0x8E);
    IDTCreateGate(0x05, (Unsig32)irq5, 0x08, 0x8E);
    IDTCreateGate(0x06, (Unsig32)irq6, 0x08, 0x8E);
    IDTCreateGate(0x07, (Unsig32)irq7, 0x08, 0x8E);
    IDTCreateGate(0x08, (Unsig32)irq8, 0x08, 0x8E);
    IDTCreateGate(0x09, (Unsig32)irq9, 0x08, 0x8E);
    IDTCreateGate(0x0A, (Unsig32)irq10, 0x08, 0x8E);
    IDTCreateGate(0x0B, (Unsig32)irq11, 0x08, 0x8E);
    IDTCreateGate(0x0C, (Unsig32)irq12, 0x08, 0x8E);
    IDTCreateGate(0x0D, (Unsig32)irq13, 0x08, 0x8E);
    IDTCreateGate(0x0E, (Unsig32)Page, 0x08, 0x8E);
    IDTCreateGate(0x0F, (Unsig32)irq15, 0x08, 0x8E);
    IDTCreateGate(0x10, (Unsig32)irq16, 0x08, 0x8E);
    IDTCreateGate(0x11, (Unsig32)irq17, 0x08, 0x8E);
    IDTCreateGate(0x12, (Unsig32)irq18, 0x08, 0x8E);
    IDTCreateGate(0x13, (Unsig32)irq19, 0x08, 0x8E);
    IDTCreateGate(0x14, (Unsig32)irq20, 0x08, 0x8E);
    IDTCreateGate(0x15, (Unsig32)irq21, 0x08, 0x8E);
    for (Unsig8 i = 0x16; i < 0xFF; i++) {
        IDTCreateGate(i, (Unsig32)irqres, 0x08, 0x8E);
    }
    IDTCreateGate(0x20, (Unsig32)IRQ32, 0x08, 0x8E);
    IDTCreateGate(0x24, (Unsig32)IRQ36, 0x08, 0x8E);
    Ip.size = sizeof(IDT) - 1;
    Ip.ptr = (Unsig32)IDT;
    
    _Static_assert(sizeof(struct IDTGate) == 8, "IDTGate size must be 8 bytes");
    _Static_assert(sizeof(struct IDTp)    == 6, "IDTp size MUST be 6 bytes");

    LIDT(&Ip);
    sti;
}
