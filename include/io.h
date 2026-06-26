#ifndef IO_H_ENVE
#define IO_H_ENVE
#include "type.h"

static inline UPointer outb(Unsig16 port, Unsig8 val) {
    __asm__ volatile("outb %0, %1" : : "a"(val), "Nd"(port));
}

static inline Unsig8 inb(Unsig16 port) {
    Unsig8 ret;
    __asm__ volatile("inb %1, %0" : "=a"(ret) : "Nd"(port));
    return ret;
}

static inline UPointer outw(Unsig16 port, Unsig8 val) {
    __asm__ volatile("outw %0, %1" : : "a"(val), "Nd"(port));
}

static inline Unsig16 inw(Unsig16 port) {
    Unsig16 ret;
    __asm__ volatile("inw %1, %0" : "=a"(ret) : "Nd"(port));
    return ret;
}

static inline UPointer io_wait(void) {
    outb(0x80, 0);
}

#endif /* IO_H_ENVE */
