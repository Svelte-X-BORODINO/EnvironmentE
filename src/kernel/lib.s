.section .text
.globl IRQMainRoutine
.globl IRQMainRoutineNonErr
.globl irq0, irq1, irq2, irq3, irq4, irq5, irq6, irq7, irq8, irq9, irq10, irq11, irq12, irq13, Page, irq15, irq16, irq17, irq18, irq19, irq20, irq21, irqres

# RegsFrame is:
#   INT-saved regs:
#   eflags 
#   cs
#   eip    
#   Our code-saved data:
#   interrupt number
#   error code (zero)   
#   IRQMainRoutine(Err/NonErr)-saved regs:
#   ds    
#   eax    
#   ecx    
#   edx    
#   ebx    
#   esp    
#   ebp    
#   esi    
#   edi    
# And...
# Here's the message to GNU C Compiler:
# DELETE THIS FUCKING LIFO, OR I WILL KILL Y'ALL!

IRQMainRoutineErr:
    pushl $0 # RegsFrame->cr2 (useless in default error handler)
    pushl %ds # RegsFrame->ds

    pushal # RegsFrame->eax..ebp


    movw $0x10, %ax
    movw %ax, %ds
    movw %ax, %es
    movw %ax, %ss
    movw %ax, %fs
    movw %ax, %gs

    pushl %esp # RegsFrame for IRQ
    calll CIRQErr
    add $0x4, %esp
    popal
    popl %ds
    add $0x8, %esp

    iret

IRQMainRoutineNonErr:
    pushl $0 # RegsFrame->cr2 (useless too)
    pushl %ds # RegsFrame->ds

    pushal # RegsFrame->eax..ebp

    movw $0x10, %ax
    movw %ax, %ds
    movw %ax, %es
    movw %ax, %ss
    movw %ax, %fs
    movw %ax, %gs

    pushl %esp # RegsFrame for IRQ
    calll CIRQNonErr
    add $0x4, %esp
    popal
    popl %ds
    add $0x8, %esp

    iret

Page:
    pushl %ds # RegsFrame->ds

    pushal # RegsFrame->eax..ebp
    movl %cr2, %edx
    pushl %edx

    movw $0x10, %ax
    movw %ax, %ds
    movw %ax, %es
    movw %ax, %ss
    movw %ax, %fs
    movw %ax, %gs

    pushl %esp # RegsFrame for IRQ
    calll CPage
    add $0x4, %esp
    popal
    popl %ds
    add $0x8, %esp

    iret

# Division by zero
irq0:
    pushl $0
    pushl $0
    jmp IRQMainRoutineNonErr

# Debug
irq1:
    pushl $1
    pushl $0
    jmp IRQMainRoutineNonErr

# Non-maskable interrupt (kapec)
irq2:
    pushl $2
    pushl $0
    jmp IRQMainRoutineNonErr

# Breakpoint
irq3:
    pushl $3
    pushl $0
    jmp IRQMainRoutineNonErr

# Overflow
irq4:
    pushl $4
    pushl $0
    jmp IRQMainRoutineNonErr

# Bound Range Exceeded
irq5:
    pushl $5
    pushl $0
    jmp IRQMainRoutineNonErr

# Invalid Opcode
irq6:
    pushl $6
    pushl $0
    jmp IRQMainRoutineNonErr

# Device Not Available (FPU unavailable (a shame..))
irq7:
    pushl $7
    pushl $0
    jmp IRQMainRoutineNonErr

# Double Fault (kapec x2)
irq8:
    pushl $8
    pushl $0
    jmp IRQMainRoutineNonErr

# Coprocessor Segment Overrun (reserved)
irq9:
    pushl $9
    pushl $0
    jmp IRQMainRoutineErr

# Invalid TSS
irq10:
    pushl $10
    pushl $0
    jmp IRQMainRoutineErr

# Segment Not Present
irq11:
    pushl $11
    pushl $0
    jmp IRQMainRoutineErr

# Stack-Segment Fault
irq12:
    pushl $12
    pushl $0
    jmp IRQMainRoutineErr

# General Protection Fault (kapec x3)
irq13:
    pushl $13
    pushl $0
    jmp IRQMainRoutineErr

# Page Fault (kapec x4)
irq14:
    pushl $14
    jmp Page

# Reserved (do not use, please)
irq15:
    pushl $15
    pushl $0
    jmp IRQMainRoutineErr

# Floating-Point Exception
irq16:
    pushl $16
    pushl $0
    jmp IRQMainRoutineNonErr

# Alignment Check
irq17:
    pushl $17
    pushl $0
    jmp IRQMainRoutineNonErr

# Machine Check (you are dead, goodbye, CPU)
irq18:
    pushl $18
    pushl $0
    jmp IRQMainRoutineNonErr

# SIMD Floating-Point Exception
irq19:
    pushl $19
    pushl $0
    jmp IRQMainRoutineNonErr

# Reserved (lie, but dont care)
irq20:
    pushl $20
    pushl $0
    jmp IRQMainRoutineNonErr

# Reserved (lie, but dont care x2)
irq21:  
    pushl $21
    pushl $0
    jmp IRQMainRoutineNonErr

irqres:
    pushl $22
    pushl $0
    jmp IRQMainRoutineNonErr