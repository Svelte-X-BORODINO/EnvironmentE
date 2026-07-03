.section .text
.globl SSEInit

SSEInit:
    pushal
    movl %cr4, %eax
    orl $0x600, %eax
    movl %eax, %cr4

    fninit

    pushl $0x1F80
    ldmxcsr (%esp)
    add $0x4, %esp 

    popal