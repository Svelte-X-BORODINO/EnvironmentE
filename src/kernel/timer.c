#include <timer.h>
#include <type.h>
#include <io.h>
#include <macro.h>
#include <pic.h>

Unsig32 ticks = 0;

UPointer TimerInit
(Unsig32 div) {
    Unsig32 new_freq = FREQ / 100;
    outb(0x43, 0x36);                    // channel 0, both bytes (idk what is this), mode 3
    outb(0x40, new_freq &0xFF);          // new_freq lo byte
    outb(0x40, (new_freq >> 8) &0xFF);   // new_freq hi byte
    // now we need to insert this shit into IDT and try to not blow the universe
}

ATTR
((naked)) UPointer IRQ32(void) {
    ticks++;
}