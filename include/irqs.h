#ifndef IRQS_H
#define IRQS_H
#include "macro.h"
#include "type.h"
#include "serial.h"

struct RegsFrame {
    Unsig32 edi;      
    Unsig32 esi;      
    Unsig32 ebp;      
    Unsig32 esp;      
    Unsig32 ebx;      
    Unsig32 edx;      
    Unsig32 ecx;      
    Unsig32 eax;      
    Unsig32 ds;       
    Unsig32 errcode;  
    Unsig32 int_no;   
    Unsig32 eip;      
    Unsig32 cs;       
    Unsig32 eflags;   
} align(4);
void CIRQErr(struct RegsFrame *r);
void CIRQNonErr(struct RegsFrame *r);
#endif /* IRQS_H */
