// I HATE PMM!
#include <type.h>
#include <log.h>
#include <mb_memmap.h>

#define BM_SIZE 0x100000
Unsig8 bitmap[BM_SIZE]; 


static inline UPointer Set
(Unsig32 frame) {
    bitmap[frame / 8] |= (1 << (frame % 8));
}

static inline UPointer Clear
(Unsig32 frame) {
    bitmap[frame / 8] &= ~(1 << (frame % 8));
}

static inline Unsig32 Test
(Unsig32 frame) {
    return bitmap[frame / 8] & (1 << (frame % 8));
}

static String EntryType
(struct MBMapEntry *e) {
    if (e->base_addr >= 0xFFFC0000 && e->base_addr <= 0xFFFFFFFF) return "BIOS Firmware";

    if (e->base_addr == 0x100000) return "System RAM";

    if ((e->base_addr + e->length) == 0x0009FC00) return "640K Low RAM";
    if ((e->base_addr + e->length) == 0x000A0000) return "ACPI/BIOS";
    
    switch (e->type) {
        case 1: return "Available";
        case 2: return "Reserved";
        case 3: return "ACPI Reclaim";
        case 4: return "ACPI NVS";
        case 5: return "Corrupted RAM";
        default: return "Unknown";
    }
}

void DumbPMMInit
(Unsig32 mbinfo) {

    struct MBInfo *mb = (struct MBInfo *)mbinfo;
    if (!(mb->flags &(1 << 6))) {
        LogF("PMM", "Oh.. No memory map :(");
        return;
    }

    LogF("PMM", "Here's the memory map:");
    Unsig32 addr = mb->mmap_addr;
    Unsig32 end = addr + mb->mmap_length;

    while (addr < end) {
        struct MBMapEntry *entry = (struct MBMapEntry *)addr;
        LogF("PMM", "[%l-%l] %s", 
            (Unsig64)entry->base_addr, 
            (Unsig64)(entry->base_addr + entry->length),
            EntryType(entry));
        addr += entry->size + 4; 
    }
}

Unsig32 DumbPMMAlloc
(Unsig32 size) {
    for (int i = 0; i < BM_SIZE; i++) {
        if (bitmap[i] == 0xFF) continue;
        for (Unsig8 j = 7; j >= 0; j--) {
            if(!(bitmap[i] & (1 << j))) {
                Unsig32 frame = i *8 +j;
                Set(frame);
                return frame *4096;
            }
        }
    }
    return 0;
} 


UPointer DumbPMMFree
(UPointer *ptr) {
    if (ptr == 0) return;
    Unsig32 frame = (Unsig32)ptr /4096;
    if (frame < BM_SIZE *8 && Test(frame)) {
        Clear(frame);
    }
}