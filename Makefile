# Implicit Variable Definitions

# Define C compiler
CC = arm-none-eabi-gcc

# Define compiler flags
CFLAGS = -mcpu=cortex-m4 -mthumb -nostdlib

# Define compiler pre-processor flags
CPPFLAGS = -DSTM32F411xE \
		 -ISTM32CubeF4/Drivers/CMSIS/Device/ST/STM32F4xx/Include \
		 -ISTM32CubeF4/Drivers/CMSIS/Core/Include

# Define linker flags
LDFLAGS = -T $(LINKER_FILE)


# File Path Variable Definitions

STM_CMSIS_TEMPLATES = STM32CubeF4/Drivers/CMSIS/Device/ST/STM32F4xx/Source/Templates

SRC_DIR = src
SYS_DIR = system
BUILD_DIR = build
OBJ_DIR = $(BUILD_DIR)/obj

# vpath allows for directories to be specified for a particular class of files
vpath %.c $(SRC_DIR) $(SYS_DIR) $(STM_CMSIS_TEMPLATES)

# Create list of object files
OBJ_FILES =  $(patsubst $(SRC_DIR)/%.c, $(OBJ_DIR)/%.o, $(wildcard $(SRC_DIR)/*.c)) \
						 $(OBJ_DIR)/system_stm32f4xx.o 																					\
						 $(OBJ_DIR)/startup.o

# Define linker script file
LINKER_FILE = $(SYS_DIR)/linker_script.ld


# Other Variable Definitions
PROGRAMMER = openocd
PROGRAMMER_FLAGS = -f interface/stlink.cfg -f target/stm32f4x.cfg


# Rule Definitions

all: $(BUILD_DIR)/program.elf

# Note: $^ (the automatic variable) is short-hand for the
# names of all the prerequisites with spaces between them
# Note: $@ is short-hand for the name of the target
$(BUILD_DIR)/program.elf: $(OBJ_FILES) | $(BUILD_DIR) $(OBJ_DIR)
	$(CC) $(CFLAGS) $(CPPFLAGS) $(LDFLAGS) $^ -o $@

$(OBJ_DIR)/%.o: %.c | $(BUILD_DIR) $(OBJ_DIR)
	$(CC) $(CFLAGS) $(CPPFLAGS) $< -c -o $@

$(BUILD_DIR) $(OBJ_DIR):
	@mkdir -p $@

.PHONY: clean
clean:
	@rm -r $(BUILD_DIR)

flash: $(BUILD_DIR)/program.elf
	$(PROGRAMMER) $(PROGRAMMER_FLAGS) -c "program $(BUILD_DIR)/program.elf verify reset exit"

