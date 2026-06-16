.section .data
irq0_msg:
    .asciz "Kernel Panic caught : Division by zero! x86 is not IEEE 754, bro\n\r"
irq8_msg:
    .asciz "Kernel Panic caught : DOUBLE FAULT!!!!! WHAT THE F*CK IS GOIN' ON?! BLYAAAAAAAAA\n\r"
irqwtf_msg:
    .asciz "some interrupt caught\n\r"

.section .text
.globl IRQMainRoutine

IRQMainRoutine:
    pushl %ds # RegsFrame->ds

    pushal # RegsFrame->eax..ebp

    movw $0x10, %ax
    movw %ax, %ds
    movw %ax, %es
    movw %ax, %ss
    movw %ax, %fs
    movw %ax, %gs

    pushl %esp # RegsFrame for IRQ
    calll CIRQ
    popl %esp
    popal
    popl %ds
    add $0x4, %esp

    iret



another_irq: iret