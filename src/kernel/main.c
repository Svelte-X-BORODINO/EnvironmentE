#include <io.h>
#include <serial.h>
#include <gdt.h>
#include <macro.h>
void Setup(void) {
    outb(0x21, 0xFF);
    outb(0xA1, 0xFF);
    OutS("UART init...\n");
    UARTInit();
    OutS("GDT loading...\n");
    GDTLoad();            
    OutS("GDT Loaded!\n");      
    OutS(TODO("idt"));
    for(;;);
}
