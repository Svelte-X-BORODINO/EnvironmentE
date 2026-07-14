#include <macro.h>
#include <sched.h>

struct Task *tasktail = NULL;
struct Task *taskhead = NULL;

static UPointer GoToR3(Unsig32 ueip, Unsig32 uesp) {
    VASM (
        "movw $0x23, %%ax\n"
        "movw %%ax, %%ds\n"
        "movw %%ax, %%es\n"
        "movw %%ax, %%ss\n"
        "movw %%ax, %%fs\n"
        "movw %%ax, %%gs\n"
        "pushw %%ax\n" // SS
        "pushl %0\n"   // ESP
        "pushl $0x200206\n" // EFLAGS
        "pushl $0x1B\n" // CS
        "pushl %1\n" // EIP
        "iret"
        :: "m"(uesp), "m"(ueip) : "memory"
    );

    __builtin_unreachable(); // thanks to JokelaOS
}


//static UPointer CreateTask() {
//
//}

