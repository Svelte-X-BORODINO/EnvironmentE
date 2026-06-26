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

void Setup
(Unsig32 magic, Unsig32 mbinfo) {
    packed struct {Unsig16 l; Unsig32 b} gdt;
    packed struct {Unsig16 l; Unsig32 b} idt;
    Unsig32 f = 0;

    VASM
    ( "fninit\npushfl\npopl %0" :: "m"(f) : "memory" );
    UARTInit();
    LogF("MAIN", "Environment E version kapec starting");
    LogF("UART", "UART initialized with baud 115200");
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
    LogF("FLG", "Flags : %b", f);
    PICInit();
    LogF("PIT", "Timer ready.");
    TimerInit(10);
    LogF("KBD", "Keyboard ready.");
    VASM("int $0x15" ::: "memory");
    for (;;) VASM ("hlt");
}
