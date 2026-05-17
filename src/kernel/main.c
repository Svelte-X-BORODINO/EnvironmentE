#include <io.h>
#include <serial.h>
#include <gdt.h>
#include <macro.h>
#include <pic.h>
void Setup
(void) {
    //PICInit();
    OutS("UART init...\n");
    UARTInit();
    OutS("GDT loading...\n");
    GDTLoad();            
    OutS("GDT Loaded!\n");      
    OutS(TODO("idt"));
    for(;;);
}
