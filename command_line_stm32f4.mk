# Paths that should be defined
# CLISTM_SRC_DIRS: all directories containing source code
# CLISTM_BUILD_DIR: top level build directory
# CLISTM_MODEL_NUM: specific stm mcu model within F4 family
#
# Optional Define
# CLISTM_HAL_MODULES: HAL modules to incorporate into build
#
# Ensure necessary defines exist, else exit
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


# Prefix to HAL source files
CLISTM_HAL_SRC_PREFIX = stm32f4xx_hal_


# Default startup file if not already set by user
CLISTM_STARTUP_FILE ?= $(CLISTM_SYS_DIR)/startup.c


# Default linker script path if not already set by user
CLISTM_LINKER_FILE ?= $(CLISTM_SYS_DIR)/linker_script.ld


# Source code paths
CLISTM_PATHS = $(CLISTM_SRC_DIRS)


# Build paths
CLISTM_PATHB = $(CLISTM_BUILD_DIR)/command_line_stm32_build
CLISTM_PATHO = $(CLISTM_PATHB)/objs
CLISTM_SYS_PATHO = $(CLISTM_PATHO)/system
CLISTM_HAL_PATHO = $(CLISTM_PATHO)/hal
CLISTM_PATHO_DIRS = $(addprefix $(CLISTM_PATHO)/, $(CLISTM_PATHS)) $(CLISTM_SYS_PATHO) $(CLISTM_HAL_PATHO)
CLISTM_BUILD_PATHS = $(CLISTM_PATHB) $(CLISTM_PATHO) $(CLISTM_PATHO_DIRS)


# Essential and optionally HAL source files and corresponding object and dependancy files
CLISTM_SYS_SRCS = system_stm32f4xx.o startup.o syscalls.o usart_print.o
CLISTM_SYS_OBJS = $(addprefix $(CLISTM_SYS_PATHO)/, $(CLISTM_SYS_SRCS))
CLISTM_SYS_DEPS = $(patsubst %.o, %.d, $(CLISTM_SYS_OBJS))

ifdef CLISTM_HAL_MODULES
  $(info HAL will be incorporated into build)
  CLISTM_HAL_MODULES += cortex rcc
  CLISTM_HAL_OBJS = $(addsuffix .o, $(CLISTM_HAL_PATHO)/stm32f4xx_hal $(addprefix $(CLISTM_HAL_PATHO)/$(CLISTM_HAL_SRC_PREFIX), $(CLISTM_HAL_MODULES)))
  CLISTM_HAL_DEPS = $(patsubst %.o, %.d, $(CLISTM_HAL_OBJS))
endif


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
CLISTM_LDFLAGS = -u  _printf_float -T $(CLISTM_LINKER_FILE)


# Output program
CLISTM_TARGET_EXTENSION = elf
CLISTM_PROGRAM = $(CLISTM_PATHB)/program.$(CLISTM_TARGET_EXTENSION)


# Programmer variables
CLISTM_PROGRAMMER = openocd
CLISTM_PROGRAMMER_FLAGS = -f interface/stlink.cfg -f target/stm32f4x.cfg


# Rules for building program
build: $(CLISTM_PROGRAM) | $(CLISTM_BUILD_PATHS)

$(CLISTM_PROGRAM): $(CLISTM_USR_OBJS) $(CLISTM_SYS_OBJS) $(CLISTM_HAL_OBJS) | $(CLISTM_BUILD_PATHS)
	$(CLISTM_CC) $(CLISTM_CFLAGS) $(CLISTM_CPPFLAGS) $(CLISTM_LDFLAGS) $^ -o $@

# Rule for user files
$(CLISTM_PATHO)/%.o: %.c | $(CLISTM_BUILD_PATHS)
	$(CLISTM_CC) $(CLISTM_CFLAGS) $(CLISTM_CPPFLAGS) -c $< -o $@

# Rule for main CMSIS system file
$(CLISTM_SYS_PATHO)/system_stm32f4xx.o: $(CLISTM_CMSIS_TEMPLATE)/system_stm32f4xx.c | $(CLISTM_BUILD_PATHS)
	$(CLISTM_CC) $(CLISTM_CFLAGS) $(CLISTM_CPPFLAGS) -c $< -o $@

# Rule for system files
$(CLISTM_SYS_PATHO)/%.o: $(CLISTM_SYS_DIR)/%.c | $(CLISTM_BUILD_PATHS)
	$(CLISTM_CC) $(CLISTM_CFLAGS) $(CLISTM_CPPFLAGS) -c $< -o $@

# Rule for HAL files
$(CLISTM_HAL_PATHO)/%.o: $(CLISTM_HAL)/Src/%.c | $(CLISTM_BUILD_PATHS)
	$(CLISTM_CC) $(CLISTM_CFLAGS) $(CLISTM_CPPFLAGS) -c $< -o $@

$(CLISTM_BUILD_PATHS):
	mkdir -p $@


# Rule for flashing mcu
flash: $(CLISTM_PROGRAM)
	$(CLISTM_PROGRAMMER) $(CLISTM_PROGRAMMER_FLAGS) -c "program $(CLISTM_PATHB)/program.elf verify reset exit"


# Include all dependancy files
-include $(CLISTM_USR_DEPS)
-include $(CLISTM_ESSENTIAL_DEPS)
-include $(CLISTM_HAL_DEPS)

.PHONY: build flash

