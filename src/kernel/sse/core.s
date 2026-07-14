.globl sse_check
.globl SSEInit

sse_check:
    movl $0x1, %eax
    cpuid

    test $(1 << 25), %edx        
    jz .no_sse

    xorl %eax, %eax
    ret
.no_sse:
    pushl $no_sse
    pushl $no_sse_prefix
    calll LogF
    movl $-1, %eax
    ret

SSEInit:
    pushal

    calll sse_check
    cmp $-1, %eax
    je .done

    movl %cr4, %eax
    orl $0x600, %eax
    movl %eax, %cr4

    pushl $0x1F80
    ldmxcsr (%esp)
    add $0x4, %esp 

    popal
.done: ret

.section .data
no_sse_prefix: .asciz "SHAME"
no_sse: .asciz "SSE is not supported, so u can't run sectorLLM in EnvE :("