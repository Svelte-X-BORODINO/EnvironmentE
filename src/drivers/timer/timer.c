#include <timer.h>
#include <type.h>
#include <io.h>
#include <macro.h>
#include <pic.h>
#include <serial.h>

indata Unsig32 ticks = 0;

UPointer TimerInit
(Unsig32 div) {
    Unsig32 new_freq = FREQ / 100;
    outb(0x43, 0x36);                    // channel 0, both bytes (idk what is this), mode 3
    outb(0x40, new_freq &0xFF);          // new_freq lo byte
    outb(0x40, (new_freq >> 8) &0xFF);   // new_freq hi byte
    // now we need to insert this shit into IDT and try to not blow the universe
}

naked UPointer IRQ32
(void) {
    VASM (
        "pushal\n"      // saving eax, ebx, ecx, edx, esi, edi, and maybe ebp/esp
        "incl %0\n"
        "pushl $0\n"
        "calll EOI\n"
        "add $0x4, %%esp\n"
        "popal\n"    
        "iret"
        :: "m"(ticks) : "memory"
    );
}
