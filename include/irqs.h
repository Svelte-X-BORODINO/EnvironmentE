#ifndef IRQS_H
#define IRQS_H
#include <macro.h>
#include <type.h>
#include <serial.h>

packed struct RegsFrame {
    Unsig16 int_no;
    Unsig16 ds;
    
    Unsig32 edi;
    Unsig32 esi;
    Unsig32 ebp;
    Unsig32 esp;      
    Unsig32 ebx;
    Unsig32 edx;
    Unsig32 ecx;
    Unsig32 eax;
    
    Unsig16 cs;
    Unsig32 eip;
    Unsig32 eflags;
};

#define NONERROR(name, msg)                 \
    naked void name(void) {                 \
        __asm__ volatile(                   \
            "pushal\n"                      \
            "pushl %0\n"                    \
            "call OutS\n"                   \
            "addl $4, %%esp\n"               \
            "popal\n"                       \
            "iret\n"                        \
            : : "r"(msg)                    \
            : "memory"                      \
        );                                  \
    }

#define ERROR(name, msg)                    \
    naked void name(void) {                 \
        __asm__ volatile(                   \
            "pushal\n"                      \
            "pushl %0\n"                    \
            "call OutS\n"                   \
            "add $4, %%esp\n"               \
            "popal\n"                       \
            "1: hlt\n"                      \
            "jmp 1b\n"                      \
            : : "r"(msg)                    \
            : "memory"                      \
        );                                  \
    }

void CIRQ(struct RegsFrame *r);
#endif /* IRQS_H */
