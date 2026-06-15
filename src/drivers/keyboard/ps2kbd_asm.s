.text
.globl IRQ33

.extern KBDMainRoutine
.extern EOI

IRQ33:
    pushal
    calll KBDMainRoutine
    pushl $1
    calll EOI
    addl $4, %esp
    popal
    iret