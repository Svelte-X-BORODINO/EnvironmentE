.code32

.section .mboot, "a", @progbits
.align 4
MBV1_header:
    .long 0x1BADB002         
    .long 0x00000003         
    .long -(0x1BADB002 + 0x3) 
MBV1_end:

# reserved for later updates
# .section .data
# video_ofs: .byte 0
# test: .asciz "Test!!!"

.section .data
.globl heap_start
heap_start: .long .

.section .bss
.align 16
stack_bottom:
    .skip 65536         
stack_top:

.section .text
.globl _start
.extern Setup

_start:
    # call .clrscr
    cli
    movl $stack_top, %esp
    pushl %ebx
    pushl %eax
    pushl $(1 << 21)   # CPUID
    popf       
    call Setup
             

    movw $0x4F42, 0xB8000
    # movl $test, %esi
    # movl $7, %ecx
    # call early_log     
    
    pushl $0x00
    popf

a:
    hlt 
    jmp a

# putc:
#     pushal
#     movb video_ofs, %dl      
#     shll $1, %edx                
#     addl $0xB8000, %edx         
#     movb %al, video_ofs        
#     popal
#     ret

# early_log:
#     movb (%esi), %al
#     call putc
#     decl %ecx
#     jnz early_log