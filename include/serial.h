#ifndef SERIAL_H_ENVE
#define SERIAL_H_ENVE
#include <type.h>
#define COM_BASE 0x3F8

UPointer UARTInit(void);
UPointer OutC(JustAChar ch);
UPointer OutS(String s);

#endif /* SERIAL_H_ENVE */
