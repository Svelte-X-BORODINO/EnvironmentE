.globl fpu_check
.globl FPUInit

fpu_check:
    movl $0x1, %eax
    cpuid
    test $0x1, %edx
    jz .nofpu
    ret
.nofpu:
    pushl $no_fpu
    pushl $no_fpu_prefix
    calll LogF
    d: jmp d

FPUInit:
    pushal
    calll fpu_check

    movl %cr0, %eax
    andl $0xFFFFFFFB, %eax
    orl $0x22, %eax 
    movl %eax, %cr0
    # now CR0 equals to 0x33, I hope...
    clts

    fninit
    popal
    ret

.section .rodata
no_fpu_prefix: .asciz "SHAME"
no_fpu: .asciz "Ohh.. there's no FPU support in your CPU, so we cant boot EnvE :("
