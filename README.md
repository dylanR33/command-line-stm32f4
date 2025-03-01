# command-line-stm32f4

## Incorperation Into Project
This repository serves as a drop in setup for projects using the STM32F4 family of 
MCU's. The intended workflow is adding this repository as a git submodule into your 
project. This repository is self-contained in that it contains STM32CubeF4 a set 
of device drivers for the F4 family of MCU's so no other repositories need to be 
cloned externally.

Use the following command to add this repository as a git submodule of your project:
```
git submodule add https://github.com/dylanR33/command-line-stm32f4.git
```

Use the following command to clone this repository into your project:
```
git clone --recurse-submodules https://github.com/dylanR33/command-line-stm32f4.git
```

## Necessary Software
The following are software packages necessary to use this repository.

`arm-none-eabi-gcc`
`arm-none-eabi-newlib`
`GNU make`
`openocd`

Please download them with your preferred package manager.


## Usage
Before continuing ensure you have read the sections [Necessary Variable Definitions](#necessary-variable-definitions) 
and [Optional Variable Definitions](#optional-variable-definitions) below.

Your project should contain a makefile of its own which needs to contain two things

1. Definitions for the variables outlined in the sections just mentioned

2. Inclusion of the makefile `command_line_stm32f4.mk` found within this repository

For example:
```
CLISTM_SRC_DIRS = path_to/source_dir1 path_to/source_dir2

CLISTM_BUILD_DIR = path_to/build_dir

CLISTM_MODEL_NUM = STM32F411xE

CLISTM_HAL_MODULES = gpio

include path_to/command-line-stm32f4/command_line_stm32f4.mk
```

The makefile `command_line_stm32f4.mk` contains the necessary rules to build your 
source files and flash the executable onto your target hardware. These rules are 
`build` and `flash` respectively. To invoke them run the following from the 
directory containing your own makefile.
```
make build
```
followed by
```
make flash
```

Alternatively simply use `flash` to build out of date files and flash the program 
as the rule flash contains the executable as a prerequisite.


## Necessary Variable Definitions
The following paths should be defined for the makefile to work correctly.

`CLISTM_SRC_DIRS`: directories containing source code

`CLISTM_BUILD_DIR`: your projects build directory

`CLISTM_MODEL_NUM`: the specific STM32 model number within the F4 family (See options 
[here](#list-of-supported-definitions-for-clistm_model_num)).


## Optional Variable Definitions
The variable `CLISTM_HAL_MODULES` is an optional variable and if used should specify the 
HAL modules the user would like to incorporate into their build (see options 
[here](#list-of-supported-hal-modules)). When used the makefile also incorporates the base 
HAL files necessary to use the other modules. If not defined no HAL modules will be part of the build.

The variable `CLISTM_LINKER_FILE` is an optional variable which defines the path to a user 
provided linker file to use during the linking process. If not defined a default linker file is 
used which is targeted for the `STM32F446xx`. See directory `templates` for a linker file 
template to use as a starting point. The main changes necessary are within the `MEMORY` section.

The variable `CLISTM_STARTUP_FILE` is an optional variable which defines the path to a user 
provided startup file to use for compilation. If not defined a default startup file is used 
which is targeted for the `STM32F446xx`. See directory `templates` for a startup file template 
to use as a starting point.

The variable `CLISTM_WFLAGS` is an optional variable which defines warning flags 
to pass to the compiler. Can also be used for additional compiler flags.


## Minimal Necessary Configuration When Using HAL and Template
Before any application or HAL peripheral module code runs the user should call the 
HAL function HAL_Init() and proceedingly configure the system clock. Within the 
directory `templates` a minimal configuration is provided along with a simple main() 
and Systick_Handler() definition for using the HAL provided HAL_Delay() function.


## Templates
Some files to get you started for a main, linker, and startup file.


## Examples
The directory `examples` contains minimal examples of how to incorperate this repository 
into a project.


## List of Supported Definitions for CLISTM_MODEL_NUM
```
STM32F401xC STM32F411xE STM32F417xx STM32F469xx 
STM32F401xE STM32F412Cx STM32F423xx STM32F479xx
STM32F405xx STM32F412Rx STM32F427xx 
STM32F407xx STM32F412Vx STM32F429xx 
STM32F410Cx STM32F412Zx STM32F437xx
STM32F410Rx STM32F413xx STM32F439xx
STM32F410Tx STM32F415xx STM32F446xx
```


## List of supported HAL modules
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

