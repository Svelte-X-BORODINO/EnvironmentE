// I HATE PMM!
#include <type.h>
#include <log.h>
#include <mb_memmap.h>

Unsig8 bitmap[0x100000 / 8]; 

static String EntryType(struct MBMapEntry *e) {
    if (e->base_addr >= 0xFFFC0000 && e->base_addr <= 0xFFFFFFFF) {
        return "SeaBIOS Firmware";
    }

    if (e->base_addr >= 0xC0000000 && e->base_addr <= 0xF0000000) {
        return "Higher Half Kernel (soon)";
    }
    switch (e->type) {
        case 1: return "Available";
        case 2: return "Reserved";
        case 3: return "ACPI Reclaim";
        case 4: return "ACPI NVS";
        case 5: return "Bad Memory";
        default: return "Unknown";
    }
}

void DumbPMMInit(Unsig32 mbinfo) {
    struct MBInfo *mb = (struct MBInfo *)mbinfo;
    if (!(mb->flags &(1 << 6))) {
        LogF("PMM", "Oh.. No memory map :(");
        return;
    }

    Unsig32 addr = mb->mmap_addr;
    Unsig32 end = addr + mb->mmap_length;

    while (addr < end) {
        struct MBMapEntry *entry = (struct MBMapEntry *)addr;
        LogF("PMM", "[%l-%l] %s", 
            (Unsig64)entry->base_addr, 
            (Unsig64)(entry->base_addr + entry->length),
            EntryType(entry));
        addr += entry->size + 4; // size не считает себя
    }
}