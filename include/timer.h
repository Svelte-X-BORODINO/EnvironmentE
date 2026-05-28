#ifndef TIMER_H_ENVE
#define TIMER_H_ENVE
#include <type.h>
#include <macro.h>

#define FREQ 1193180

UPointer TimerInit(Unsig32 div);
naked UPointer IRQ32(void);

#endif /* TIMER_H_ENVE */
