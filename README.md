# command_line_stm32

## Incorperation Into Project
This repository serves as a drop in setup for projects using the STM32F4 family of 
MCU's. The intended workflow is adding this repository as a git submodule into your 
project. This repository is self-contained in that it contains STM32CubeF4 a set 
of device drivers for the F4 family of MCU's so no other repositories need to be 
cloned externally.

Use the following command to add this repository as a git submodule of your project:
```
git submodule add https://github.com/dylanR33/command_line_stm32.git
```

Use the following command to clone this repository into your project:
```
git clone --recurse-submodules https://github.com/dylanR33/command_line_stm32.git
```


## Usage
Before continuing ensure you have read the section "Necessary Variable Definitions" 
below.

Your project should contain a makefile of its own which needs to contain two things

1. Definitions for the necessary variables outlined in the section "Necessary Variable 
Definitions"

2. Inclusion of the makefile 'command_line_stm32.mk' found within this repository

For example:
```
CLISTM_SRC_DIRS = path_to/source_dir1 path_to/source_dir2

CLISTM_BUILD_DIR = path_to/build_dir

CLISTM_STM_MODEL = STM32F411xE

include path_to/command_line_stm32/command_line_stm32.mk
```

The makefile 'command_line_stm32.mk' contains the necessary rules to build your 
source files and flash the executable onto your target hardware. These rules are 
'build' and 'flash' respectively. To invoke them run the following from the 
directory containing your own makefile.
```
make build // compiles source files
```
followed by
```
make flash // flashes program onto target hardware
```

Alternatively simply use 'flash' to build out of date files and flash the program 
as the rule 'flash' contains the executable as a prerequisite.


## Necessary Variable Definitions
The following paths should be defined for the makefile to work correctly.

CLISTM_SRC_DIRS: directories containing source code

CLISTM_BUILD_DIR: your projects build directory

CLISTM_STM_MODEL: the specific STM32 model number within the F4 family (See options below)


## List of supported definitions for CLISTM_MODEL_NUM
```
STM32f401XC STM32f411XE STM32f417XX STM32f469XX 
STM32f401XE STM32f412CX STM32f423XX STM32f479XX
STM32f405XX STM32f412RX STM32f427XX 
STM32f407XX STM32f412VX STM32f429XX 
STM32f410CX STM32f412ZX STM32f437XX
STM32f410RX STM32f413XX STM32f439XX
STM32f410TX STM32f415XX STM32f446XX
```


## Example
The directory 'example' contains a minimal example of how to incorperate this repository 
into a project. 


## Note on stm32f3xx_hal_conf.h
As stated in STM32CubeF4/Drivers/STM32F4xx_HAL_Driver/Inc/stm32f4xx_hal_conf_template.h 
stm32f4xx_hal_conf_template.h should be copied to the system directory and renamed to 
stm32f4xx_hal_conf.h
