#ifndef RING3_H_ENVE
#define RING3_H_ENVE
#include "type.h"
#include "macro.h"

packed struct segregs {
    Unsig16 es;        
    Unsig16 cs;        
    Unsig16 ss;        
    Unsig16 ds;        
    Unsig16 fs;        
    Unsig16 gs;
};

packed struct TaskRegs {
    Unsig32 eip;       
    Unsig32 eflags;    
    Unsig32 eax;       
    Unsig32 ecx;       
    Unsig32 edx;       
    Unsig32 ebx;       
    Unsig32 esp;       
    Unsig32 ebp;       
    Unsig32 esi;       
    Unsig32 edi;      

    struct segregs s;

    Unsig128 fpr[16];
    Unsig128 xmm[8];
};

packed struct TSS {
    Unsig32 prevtss;
    Unsig32 esp0;
    Unsig32 ss0;
    Unsig32 esp1, ss1;
    Unsig32 esp2, ss2;
    Unsig32 cr3;

    Unsig32 eip;    
    Unsig32 eflags; 
    Unsig32 eax;    
    Unsig32 ecx;    
    Unsig32 edx;    
    Unsig32 ebx;    
    Unsig32 esp;    
    Unsig32 ebp;    
    Unsig32 esi;    
    Unsig32 edi;    
    Unsig32 es;     
    Unsig32 cs;     
    Unsig32 ss;     
    Unsig32 ds;     
    Unsig32 fs;     
    Unsig32 gs;

    Unsig32 ldt;
    Unsig16 trap;
    Unsig32 iobitmap;
};



#endif /* RING3_H_ENVE */
