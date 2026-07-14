#include <type.h>
#include <io.h>
#include <serial.h>

UPointer KBDMainRoutine
() {
    Unsig8 key = inb(COM_BASE);
    switch (key) {
        case '\r':
        case '\n': OutC('\n'); break;
        case 0x7F: OutS("\b \b"); break; // ОНО РАБОТАЕЕЕЕЕЕЕЕЕЕЕЕЕЕЕЕЕЕЕЕЕЕЕТ
        default: OutC(key); break;
    }
}