AS = as --32
OBJCOPY = objcopy
QEMU = qemu-system-i386
GCC = gcc
CFLAGS = -m32 -ffreestanding -fno-stack-protector -fno-pie -fno-pic -Iinclude -O2 -z noexecstack -mno-sse -mno-mmx -fpack-struct=1 
LD = ld -z noexecstack
LDFLAGS = -m elf_i386 -T enve.ld

KERNEL = NVKern

C_SRC = $(shell find src/ -name "*.c")
C_OBJ = $(C_SRC:.c=.o)

ASM_SRC = boot.s $(shell find src/ -name "*.s")
ASM_OBJ = boot.o $(ASM_SRC:.s=.o)

OBJ = $(ASM_OBJ) $(C_OBJ)

all: $(KERNEL)

boot.o: boot.s
	$(AS) -o $@ $<

%.o: %.s
	$(AS) -o $@ $<

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

$(KERNEL): $(OBJ)
	$(LD) $(LDFLAGS) -o $@ $^
	./tools/debug-info kernel.elf report.txt
	@echo "Kernel is ready, see report.txt"

run: $(KERNEL)
	$(QEMU) -kernel $(KERNEL) -M smm=off -d int,cpu_reset,guest_errors \
	-D emu.log -nographic -no-reboot
	
run_debug: $(KERNEL)
	@echo "Use C-a c to enter QEMU Monitor."
	$(QEMU) -kernel $(KERNEL) -M smm=off

clean:
	rm -f $(OBJ) $(KERNEL) 

ca: clean all run

cad: clean all run_debug

.PHONY: all clean run runox ca canox
# /execute in minecraft:overworld run tp @s 1400.95 63.00 -2627.30 343.18 69.60 - это мне надо для майна