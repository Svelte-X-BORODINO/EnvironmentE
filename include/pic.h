#ifndef PIC_H_ENVE
#define PIC_H_ENVE
#include "type.h"

#define PIC1_CMD  0x20
#define PIC1_DATA 0x21
#define PIC2_CMD  0xA0
#define PIC2_DATA 0xA1

UPointer EOI(Unsig8 num);
UPointer Remap(Unsig8 offset1, Unsig8 offset2);
UPointer PICInit();
UPointer PICUnmask(Unsig8 irq);
UPointer PICMask(Unsig8 irq);

#endif /* PIC_H_ENVE */
