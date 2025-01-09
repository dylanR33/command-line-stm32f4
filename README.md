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

1. Definitions for the variables outlined in the sections "Necessary Variable 
Definitions" and "Optional Variable Definition".

2. Inclusion of the makefile `command_line_stm32.mk` found within this repository

For example:
```
CLISTM_SRC_DIRS = path_to/source_dir1 path_to/source_dir2

CLISTM_BUILD_DIR = path_to/build_dir

CLISTM_MODEL_NUM = STM32F411xE

CLISTM_HAL_MODULES = gpio

include path_to/command_line_stm32/command_line_stm32.mk
```

The makefile `command_line_stm32.mk` contains the necessary rules to build your 
source files and flash the executable onto your target hardware. These rules are 
`build` and `flash` respectively. To invoke them run the following from the 
directory containing your own makefile.
```
make build // compiles source files
```
followed by
```
make flash // flashes program onto target hardware
```

Alternatively simply use `flash` to build out of date files and flash the program 
as the rule flash contains the executable as a prerequisite.


## Necessary Variable Definitions
The following paths should be defined for the makefile to work correctly.

`CLISTM_SRC_DIRS`: directories containing source code

`CLISTM_BUILD_DIR`: your projects build directory

`CLISTM_MODEL_NUM`: the specific STM32 model number within the F4 family (See options in 
section "List of Supported Definitions for CLISTM_MODEL_NUM").


## Optional Variable Definition
The variable `CLISTM_HAL_MODULES` is an optional variable and if used should specify the 
HAL modules the user would like to incorporate into their build (see options in section 
"List of supported HAL modules"). When used the makefile 
also incorporates the base HAL files necessary to use the other modules.

If not defined no HAL modules will be part of the build.


## Minimal Necessary Configuration When Using HAL and Template
Before any application or HAL peripheral module code runs the user should call the 
HAL function HAL_Init() and proceedingly configure the system clock. Within the 
directory 'template' a minimal configuration is provided along with a simple main() 
and Systick_Handler() definition for using the HAL provided HAL_Delay() function.


## Examples
The directory `examples` contains a minimal examples of how to incorperate this repository 
into a project. Note that these examples assume `CLISTM_MODEL_NUM` is defined as `STM32F411XE`


## List of Supported Definitions for CLISTM_MODEL_NUM
```
STM32F401XC STM32F411XE STM32F417XX STM32F469XX 
STM32F401XE STM32F412CX STM32F423XX STM32F479XX
STM32F405XX STM32F412RX STM32F427XX 
STM32F407XX STM32F412VX STM32F429XX 
STM32F410CX STM32F412ZX STM32F437XX
STM32F410RX STM32F413XX STM32F439XX
STM32F410TX STM32F415XX STM32F446XX
```


## List of supported HAL modules (Definitions for CLISTM_HAL_MODULES)
```
adc               adc_ex          can
cec               crc             cryp
cryp_ex           dac             dac_ex
dcmi              dcmi_ex         dfsdm
dma               dma2d           dma_ex
dsi               eth             exti
flash             flash_ex        flash_ramfunc
fmpi2c            fmpi2c_ex       fmpsmbus
fmpsmbus_ex       gpio            hash
hash_ex           hcd             i2c
i2c_ex            i2s             i2s_ex
irda              iwdg            lptim
ltdc              ltdc_ex         mmc
nand              nor             pccard
pcd               pcd_ex          pwr
pwr_ex            qspi            rcc_ex
rng               rtc             rtc_ex
sai               sai_ex          sd
sdram             smartcard       smbus
spdifrx           spi             sram
tim               tim_ex          uart
usart             wwdg
```

