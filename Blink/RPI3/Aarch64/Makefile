NAME = test
LINARO = aarch64-elf
ASM = start
OPT = -march=armv8-a -Wall -O0  -nostdlib -nostartfiles -ffreestanding
IMAGE = kernel8

all : $(NAME).hex $(NAME).bin $(IMAGE).img

$(ASM).o : $(ASM).s
	$(LINARO)-as $(ASM).s -o $(ASM).o

$(NAME).o : $(NAME).c
	$(LINARO)-gcc $(OPT) -c $(NAME).c -o $(NAME).o

$(NAME).elf : memmap $(ASM).o $(NAME).o
	$(LINARO)-ld $(ASM).o $(NAME).o -T memmap -o $(NAME).elf
	$(LINARO)-objdump -D $(NAME).elf > $(NAME).list

$(NAME).bin : $(NAME).elf
	$(LINARO)-objcopy $(NAME).elf -O binary $(NAME).bin

$(IMAGE).img :
	$(LINARO)-objcopy $(NAME).elf -O binary $(IMAGE).img

$(NAME).hex : $(NAME).elf
	$(LINARO)-objcopy $(NAME).elf -O ihex $(NAME).hex


clean :
	rm -f *.o
	rm -f *.bin
	rm -f *.hex
	rm -f *.img
	rm -f *.list




