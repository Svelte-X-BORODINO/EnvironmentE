#ifndef TIMER_H_ENVE
#define TIMER_H_ENVE
#include <type.h>

#define FREQ 1193180

UPointer TimerInit(Unsig32 div);
__attribute__((naked)) UPointer IRQ32(void);

#endif /* TIMER_H_ENVE */
