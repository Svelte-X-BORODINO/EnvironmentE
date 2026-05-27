#include <io.h>
#include <serial.h>
#include <gdt.h>
#include <idt.h>
#include <macro.h>
#include <pic.h>
#include <timer.h>
void Setup
(void) {
    OutS("UART init...\n");
    UARTInit();
    OutS("GDT loading...\n");
    GDTLoad();            
    OutS("GDT Loaded!\n");      
    OutS("IDT loading...\n");
    IDTLoad();
    PICInit();
    OutS("IDT/Timer Ready!\n");
    TimerInit(100);
    for (;;) VASM ("hlt");
}
