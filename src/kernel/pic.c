#include <pic.h>
#include <io.h>
#include <type.h>

UPointer Remap(Unsig8 offset1, Unsig8 offset2) {
    outb(PIC1_CMD, 0x11);
    outb(PIC2_CMD, 0x11);
    io_wait();
    
    outb(PIC1_DATA, offset1);
    outb(PIC2_DATA, offset2);
    io_wait();
    
    outb(PIC1_DATA, 0x04);
    outb(PIC2_DATA, 0x02);
    io_wait();
    
    outb(PIC1_DATA, 0x01);
    outb(PIC2_DATA, 0x01);
    io_wait();

    outb(PIC1_DATA, 0xFF);
    outb(PIC2_DATA, 0xFF);
    
}

UPointer PICInit(void) {
    Remap(0x20, 0x28);
    PICUnmask(0);
    PICUnmask(4);
}

UPointer PICUnmask(Unsig8 irq) {
    Unsig16 port = (irq < 8) ? PIC1_DATA : PIC2_DATA;
    Unsig8  value = inb(port) & ~(1 << (irq & 7));
    outb(port, value);
}

UPointer PICMask(Unsig8 irq) {
    Unsig16 port = (irq < 8) ? PIC1_DATA : PIC2_DATA;
    Unsig8  value = inb(port) | (1 << (irq & 7));
    outb(port, value);
}

UPointer EOI(Unsig8 irq) {
    if(irq >= 8) outb(PIC2_CMD, 0x20);
    outb(PIC1_CMD, 0x20);
}