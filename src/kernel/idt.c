#include <idt.h>
#include <macro.h>
#include <timer.h>
#include <type.h>
struct IDTGate IDT[0xFF];
struct IDTp    Ip;

extern UPointer irq0();
extern UPointer irq8();

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
    //for(Unsig32 i = 0; i < 0x20; i++) {
    //    IDTCreateGate
    //}
    struct {
        struct IDTp    header;
        struct IDTGate gates[0xFF];
    } idt = {0};
    
    
}