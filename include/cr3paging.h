#ifndef CR3_PAGING_ENVE
#define CR3_PAGING_ENVE

#include "type.h"
#include "macro.h"

packed struct PageTableEntry {
    Unsig16 flags : 9; // bit 8 - PAT
    Unsig8  avl   : 3;
    Unsig32 frame : 20;
};


packed struct PageDirectoryEntry {
    Unsig16 flags : 9; // bit 8 - page size
    Unsig8  avl   : 3;
    Unsig32 frame : 20;
};

UPointer PagingInit();
UPointer MapAPage(Unsig32 virtaddr, Unsig32 physaddr, Unsig32 flags);

#endif /* CR3_PAGING_ENVE */
