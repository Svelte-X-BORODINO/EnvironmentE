section .data
irq0_msg:   db "Kernel Panic caught : Division by zero! x86 is not IEEE 754, bro", 0x0D, 0x0A
irq8_msg:   db "Kernel Panic caught : DOUBLE FAULT!!!!! WHAT THE F*CK IS GOIN' ON?!", 0x0D, 0x0A
irqwtf_msg: db "some interrupt caught\n"


section .text
global irq0
global irq8
global another_irq

extern OutS
extern EOI

irq0:
    push irq0_msg
    call OutS
    push 0
    call EOI
    add esp, 8
    iret
    

irq8:
    push irq8_msg
    call OutS
    push 8
    call EOI
    add esp, 8
    iret
    

another_irq:
    push irqwtf_msg
    call OutS
    mov al, 0x20
    out 0x20, al
    out 0xA0, al
    add esp, 4
    iret
    