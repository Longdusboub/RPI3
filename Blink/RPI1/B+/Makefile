NAME = test
LINARO = arm-eabi
ASM = start
OPT = -march=armv6z -Wall -O0  -nostdlib -nostartfiles -ffreestanding

all : $(NAME).hex $(NAME).bin kernel.img

$(ASM).o : $(ASM).s
	$(LINARO)-as $(ASM).s -o $(ASM).o

$(NAME).o : $(NAME).c
	$(LINARO)-gcc $(OPT) -c $(NAME).c -o $(NAME).o

$(NAME).elf : memmap $(ASM).o $(NAME).o
	$(LINARO)-ld $(ASM).o $(NAME).o -T memmap -o $(NAME).elf
	$(LINARO)-objdump -D $(NAME).elf > $(NAME).list

$(NAME).bin : $(NAME).elf
	$(LINARO)-objcopy $(NAME).elf -O binary $(NAME).bin

kernel.img :
	$(LINARO)-objcopy $(NAME).elf -O binary kernel.img

$(NAME).hex : $(NAME).elf
	$(LINARO)-objcopy $(NAME).elf -O ihex $(NAME).hex


clean :
	rm *.o
	rm *.bin
	rm *.hex
	rm *.img
	rm *.list



