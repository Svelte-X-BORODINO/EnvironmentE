#ifndef SERIAL_H_ENVE
#define SERIAL_H_ENVE
#include <type.h>
#define COM_BASE 0x3F8

UPointer UARTInit(void);

UPointer KBDMainRoutine();

UPointer OutC(JustAChar ch);
UPointer OutS(String s);
UPointer OutI(Unsig32 n);
UPointer OutH(Unsig32 n);
UPointer OutB(Unsig32 n);

#endif /* SERIAL_H_ENVE */
