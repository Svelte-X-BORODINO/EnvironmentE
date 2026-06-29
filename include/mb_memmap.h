#ifndef MB_MEMMAP_H_ENVE
#define MB_MEMMAP_H_ENVE
#include "macro.h"
#include "type.h"

packed struct MBMapEntry {
    Unsig32  size;        
    Unsig64  base_addr;
    Unsig64  length;
    Unsig32  type;        
};

packed struct MBInfo {
    Unsig32 flags;
    Unsig32 lower;
    Unsig32 upper;
    Unsig32 device;
    Unsig32 cmdline; // WTF?
    Unsig32 mods_count;
    Unsig32 mods_addr;
    Unsig32 syms[4]; // WTF?!
    Unsig32 mmap_length;
    Unsig32 mmap_addr;
};

UPointer DumbPMMInit(Unsig32 mbinfo);
//UPointer DumbPMMAlloc(size_t size);
//UPointer DumbPMMFree(UPointer *ptr);

#endif /* MB_MEMMAP_H_ENVE */
