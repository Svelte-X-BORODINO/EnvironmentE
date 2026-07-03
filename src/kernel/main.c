#include <serial.h>
#include <log.h>
#include <gdt.h>
#include <idt.h>
#include <macro.h>
#include <pic.h>
#include <panic.h>
#include <timer.h>
#include <kbd.h>
#include <type.h>
#include <mb_memmap.h>
#include <cr3paging.h>
#include <bump.h>

extern UPointer FPUInit();
extern UPointer SSEInit();

void Setup
(Unsig32 magic, Unsig32 mbinfo) {
    packed struct {Unsig16 l; Unsig32 b} gdt;
    packed struct {Unsig16 l; Unsig32 b} idt;
    Unsig32 f = 0;

    VASM
    ( "pushfl\npopl %0" :: "m"(f) : "memory" );
    UARTInit();
    OutC('\n');
    LogF("MAIN", "Environment E version kapec starting");
    LogF("UART", "UART I/O initialized with baud 115200");
    if(magic != 0x2BADB002) {
        FAULT("Invalid magic!!!");
    }
    GDTLoad();
    VASM 
    ( "sgdt %0\n" : "=m"(gdt) :: "memory" );
    LogF("GDT", "Ready, Base : %x; Limit : %x", gdt.b, gdt.l);    

    IDTLoad();
    VASM 
    ( "sidt %0\n" : "=m"(idt) :: "memory" );
    LogF("IDT", "Ready, Base : %x; Limit : %x", idt.b, idt.l);
    
    FPUInit();
    LogF("FPU", "FPU is ready. Now u can run DeepSeek-V4 Full (dont try it, please)");
    SSEInit();
    LogF("SSE", "SSE is ready. Now u can run sectorLLM in EnvE");

    LogF("FLG", "Flags : %b", f);

    PICInit();
    LogF("PIC", "PIC ready.");

    TimerInit(10);
    LogF("PIT", "Timer ready.");

    DumbPMMInit(mbinfo);
    LogF("PMM", "Testing PMM allocator!");
    Unsig32 addr = DumbPMMAlloc(0x1000);
    LogF("PMM", "Allocated 0x1000 bytes at %x", addr);
    DumbPMMFree((UPointer *)addr);
    LogF("PMM", "Freed 0x1000 bytes");

    PagingInit();
    LogF("CR3", "Identity-mapped some memory for you (256 MB)");

    for (;;) VASM ("hlt");
}
