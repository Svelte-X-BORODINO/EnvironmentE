#include <idt.h>
#include <macro.h>
#include <timer.h>
#include <type.h>
#include <pic.h>
struct IDTGate IDT[0xFF];
struct IDTp    Ip;

extern UPointer irq0();
extern UPointer irq8();
extern UPointer another_irq();

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
    for (Unsig32 i = 0; i < 0x20; i++) {
        IDTCreateGate(i, (Unsig32)another_irq, 0x08, 0x8E);
    }
    IDTCreateGate(0x00, (Unsig32)irq0, 0x08, 0x8E);
    IDTCreateGate(0x08, (Unsig32)irq8, 0x08, 0x8E);
    IDTCreateGate(0x20, (Unsig32)IRQ32, 0x08, 0x8E);
    
    Ip.size = sizeof(IDT) - 1;  
    Ip.ptr  = (Unsig32)IDT;     
    
    char msg[] = "IDTGate size: \n";
    char msg2[] = "IDTp size: \n";
    msg[13] = '0' + sizeof(struct IDTGate);
    msg2[10] = '0' + sizeof(struct IDTp);
    OutS(msg);
    OutS(msg2);

    LIDT(&Ip);
    sti;
}
