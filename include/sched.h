#ifndef SCHED_H_ENVE
#define SCHED_H_ENVE
#include "type.h"
#include "macro.h"
#include "ring3.h"

enum TaskState {
    T_RUNNING = 0,
    T_IDLE = 1,
    T_DEAD = 2,
};

// WTF?!
struct Task {
    enum TaskState ts;
    Unsig32 pid;
    struct TaskRegs r;

    struct Task *next;
};

UPointer CreateTask();

UPointer Y();
#endif /* SCHED_H_ENVE */
