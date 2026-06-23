#ifndef GDT_H_ENVE
#define GDT_H_ENVE
#include "type.h"
#include "macro.h"

#define GR (1 << 7)
#define DB (1 << 6)

packed struct GDTp {
    Unsig16  size;
    Unsig32  ptr;
};

// limit, base (l, m, h), gran, access
packed struct GDTEntry {
    Unsig16 limit_low;   
    Unsig16 base_low;    
    Unsig8  base_mid;    
    Unsig8  access;      
    Unsig8  gran;        
    Unsig8  base_high;   
};

UPointer GDTLoad(); // init
#endif /* GDT_H_ENVE */
