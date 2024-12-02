# Define C compiler.
CC=arm-none-eabi-gcc
# Define compiler flags.
CFLAGS=-mcpu=cortex-m4 -mthumb -nostdlib
# Define compiler pre-processor flags
CPPFLAGS=-DSTM32F411xE \
		 -Ivendor/CMSIS_5/Device/ST/cmsis-device-f4/Include \
		 -Ivendor/CMSIS_5/CMSIS/Core/Include

# Define linker script file.
LINKER_FILE=linker_script.ld
# Define linker flags.
LDFLAGS=-T $(LINKER_FILE)

PROGRAMMER=openocd
PROGRAMMER_FLAGS=-f interface/stlink.cfg -f target/stm32f4x.cfg

all: blink.elf

# Note: $^ (the automatic variable) is short-hand for the
# names of all the prerequisites with spaces between them.
blink.elf: main.o startup.o system_stm32f4xx.o
	$(CC) $(CFLAGS) $(CPPFLAGS) $(LDFLAGS) $^ -o blink.elf

main.o: main.c
	$(CC) $(CFLAGS) $(CPPFLAGS) main.c -c

startup.o: startup.c
	$(CC) $(CFLAGS) $(CPPFLAGS) startup.c -c

system_stm32f4xx.o: vendor/CMSIS_5/Device/ST/cmsis-device-f4/Source/Templates/system_stm32f4xx.c
	$(CC) $(CFLAGS) $(CPPFLAGS) vendor/CMSIS_5/Device/ST/cmsis-device-f4/Source/Templates/system_stm32f4xx.c -c

.PHONY: clean
clean:
	rm -f *.o *.elf

flash: blink.elf
	$(PROGRAMMER) $(PROGRAMMER_FLAGS) -c "program blink.elf verify reset exit"



