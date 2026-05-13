#include <idt.h>

struct IDTGate IDT[0xFF];
struct IDTp    Ip;



void IDTCreateGate(int vector, Unsig32 handler_addr, Unsig16 sel, Unsig8 flags) {
    struct IDTGate *gate = &IDT[vector]; 

    gate->offset_low = handler_addr & 0xFFFF;
    gate->selector = sel;
    gate->zero = 0;      
    gate->flags = flags; 
    gate->offset_high = (handler_addr >> 16) & 0xFFFF;
}

void IDTLoad() {

}