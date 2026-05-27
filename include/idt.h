#ifndef IDT_H_ENVE
#define IDT_H_ENVE
#include "type.h"


struct IDTGate {
    Unsig16 offset_low;
    Unsig16 selector;
    Unsig8  zero;
    Unsig8  flags;
    Unsig16 offset_high;
} __attribute__((packed));

struct IDTp {
    Unsig16 size;
    Unsig32 ptr;
} __attribute__((packed));

void IDTInsertGate(Unsig8 num, Unsig32 base, Unsig16 sel, Unsig8 flags);
void IDTLoad(void);
void Interrupt(Unsig8 num);


#endif /* IDT_H_ENVE */
