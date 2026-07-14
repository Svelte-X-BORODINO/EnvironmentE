OUTPUT_FORMAT("elf32-i386")
ENTRY(_start)

SECTIONS
{
    . = 0x100000;

    .boot ALIGN(4) : {
        *(.mboot)
    }

    .multiboot : {
        *(.multiboot)
    }

    .text : {
        *(.text)
    }

    .data : {
        *(.data)
    }

    .rodata : {
        *(.rodata)
    }

    . = 0x1C0000;
    .ring3 : {
        *(.ring3)
    }

    .bss ALIGN(4K) : {
        *(.bss)
    }

    /DISCARD/ : {
        *(.comment)
        *(.eh_frame)
        *(.note.gnu.build-id)
        *(.note.GNU-stack)
        *(.note)
    }
}