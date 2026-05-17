section .data
irq0_msg:   db "Kernel Panic caught : Division by zero! x86 is not IEEE 754, bro"
irq8_msg:   db "Kernel Panic caught : DOUBLE FAULT!!!!! WHAT THE F*CK IS GOIN' ON?!"
irqwtf_msg: db "some interrupt caught"

section .text
global irq0
global irq8

extern OutS

irq0:
    push irq0_msg
    call OutS
    add esp, 4
    cli 
    hlt

irq8:
    push irq8_msg
    call OutS
    add esp, 4
    cli 
    hlt