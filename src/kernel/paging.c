#include <type.h>
#include <macro.h> // paged macro - 4096-align
#include <mb_memmap.h> // DumbPMMAlloc()
#include <log.h> // LogF()
#include <cr3paging.h>

paged Unsig32 pd[1024];


static UPointer TLBFlush
() {
    Unsig32 cr3;
    VASM ("mov %%cr3, %0" : "=r"(cr3));
    VASM ("mov %0, %%cr3" :: "r"(cr3) : "memory");
}

static UPointer INVLPG(Unsig32 p) {
    if (p & (1 pages)-1) LogF("CR3", "p is not page aligned!");
    VASM 
    (
        "invlpg (%0)\n"
        :: "r"(p) : "memory"
    );
}

UPointer PagingInit
() {
    for (int i = 0; i < 1024; i++) {
        pd[i] = 0;
    }

    for (int i = 0; i < 64; i++) {
        paged Unsig32 *pt = (Unsig32 *)DumbPMMAlloc(4096);

        for (int j = 0; j < 1024; j++) {
            pt[j] = ((i pages + j /* OMG AI PREDICT FORMULA REFERENCE */) * 4096) | PG_PRESENT | PG_RW | PG_USR;
        }

        pd[i] = (Unsig32)pt | PG_PRESENT | PG_RW | PG_USR;
    }

    VASM 
    (
        "mov %0, %%cr3\n"
        :: "r"((Unsig32)pd) : "memory"
    );

    // someone : are you an idiot?!
    // me : no, i'm m4a1 X CS
    MapAPage(0x3FA00000, 0x3FA00000, PG_PRESENT | PG_RW | PG_USR); // user stack 

    TLBFlush();
    CR0(31);
}

UPointer MapAPage
(Unsig32 virtaddr, Unsig32 physaddr, Unsig32 flags) {
    Unsig32 di = virtaddr >> 22;
    Unsig32 ti = (virtaddr >> 12) &0x3FF;

    if (!(pd[di] &(1 << PG_PRESENT))) {
        paged Unsig32 *new_pt = (Unsig32 *)DumbPMMAlloc(4096);
        for (int i = 0; i < 1024; i++) new_pt[i] = 0;
        pd[di] = (Unsig32)new_pt | PG_PRESENT | PG_RW | PG_USR;
    }

    Unsig32 *another_pt = (Unsig32 *)(pd[di] & 0xFFFFF000);
    another_pt[ti] = (physaddr &0xFFFFF000) | (flags &0x00000FFF) | PG_PRESENT | PG_RW | PG_USR;
    
    INVLPG(virtaddr);
}