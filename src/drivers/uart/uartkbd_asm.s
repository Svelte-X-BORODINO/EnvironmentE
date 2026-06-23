.text
.globl IRQ36

.extern KBDMainRoutine
.extern EOI

IRQ36:
    pushal
    pushl %ds
    pushl %es
    pushl %fs
    pushl %gs
    movl $0x10, %eax
    movw %ax, %ds
    movw %ax, %es
    movw %ax, %fs
    movw %ax, %gs

    calll KBDMainRoutine
    pushl $4
    calll EOI
    addl $4, %esp
    pop %gs
    pop %fs
    pop %es
    pop %ds
    popal
    iret
    