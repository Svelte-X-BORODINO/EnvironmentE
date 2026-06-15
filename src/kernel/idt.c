#include <idt.h>
#include <macro.h>
#include <serial.h>
#include <timer.h>
#include <kbd.h>
#include <type.h>
#include <pic.h>
indata struct IDTGate IDT[0xFF];
indata struct IDTp    Ip;

extern UPointer IRQ32();
extern UPointer IRQ33();

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
    for (Unsig32 i = 0; i < 0xFF; i++) {
        IDTCreateGate(i, (Unsig32)0, 0x08, 0x8E);
    }
    IDTCreateGate(0x20, (Unsig32)IRQ32, 0x08, 0x8E);
    IDTCreateGate(0x21, (Unsig32)IRQ33, 0x08, 0x8E);
    
    Ip.size = sizeof(IDT) - 1;  
    Ip.ptr  = (Unsig32)IDT;     
    
    _Static_assert(sizeof(struct IDTGate) == 8, "IDTGate size must be 8 bytes");
    _Static_assert(sizeof(struct IDTp)    == 6, "IDTp size MUST be 6 bytes");

    LIDT(&Ip);
    sti;
}
