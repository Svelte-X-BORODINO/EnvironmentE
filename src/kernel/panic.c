#include <panic.h>
#include <log.h>
#include <type.h>
#include <macro.h>

void FAULT(String s) {
    LogF("FAULT", "Kernel fault! Reason: %s", s);
    VASM 
    ( "1: jmp 1b\n" ::: "memory", "cc" );
} 
