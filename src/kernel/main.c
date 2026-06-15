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
    struct {Unsig16 l; Unsig32 b} __attribute__((packed)) gdt;
    struct {Unsig16 l; Unsig32 b} __attribute__((packed)) idt;

    VASM
    ( "fninit" );
    UARTInit();
    LogF("MAIN", "Environment E version huynya starting");
    LogF("UART", "UART initialized with baud 115200");

    if(magic != 0x2BADB002) {
        FAULT("Invalid magic!!!");
    }

    OutC('\n');
    GDTLoad();
    VASM 
    ( "sgdt %0\n" : "=m"(gdt) :: "memory" );
    LogF("GDT", "Ready, Base : %x; Limit : %x", gdt.b, gdt.l);    
    IDTLoad();
    VASM 
    ( "sidt %0\n" : "=m"(idt) :: "memory" );
    LogF("IDT", "Ready, Base : %x; Limit : %x", idt.b, idt.l);
    PICInit();
    OutS("IDT/Timer Ready!\n");
    TimerInit(100);
    KeyboardInit();
    OutS("Keyboard Ready!(vozduh)");
    for (;;) VASM ("hlt");
}
