.globl FPUInit

FPUInit:
    pushal

    movl %cr0, %eax
    andl $0xFFFFFFFB, %eax
    orl $0x22, %eax 
    movl %eax, %cr0
    # now CR0 equals to 0x33, I hope...

    fninit
    popal
    ret


