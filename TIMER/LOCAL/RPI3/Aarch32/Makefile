NAME = test
LINARO = arm-eabi
ASM = start
OPT = -march=armv8-a -Wall -O0  -nostdlib -nostartfiles -ffreestanding
KERNEL = kernel7

all : $(NAME).hex $(NAME).bin $(KERNEL).linker.ld

$(ASM).o : $(ASM).s
	$(LINARO)-as $(ASM).s -o $(ASM).o

$(NAME).o : $(NAME).c
	$(LINARO)-gcc $(OPT) -c $(NAME).c -o $(NAME).o

$(NAME).elf : memmap start.o $(NAME).o
	$(LINARO)-ld $(ASM).o $(NAME).o -T memmap -o $(NAME).elf
	$(LINARO)-objdump -D $(NAME).elf > $(NAME).list

$(NAME).bin : $(NAME).elf
	$(LINARO)-objcopy $(NAME).elf -O binary $(NAME).bin

$(KERNEL).linker.ld :
	$(LINARO)-objcopy $(NAME).elf -O binary $(KERNEL).linker.ld

$(NAME).hex : $(NAME).elf
	$(LINARO)-objcopy $(NAME).elf -O ihex $(NAME).hex

clean :
	rm -f *.o
	rm -f *.bin
	rm -f *.hex
	rm -f *.linker.ld
	rm -f *.list
	rm -f *.elf
