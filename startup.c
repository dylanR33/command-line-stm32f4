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
void reset_handler();
void default_handler();
void nmi_handler();             __attribute__( (weak, alias( "default_handler" ) ) );
void hard_fault_handler();      __attribute__( (weak, alias( "default_handler" ) ) );
void mem_manage_handler();      __attribute__( (weak, alias( "default_handler" ) ) );
void bus_fault_handler();       __attribute__( (weak, alias( "default_handler" ) ) );
void usage_fault_handler();     __attribute__( (weak, alias( "default_handler" ) ) );
void svcall_handler();          __attribute__( (weak, alias( "default_handler" ) ) );
void debug_monitor_handler();   __attribute__( (weak, alias( "default_handler" ) ) );
void pensv_handler();           __attribute__( (weak, alias( "default_handler" ) ) );
void systick_handler();         __attribute__( (weak, alias( "default_handler" ) ) );
// Declare rest of interrupt handlers.

// Define isr_vector table.
// The section attribute ensures that it ends up in the correct memory section.
uint32_t isr_vector[ISR_VECTOR_SIZE_WORDS] __attribute__( ( section( ".isr_vector" ) ) ) = 
{
    STACK_POINTER_INIT_ADDRESS,             // Main stack pointer address must be the first address stored as the first word in the interrupt vector table (Progamming Manual 2.1.3).
    ( uint32_t )&reset_handler          ,
    ( uint32_t )&nmi_handler            ,
    ( uint32_t )&hard_fault_handler     ,
    ( uint32_t )&mem_manage_handler     ,
    ( uint32_t )&bus_fault_handler      ,
    ( uint32_t )&usage_fault_handler    ,
    0                                   ,   // Zeros indicate reserved words.
    0                                   ,
    0                                   ,
    0                                   ,
    ( uint32_t )&svcall_handler         ,
    ( uint32_t )&debug_monitor_handler  ,
    0,
    ( uint32_t )&pensv_handler          ,
    ( uint32_t )&systick_handler        ,
    // Include rest of the interrupt handlers ...
};

void default_handler()
{
    while (1);
}

// Declare the symbols defined within the linker script. Extern means these variables are defined in a seperate file.
extern uint32_t _etext, _sdata, _edata, _sbss, _ebss;
void main();

// This is defined as the program entry point within the linker script.
void reset_handler()
{
    // Copy .data from FLASH memory to SRAM memory.
    uint32_t data_size  = ( uint32_t )&_edata - ( uint32_t )&_sdata;
    uint8_t* flash_data = ( uint8_t* )&_etext;
    uint8_t* sram_data  = ( uint8_t* )&_sdata;

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
    
    // Call main function.
    main();
}




