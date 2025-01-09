// Define start address, size, and end address of SRAM to define the
// initialization address of the stack pointer which should be initialized
// to point at the end of SRAM.
#define SRAM_START                 ( 0x20000000U )
#define SRAM_SIZE                  ( 128U * 1024U )              // 128 * kilobyte (1024 bytes) = 128 kilobytes
#define SRAM_END                   ( SRAM_START + SRAM_SIZE )
#define STACK_POINTER_INIT_ADDRESS ( SRAM_END )

#include <stdint.h>
#define ISR_VECTOR_SIZE_WORDS 102                                // STM32F411RE Reference Manual Section 10.2

// Declaring system exception handlers of interrupt vector table. Leaving out the rest
// of the interrupt handlers.
// Aliasing handlers to the default handler and declaring them weak so they can be overridden
// later in the application code as neccessary.
void Reset_Handler();
void Default_Handler();
void NMI_Handler()            __attribute__( (weak, alias( "Default_Handler" ) ) );
void HardFault_Handler()      __attribute__( (weak, alias( "Default_Handler" ) ) );
void MemManage_Handler()      __attribute__( (weak, alias( "Default_Handler" ) ) );
void BusFault_Handler()       __attribute__( (weak, alias( "Default_Handler" ) ) );
void UsageFault_Handler()     __attribute__( (weak, alias( "Default_Handler" ) ) );
void SVCall_Handler()         __attribute__( (weak, alias( "Default_Handler" ) ) );
void DebugMonitor_Handler()   __attribute__( (weak, alias( "Default_Handler" ) ) );
void PendSV_Handler()         __attribute__( (weak, alias( "Default_Handler" ) ) );
void Systick_Handler()        __attribute__( (weak, alias( "Default_Handler" ) ) );
// Declare rest of interrupt handlers.

// Define isr_vector table.
// The section attribute ensures that it ends up in the correct memory section.
uint32_t isr_vector[ISR_VECTOR_SIZE_WORDS] __attribute__( ( section( ".isr_vector" ) ) ) = 
{
    STACK_POINTER_INIT_ADDRESS,             // Main stack pointer address must be the first address stored as the first word in the interrupt vector table (Progamming Manual 2.1.3).
    ( uint32_t )&Reset_Handler          ,
    ( uint32_t )&NMI_Handler            ,
    ( uint32_t )&HardFault_Handler     ,
    ( uint32_t )&MemManage_Handler     ,
    ( uint32_t )&BusFault_Handler      ,
    ( uint32_t )&UsageFault_Handler    ,
    0                                   ,   // Zeros indicate reserved words.
    0                                   ,
    0                                   ,
    0                                   ,
    ( uint32_t )&SVCall_Handler         ,
    ( uint32_t )&DebugMonitor_Handler  ,
    0,
    ( uint32_t )&PendSV_Handler          ,
    ( uint32_t )&Systick_Handler        ,
    // Include rest of the interrupt handlers ...
};

void Default_Handler()
{
    while (1);
}

// Declare the symbols defined within the linker script. Extern means these variables are defined in a seperate file.
extern uint32_t _etext, _sdata, _edata, _sbss, _ebss, _sidata;
void main();
void __libc_init_array();

// This is defined as the program entry point within the linker script.
void Reset_Handler()
{
    // Copy .data from FLASH memory to SRAM memory.
    uint32_t data_size  = ( uint32_t )&_edata - ( uint32_t )&_sdata;
    uint8_t* flash_data = ( uint8_t* )&_sidata; // Data load address (in flash memory)
    uint8_t* sram_data  = ( uint8_t* )&_sdata;  // Data virtual address (in sram)

    for ( uint32_t i = 0; i < data_size; i++ )
    {
        sram_data[ i ] = flash_data[ i ];
    }

    // Zero fill .bss section in SRAM.
    uint32_t bss_size = ( uint32_t )&_ebss - ( uint32_t )&_sbss;
    uint8_t* bss = ( uint8_t* )&_sbss;

    for ( uint32_t i = 0; i < bss_size; i++ )
    {
        bss[ i ] = 0;
    }
    
    // Call Newlib initialization function.
    __libc_init_array();
    // Call main function.
    main();
}




