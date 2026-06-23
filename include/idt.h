#ifndef IDT_H_ENVE
#define IDT_H_ENVE
#include "type.h"
#include "macro.h"

packed struct IDTGate {
    Unsig16 offset_low;
    Unsig16 selector;
    Unsig8  zero;
    Unsig8  flags;
    Unsig16 offset_high;
};

packed struct IDTp {
    Unsig16 size;
    Unsig32 ptr;
};

void IDTInsertGate(Unsig8 num, Unsig32 base, Unsig16 sel, Unsig8 flags);
void IDTLoad(void);

#endif /* IDT_H_ENVE */
