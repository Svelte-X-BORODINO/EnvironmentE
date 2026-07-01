#ifndef MACRO_H_ENVE
#define MACRO_H_ENVE
// DEPRECATED!!!
// #define TODO(s) "todo : " str(s)
// #define UNIMPL(s) "unimpl : " str(s)

#define VASM(...) __asm__ volatile (__VA_ARGS__)
#define ATTR(...) __attribute__(__VA_ARGS__)

#define CR0(bit) \
    do { \
        Unsig32 cr0; \
        VASM ("mov %%cr0, %0" : "=r"(cr0)); \
        cr0 |= (1 << (bit)); \
        VASM ("mov %0, %%cr0" : : "r"(cr0)); \
    } while(0)

#define CR4(bit) \
    do { \
        Unsig32 cr0; \
        VASM ("mov %%cr0, %0" : "=r"(cr0)); \
        cr0 |= (1 << (bit)); \
        VASM ("mov %0, %%cr0" : : "r"(cr0)); \
    } while(0)

#define paged ATTR((aligned(4096)))
#define align(n) ATTR((aligned(n)))
#define naked ATTR((naked))
#define used ATTR((used))
#define packed ATTR((packed))
#define indata ATTR((section(".data")))

#define cli VASM ("cli")
#define sti VASM ("sti")
#define iret VASM ("iret")
#define int3 VASM ("int $0x3")

#define str(s) xstr(s)
#define xstr(s) #s

#endif /* MACRO_H_ENVE */
