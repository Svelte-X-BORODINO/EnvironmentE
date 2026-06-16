#include <log.h>
#include <irqs.h>

char *irqs[] = {
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

void CIRQ(struct RegsFrame *r) {
    LogF("PANIC", "Exception caught: %s; ds=%x, eip=%x", irqs[r->int_no], r->ds, r->eip);
}