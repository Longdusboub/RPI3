NAME = test
LINARO = arm-eabi
ASM = stub
HANDLER = irq_handler
OPT = -Iinclude/ -march=armv7-a -Wall -O0  -nostdlib -nostartfiles -ffreestanding
KERNEL = kernel7

all : $(NAME).hex $(NAME).bin $(KERNEL).img

$(ASM).o : src/$(ASM).s
	$(LINARO)-as src/$(ASM).s -o $(ASM).o

$(HANDLER).o : src/$(HANDLER).s
	$(LINARO)-as src/$(HANDLER).s -o $(HANDLER).o

$(NAME).o : src/$(NAME).c
	$(LINARO)-gcc $(OPT) -c src/$(NAME).c -o $(NAME).o

$(NAME).elf : src/linker.ld $(HANDLER).o $(ASM).o $(NAME).o
	$(LINARO)-ld $(HANDLER).o $(ASM).o $(NAME).o -T src/linker.ld -o $(NAME).elf
	$(LINARO)-objdump -D $(NAME).elf > $(NAME).list

$(NAME).bin : $(NAME).elf
	$(LINARO)-objcopy $(NAME).elf -O binary $(NAME).bin

$(KERNEL).img :
	$(LINARO)-objcopy $(NAME).elf -O binary $(KERNEL).img

$(NAME).hex : $(NAME).elf
	$(LINARO)-objcopy $(NAME).elf -O ihex $(NAME).hex

clean :
	rm -f *.o
	rm -f *.bin
	rm -f *.hex
	rm -f *.img
	rm -f *.list
	rm -f *.elf
