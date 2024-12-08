# Define C compiler.
CC=arm-none-eabi-gcc
# Define compiler flags.
CFLAGS=-mcpu=cortex-m4 -mthumb -nostdlib
# Define compiler pre-processor flags
CPPFLAGS=-DSTM32F411xE \
		 -ISTM32CubeF4/Drivers/CMSIS/Device/ST/STM32F4xx/Include \
		 -ISTM32CubeF4/Drivers/CMSIS/Core/Include

# Define linker script file.
LINKER_FILE=system/linker_script.ld
# Define linker flags.
LDFLAGS=-T $(LINKER_FILE)

PROGRAMMER=openocd
PROGRAMMER_FLAGS=-f interface/stlink.cfg -f target/stm32f4x.cfg

SRC_DIR=src
BUILD_DIR=build
OBJ_DIR=$(BUILD_DIR)/obj

STM_CMSIS_TEMPLATE=STM32CubeF4/Drivers/CMSIS/Device/ST/STM32F4xx/Source/Templates/system_stm32f4xx.c
STARTUP_FILE=system/startup.c

# Create list of object files.
APP_OBJ_FILES=$(patsubst $(SRC_DIR)/%.c, $(OBJ_DIR)/%.o, $(wildcard $(SRC_DIR)/*.c))
OBJ_CMSIS=$(OBJ_DIR)/system_stm32f4xx.o
OBJ_STARTUP=$(OBJ_DIR)/startup.o

all: $(BUILD_DIR)/program.elf

# Note: $^ (the automatic variable) is short-hand for the
# names of all the prerequisites with spaces between them.
# Note: $@ is short-hand for the name of the target
$(BUILD_DIR)/program.elf: $(APP_OBJ_FILES) $(OBJ_STARTUP) $(OBJ_CMSIS) | $(BUILD_DIR)
	$(CC) $(CFLAGS) $(CPPFLAGS) $(LDFLAGS) $^ -o $@

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c | $(OBJ_DIR)
	$(CC) $(CFLAGS) $(CPPFLAGS) $< -c -o $@

$(OBJ_STARTUP): $(STARTUP_FILE) | $(OBJ_DIR)
	$(CC) $(CFLAGS) $(CPPFLAGS) $^ -c -o $@

$(OBJ_CMSIS): $(STM_CMSIS_TEMPLATE) | $(OBJ_DIR)
	$(CC) $(CFLAGS) $(CPPFLAGS) $^ -c -o $@

$(OBJ_DIR) $(BUILD_DIR):
	@mkdir -p $@

.PHONY: clean
clean:
	@rm -r $(BUILD_DIR)

flash: $(BUILD_DIR)/program.elf
	$(PROGRAMMER) $(PROGRAMMER_FLAGS) -c "program $(BUILD_DIR)/program.elf verify reset exit"

