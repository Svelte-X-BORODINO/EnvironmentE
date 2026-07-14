#ifndef CR3_PAGING_H_ENVE
#define CR3_PAGING_H_ENVE

#include "type.h"
#include "macro.h"

#define PG_PRESENT 0x1
#define PG_RW 0x2
#define PG_USR 0x4
#define pages *4096
#define KB *1024

UPointer PagingInit();
UPointer MapAPage(Unsig32 virtaddr, Unsig32 physaddr, Unsig32 flags);

#endif /* CR3_PAGING_H_ENVE */
