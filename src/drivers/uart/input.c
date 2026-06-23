#include <type.h>
#include <io.h>
#include <serial.h>

UPointer KBDMainRoutine() {
    OutC(inb(COM_BASE));
}