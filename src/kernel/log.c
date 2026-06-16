#include <log.h>
#include <serial.h>
#include <type.h>
#include <stdarg.h>

// @fname : LogF
// its just printf()
// fmts: [bcdsx]
UPointer LogF(String tag, String fmt, ...) {
    OutS(tag);
    OutS(" >>> : ");

    va_list args;
    va_start(args, fmt);

    while (*fmt) {
        if (*fmt == '%') {
            fmt++;
            switch (*fmt) {
                case 'b': OutB(va_arg(args, Unsig32)); break;
                case 'c': OutC(va_arg(args, Unsig32)); break;
                case 'd': OutI(va_arg(args, Unsig32)); break;
                case 's': OutS(va_arg(args, String)); break;
                case 'x': OutH(va_arg(args, Unsig32)); break;
                case '%': OutC('%'); break;
                default: OutC('%'); break;
            }
        } else OutC(*fmt);
        fmt++;
    }

    va_end(args);
    OutC('\n');
}