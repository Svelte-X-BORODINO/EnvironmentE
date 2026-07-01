#include <type.h>
#include <macro.h> // paged macro - 4096-align
#include <mb_memmap.h> // DumbPMMAlloc()
#include <cr3paging.h>

paged Unsig32 pd[1024];

static UPointer TLBFlush() {
    Unsig32 cr3;
    VASM ("mov %%cr3, %0" : "=r"(cr3));
    VASM ("mov %0, %%cr3" :: "r"(cr3) : "memory");
}

UPointer PagingInit() {
    for (int i = 0; i < 1024; i++) {
        pd[i] = 0;
    }

    for (int i = 0; i < 64; i++) {
        Unsig32 pt_phys = DumbPMMAlloc(4096);
        paged Unsig32 *pt = (paged Unsig32 *)pt_phys;

        for (int j = 0; j < 1024; j++) {
            pt[j] = ((i *1024 + j /* OMG AI PREDICT FORMULA REFERENCE */) * 4096) | PG_PRESENT | PG_RW;
        }

        pd[i] = pt_phys | PG_PRESENT | PG_RW;
    }

    VASM 
    (
    "mov %0, %%cr3\n"
    :: "r"((Unsig32)pd) : "memory");
    TLBFlush();
    CR0(31);
}