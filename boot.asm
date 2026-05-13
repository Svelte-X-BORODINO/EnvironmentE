bits 32
section .mboot align=4
MBV1_header:
    dd 0x1BADB002         
    dd 0x00000003         
    dd -(0x1BADB002 + 0x3) 
MBV1_end:

section .bss
align 16
stack_bottom:
    resb 16384          
stack_top:

section .text
global _start
extern Setup
_start:
    ;call .clrscr
    cli
    mov esp, stack_top
    push (1 << 21) ; CPUID
    popf                

    mov word [0xB8000], 0x4F42   
    call Setup          

    push 0x00
    popf
.

a:
    hlt 
    jmp a
