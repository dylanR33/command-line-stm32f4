# Paths that should be defined
# CLISTM_SRC_DIRS: all directories containing source code
# CLISTM_BUILD_DIR: top level build directory
# CLISTM_MODEL_NUM: specific stm mcu model within F4 family
#
# Ensure these are defined, else exit
ifndef CLISTM_SRC_DIRS
  $(error CLISTM_SRC_DIRS not defined)
endif
ifndef CLISTM_BUILD_DIR
  $(error CLISTM_BUILD_DIR not defined)
endif
ifndef CLISTM_MODEL_NUM
  $(error CLISTM_MODEL_NUM not defined)
endif


# Directory where this makefile is located
CLISTM_THIS_MAKEFILE_DIR := $(dir $(abspath $(lastword $(MAKEFILE_LIST))))


# System, CMSIS, HAL paths
CLISTM_SYS_DIR = $(CLISTM_THIS_MAKEFILE_DIR)system
CLISTM_CMSIS = $(CLISTM_THIS_MAKEFILE_DIR)STM32CubeF4/Drivers/CMSIS
CLISTM_CMSIS_TEMPLATE = $(CLISTM_CMSIS)/Device/ST/STM32F4xx/Source/Templates
CLISTM_HAL = $(CLISTM_THIS_MAKEFILE_DIR)STM32CubeF4/Drivers/STM32F4xx_HAL_Driver

# Linker script path
CLISTM_LINKER_FILE = $(CLISTM_SYS_DIR)/linker_script.ld


# Source code paths
CLISTM_PATHS = $(CLISTM_SRC_DIRS)


# Build paths
CLISTM_PATHB = $(CLISTM_BUILD_DIR)/command_line_stm32_build
CLISTM_PATHO = $(CLISTM_PATHB)/objs
CLISTM_PATHO_DIRS = $(addprefix $(CLISTM_PATHO)/, $(CLISTM_PATHS) command_line_stm32)
CLISTM_BUILD_PATHS = $(CLISTM_PATHB) $(CLISTM_PATHO) $(CLISTM_PATHO_DIRS)


# User source fles and corresponding object and dependancy files
CLISTM_USR_SRCS = $(foreach clistm_dir, $(CLISTM_PATHS), $(wildcard $(clistm_dir)/*.c))
CLISTM_USR_OBJS = $(patsubst %.c, $(CLISTM_PATHO)/%.o, $(CLISTM_USR_SRCS))
CLISTM_USR_DEPS = $(patsubst %.c, $(CLISTM_PATHO)/%.d, $(CLISTM_USR_SRCS))


# Compilation variables
CLISTM_CC = arm-none-eabi-gcc
CLISTM_SPEC_FLAG = --specs=nano.specs
CLISTM_CFLAGS = -mcpu=cortex-m4 -mthumb $(CLISTM_SPEC_FLAG)
CLISTM_ST_INCLUDE = $(CLISTM_CMSIS)/Device/ST/STM32F4xx/Include
CLISTM_CORE_INCLUDE = $(CLISTM_CMSIS)/Core/Include

CLISTM_HAL_INCLUDE = $(CLISTM_HAL)/Inc

CLISTM_USR_INC_PATHS = $(addprefix -I, $(CLISTM_PATHS))
CLISTM_CPPFLAGS = -MMD -MP -I$(CLISTM_SYS_DIR) -I$(CLISTM_ST_INCLUDE) -I$(CLISTM_CORE_INCLUDE) -I$(CLISTM_HAL_INCLUDE) $(CLISTM_USR_INC_PATHS) -D$(CLISTM_MODEL_NUM)
CLISTM_LDFLAGS = -T $(CLISTM_LINKER_FILE)


# Output program
CLISTM_TARGET_EXTENSION = elf
CLISTM_PROGRAM = $(CLISTM_PATHB)/program.$(CLISTM_TARGET_EXTENSION)


# Programmer variables
CLISTM_PROGRAMMER = openocd
CLISTM_PROGRAMMER_FLAGS = -f interface/stlink.cfg -f target/stm32f4x.cfg


CLISTM_SYS_PATHO_DIR = $(CLISTM_PATHO)/command_line_stm32

CLISTM_HAL_SRC_PREFIX = stm32f4xx_hal_
CLISTM_HAL_MODULES = gpio
CLISTM_HAL_OBJS = $(addsuffix .o, $(addprefix $(CLISTM_SYS_PATHO_DIR)/$(CLISTM_HAL_SRC_PREFIX), $(CLISTM_HAL_MODULES)))


CLISTM_SYS_SRCS = system_stm32f4xx.o startup.o stm32f4xx_hal.o stm32f4xx_hal_cortex.o
CLISTM_SYSTEM_OBJS = $(addprefix $(CLISTM_SYS_PATHO_DIR)/, $(CLISTM_SYS_SRCS))


# Rules for building program
build: $(CLISTM_PROGRAM) | $(CLISTM_BUILD_PATHS)

$(CLISTM_PROGRAM): $(CLISTM_USR_OBJS) $(CLISTM_SYSTEM_OBJS) $(CLISTM_HAL_OBJS) | $(CLISTM_BUILD_PATHS)
	$(CLISTM_CC) $(CLISTM_CFLAGS) $(CLISTM_CPPFLAGS) $(CLISTM_LDFLAGS) $^ -o $@

$(CLISTM_PATHO)/%.o: %.c | $(CLISTM_BUILD_PATHS)
	$(CLISTM_CC) $(CLISTM_CFLAGS) $(CLISTM_CPPFLAGS) -c $< -o $@

$(CLISTM_SYS_PATHO_DIR)/system_stm32f4xx.o: $(CLISTM_CMSIS_TEMPLATE)/system_stm32f4xx.c | $(CLISTM_BUILD_PATHS)
	$(CLISTM_CC) $(CLISTM_CFLAGS) $(CLISTM_CPPFLAGS) -c $< -o $@

$(CLISTM_SYS_PATHO_DIR)/startup.o: $(CLISTM_SYS_DIR)/startup.c | $(CLISTM_BUILD_PATHS)
	$(CLISTM_CC) $(CLISTM_CFLAGS) $(CLISTM_CPPFLAGS) -c $< -o $@

$(CLISTM_SYS_PATHO_DIR)/stm32f4xx_hal.o: $(CLISTM_HAL)/Src/stm32f4xx_hal.c
	$(CLISTM_CC) $(CLISTM_CFLAGS) $(CLISTM_CPPFLAGS) -c $< -o $@

$(CLISTM_SYS_PATHO_DIR)/stm32f4xx_hal_cortex.o: $(CLISTM_HAL)/Src/stm32f4xx_hal_cortex.c
	$(CLISTM_CC) $(CLISTM_CFLAGS) $(CLISTM_CPPFLAGS) -c $< -o $@

$(CLISTM_SYS_PATHO_DIR)/$(CLISTM_HAL_SRC_PREFIX)%.o: $(CLISTM_HAL)/Src/$(CLISTM_HAL_SRC_PREFIX)%.c
	$(CLISTM_CC) $(CLISTM_CFLAGS) $(CLISTM_CPPFLAGS) -c $< -o $@

$(CLISTM_BUILD_PATHS):
	mkdir -p $@


# Rule for flashing mcu
flash: $(CLISTM_PROGRAM)
	$(CLISTM_PROGRAMMER) $(CLISTM_PROGRAMMER_FLAGS) -c "program $(CLISTM_PATHB)/program.elf verify reset exit"

-include $(CLISTM_USR_DEPS)

.PHONY: build flash

