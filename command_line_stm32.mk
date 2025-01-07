# Paths that should be defined
# CLISTM_SRC_DIRS: all directories containing source code
# CLISTM_BUILD_DIR: top level build directory
#
# Prefix will be CLISTM_
#
# Plan of attack:
# 	make work from example directory
# 		- Involves adjusting paths that are relative to this repo's
# 		makefile (remove use of vpath)
# 		- Adjust rules so obj directory follows that of src dir structure
# 		- add checks for necessary variable definitions
# 		- update readme
# 		- Make rules for $(CLISTM_PATHO)/system_stm32f4xx.o and
# 		$(CLISTM_PATHO)/startup.o

# Directory where this makefile is located
CLISTM_THIS_MAKEFILE_DIR := $(dir $(abspath $(lastword $(MAKEFILE_LIST))))

# File Path Definitions
CLISTM_SYS_DIR = $(CLISTM_THIS_MAKEFILE_DIR)system
CLISTM_CMSIS = $(CLISTM_THIS_MAKEFILE_DIR)STM32CubeF4/Drivers/CMSIS
CLISTM_CMSIS_TEMPLATE = $(CLISTM_CMSIS)/Device/ST/STM32F4xx/Source/Templates

# Define linker script file
CLISTM_LINKER_FILE = $(CLISTM_SYS_DIR)/linker_script.ld

# vpath allows for directories to be specified for a particular class of files
#vpath %.c $(CLISTM_PATHS) $(CLISTM_SYS_DIR) $(CLISTM_CMSIS_TEMPLATES)


CLISTM_PATHS = $(CLISTM_SRC_DIRS)
CLISTM_PATHB = $(CLISTM_BUILD_DIR)/clistm_build
CLISTM_PATHO = $(CLISTM_PATHB)/objs
CLISTM_PATHO_MODULES = $(addprefix $(CLISTM_PATHO)/, $(CLISTM_PATHS) command_line_stm32)
CLISTM_BUILD_PATHS = $(CLISTM_PATHB) $(CLISTM_PATHO) $(CLISTM_PATHO_MODULES)


CLISTM_USR_SRCS = $(foreach clistm_dir, $(CLISTM_PATHS), $(wildcard $(clistm_dir)/*.c))
CLISTM_USR_OBJS = $(patsubst %.c, $(CLISTM_PATHO)/%.o, $(CLISTM_USR_SRCS))
CLISTM_USR_DEPS = $(patsubst %.c, $(CLISTM_PATHO)/%.d, $(CLISTM_USR_SRCS))


# Compilation variables
CLISTM_CC = arm-none-eabi-gcc
CLISTM_CFLAGS = -mcpu=cortex-m4 -mthumb -nostdlib
CLISTM_CPPFLAGS = -MMD -MP \
					 -DSTM32F411xE \
		 			 -I$(CLISTM_CMSIS)/Device/ST/STM32F4xx/Include \
		 			 -I$(CLISTM_CMSIS)/Core/Include
CLISTM_LDFLAGS = -T $(CLISTM_LINKER_FILE)

# Programmer Definitions
CLISTM_PROGRAMMER = openocd
CLISTM_PROGRAMMER_FLAGS = -f interface/stlink.cfg -f target/stm32f4x.cfg


build: $(CLISTM_PATHB)/program.elf | $(CLISTM_BUILD_PATHS)

$(CLISTM_PATHB)/program.elf: $(CLISTM_USR_OBJS) $(CLISTM_PATHO)/command_line_stm32/system_stm32f4xx.o $(CLISTM_PATHO)/command_line_stm32/startup.o | $(CLISTM_BUILD_PATHS)
	$(CLISTM_CC) $(CLISTM_CFLAGS) $(CLISTM_CPPFLAGS) $(CLISTM_LDFLAGS) $^ -o $@

$(CLISTM_PATHO)/%.o: %.c | $(CLISTM_BUILD_PATHS)
	$(CLISTM_CC) $(CLISTM_CFLAGS) $(CLISTM_CPPFLAGS) -c $< -o $@

$(CLISTM_PATHO)/command_line_stm32/system_stm32f4xx.o: $(CLISTM_CMSIS_TEMPLATE)/system_stm32f4xx.c | $(CLISTM_BUILD_PATHS)
	$(CLISTM_CC) $(CLISTM_CFLAGS) $(CLISTM_CPPFLAGS) -c $< -o $@

$(CLISTM_PATHO)/command_line_stm32/startup.o: $(CLISTM_SYS_DIR)/startup.c | $(CLISTM_BUILD_PATHS)
	$(CLISTM_CC) $(CLISTM_CFLAGS) $(CLISTM_CPPFLAGS) -c $< -o $@

$(CLISTM_BUILD_PATHS):
	mkdir -p $@


flash: $(CLISTM_PATHB)/program.elf
	$(CLISTM_PROGRAMMER) $(CLISTM_PROGRAMMER_FLAGS) -c "program $(CLISTM_PATHB)/program.elf verify reset exit"

-include $(CLISTM_USR_DEPS)

.PHONY: build flash
