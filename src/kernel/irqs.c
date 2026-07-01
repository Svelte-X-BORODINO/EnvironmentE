#include <log.h>
#include <irqs.h>
#include <macro.h>
#include <stddef.h>
_Static_assert(sizeof(struct RegsFrame) == 60, "RegsFrame F*CKING MUST be 56 bytes"); // da

const char *irqs[] = {
    "Division By Zero!",
    "Debug Exception!!",
    "blyat, its NMI",
    "Breakpoint!",
    "Overflow! nu ty krivozhop",
    "BOUND Range Exceeded!!!",
    "UD2 or u are krivozhop",
    "your CPU cant do float-point",
    "oh sweet sweet double fault",
    "FPU ploho",
    "TSS!!!",
    "Segment Not Present or u are used null desc",
    "Stack Fault!",
    "General Protection Fault? AGAIN?!",
    "Page Fault..",
    "Reserved!",
    "FPU error blyat, u are real krivozhop",
    "Alignment Check Fault!",
    "R.I.P Your CPU (some year)-2026",
    "if you see this, your CPU is dumb, cuz i turned off the SSE",
    "Reserved x2!",
    "Reserved x3!",
    "Reserved x4!",
    "Reserved x5!",
    "Reserved x6!",
    "Reserved x7!",
    "Reserved x8!",
    "Reserved x9!",
    "Reserved x10!",
    "Reserved x11!",
    "Reserved x12!",
    "Reserved x13!"
};

void CIRQErr(struct RegsFrame *r) {
    LogF("PANIC", "Exception caught: %s; ds=%x, eip=%x", irqs[r->int_no], r->ds, r->eip);
    VASM ("g: jmp g" ::: "memory", "cc");
}

void CIRQNonErr(struct RegsFrame *r) {
    LogF("IRQ", "int_no=%d errcode=%d eflags=%x cs=%x eip=%x", 
        r->int_no, r->errcode, r->eflags, r->cs, r->eip);
    LogF("IRQ", "ds=%x eax=%x ecx=%x edx=%x ebx=%x", 
        r->ds, r->eax, r->ecx, r->edx, r->ebx);
    LogF("IRQ", "esp=%x ebp=%x esi=%x edi=%x", 
        r->esp, r->ebp, r->esi, r->edi);
    LogF("IRQ", "Exception caught: %s; ds=%x, eip=%x", irqs[r->int_no], r->ds, r->eip);
}

void CPage(struct RegsFrame *r) {
    LogF("ZHOPA", "Its %s ds=%x, eip=%x, cr2=%x", irqs[r->int_no], r->ds, r->eip, r->cr2);
    VASM ("p: jmp p" ::: "memory", "cc");
}