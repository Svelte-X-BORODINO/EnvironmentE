#ifndef IRQS_H
#define IRQS_H
#include "macro.h"
#include "type.h"
#include "serial.h"

struct RegsFrame {
    Unsig32 edi;        // ESP+56
    Unsig32 esi;        // ESP+52
    Unsig32 ebp;        // ESP+48
    Unsig32 esp;        // ESP+44
    Unsig32 ebx;        // ESP+30
    Unsig32 edx;        // ESP+36
    Unsig32 ecx;        // ESP+32
    Unsig32 eax;        // ESP+28
    Unsig32 ds;         // ESP+24
    Unsig32 cr2;        // ESP+20
    Unsig32 errcode;    // ESP+16
    Unsig32 int_no;     // ESP+12
    Unsig32 eip;        // ESP+8
    Unsig32 cs;         // ESP+4
    Unsig32 eflags;     // ESP+0
} align(4);
void CIRQErr(struct RegsFrame *r);
void CIRQNonErr(struct RegsFrame *r);
#endif /* IRQS_H */
