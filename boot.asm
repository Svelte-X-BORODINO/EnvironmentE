bits 32
section .mboot align=4
MBV1_header:
    dd 0x1BADB002         
    dd 0x00000003         
    dd -(0x1BADB002 + 0x3) 
MBV1_end:

; reserved for later updates
;section .data
;video_ofs: db 0
;test: db "Test!!!", 0

section .bss
align 16
stack_bottom:
    resb 16384          
stack_top:

;section .text
;global _start
;global early_log
;extern Setup
;
;putc:
;    pusha
;    mov dl, [video_ofs]      
;    shl edx, 1                
;    add edx, 0xB8000         
;    mov byte [video_ofs], al        
;    popa
;    ret
;
;early_log:
;    mov al, [esi]
;    call putc
;    dec ecx
;    jnz early_log
;

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
    ;mov esi, test
    ;mov ecx, 7
    ;call early_log       
    call Setup
    push 0x00
    popf


a:
    hlt 
    jmp a
