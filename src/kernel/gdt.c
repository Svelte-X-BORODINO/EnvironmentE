#include <gdt.h>
#include <type.h>
#include <serial.h>
#include <macro.h>
#define SIZE 3
indata struct GDTEntry GDT[SIZE];
indata struct GDTp     Gp;

struct {
        struct GDTp header;     
        struct GDTEntry entries[3]; 
} __attribute__((packed)) gdt;

// @fname            : GDTInstall
// @param *p         : Pointer to GDT (TL;DR: this is the position & size of GDT)
ATTR 
((noinline, noclone)) used UPointer GDTInstall
(struct GDTp *p) {
    VASM 
    (
        "cli\n"
        "lgdt %0\n"
        ".byte 0xEA\n"
        ".long cs_flush\n"
        ".word 0x08\n"
        "cs_flush:\n\t"
        "xorl %%eax, %%eax\n\t"
        "movl $0x10, %%eax\n\t"
        "movl %%eax, %%ds\n\t"
        "movl %%eax, %%es\n\t"
        "movl %%eax, %%ss\n\t" // ладно ss, заслужил
        "movl %%eax, %%fs\n\t"
        "movl %%eax, %%gs\n\t"
        "ret" 
        :: "m"(*p)
        : "eax", "cc", "memory"
    );
}

// @fname            : InsertEntry
// @param idx        : Index of GDT table.
// @param limit      : Limit of GDT descriptor (end of memory area).
// @param base       : Base of GDT descriptor(TL;DR: start of memory area).
// @param access     : Access of the descriptor(TL;DR: this thing tells to CPU how we want to use our descriptor)
// @param gran       : Granunaliry of the descriptor(TL;DR: this asks the CPU - "yo, do we need to left shift the limit?")

static UPointer InsertEntry
(Unsig8 idx, Unsig32 limit, Unsig32 base, Unsig8 access, Unsig8 gran) {
    struct GDTEntry *entry = &GDT[idx];

    if (idx > SIZE) {
        OutS("pokolena boroda\n");
        return;
    }
    
    entry->base_low  = (base & 0xFFFF);
    entry->base_mid  = (base >> 16) & 0xFF;
    entry->base_high = (base >> 24) & 0xFF;
    entry->limit_low = (limit & 0xFFFF); // 16 limit bits in limit
    entry->gran      = (gran & 0xF0) | ((limit >> 16) & 0x0F); // 4 limit bits in... GRANULARITY!?
    entry->access    = access;
}

// @fname            : GDTLoad
// this thing initialize the f*cking GDT (i spent 4 days to fix this shit)
UPointer GDTLoad
(void) {
    InsertEntry(0, 0, 0, 0, 0);
    InsertEntry(1, 0x3FFF, 0, 0x9A, GR | DB);
    InsertEntry(2, 0x3FFF, 0, 0x92, GR | DB);

    gdt.entries[0] = GDT[0];
    gdt.entries[1] = GDT[1];
    gdt.entries[2] = GDT[2];

    gdt.header.size = sizeof(gdt.entries) - 1;
    gdt.header.ptr  = (Unsig32) &gdt.entries;

    _Static_assert(sizeof(struct GDTEntry) == 8, "GDTEntry must be 8 bytes");  // best C99 feature 
    _Static_assert(sizeof(struct GDTp) == 6, "GDTp MUST be 6 bytes");

    GDTInstall(&gdt.header);
}
