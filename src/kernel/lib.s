.section .text
.globl IRQMainRoutine
# .globl irq0, irq1, irq2, irq3, irq4, irq5, irq6, irq8, irq9, irq10, irq11, irq12, irq13, irq14, irq15, irq16, irq17, irq18, irq19, irqres

IRQMainRoutine:
    pushw %ds # RegsFrame->ds

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
