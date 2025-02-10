#include <stdint.h>

// Define start address, size, and end address of SRAM to define the
// initialization address of the stack pointer which should be initialized
// to point at the end of SRAM.
#define SRAM_START                 ( 0x20000000U )
#define SRAM_SIZE                  ( 128U * 1024U )              // 128 * kilobyte (1024 bytes) = 128 kilobytes
#define SRAM_END                   ( SRAM_START + SRAM_SIZE )
#define STACK_POINTER_INIT_ADDRESS ( SRAM_END )

#define ISR_VECTOR_SIZE_WORDS 102                                // STM32F411RE Reference Manual Section 10.2
                                                                 
 
// Interrupt Vector Table
//
// Aliasing handlers to the default handler and declaring them weak so they can be overridden
// later in the application code as neccessary.
//
// System Exception Handlers
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

// Other Handlers
void WWDG_Handler()                   __attribute__( (weak, alias( "Default_Handler" ) ) );
void EXTI16_PVD_Handler()             __attribute__( (weak, alias( "Default_Handler" ) ) );
void EXTI21_TAMP_STAMP_Handler()      __attribute__( (weak, alias( "Default_Handler" ) ) );
void EXTI22_RTC_WKUP_Handler()        __attribute__( (weak, alias( "Default_Handler" ) ) );
void FLASH_Handler()                  __attribute__( (weak, alias( "Default_Handler" ) ) );
void RCC_Handler()                    __attribute__( (weak, alias( "Default_Handler" ) ) );
void EXTI0_Handler()                  __attribute__( (weak, alias( "Default_Handler" ) ) );
void EXTI1_Handler()                  __attribute__( (weak, alias( "Default_Handler" ) ) );
void EXTI2_Handler()                  __attribute__( (weak, alias( "Default_Handler" ) ) );
void EXTI3_Handler()                  __attribute__( (weak, alias( "Default_Handler" ) ) );
void EXTI4_Handler()                  __attribute__( (weak, alias( "Default_Handler" ) ) );
void DMA1_Stream0_Handler()           __attribute__( (weak, alias( "Default_Handler" ) ) );
void DMA1_Stream1_Handler()           __attribute__( (weak, alias( "Default_Handler" ) ) );
void DMA1_Stream2_Handler()           __attribute__( (weak, alias( "Default_Handler" ) ) );
void DMA1_Stream3_Handler()           __attribute__( (weak, alias( "Default_Handler" ) ) );
void DMA1_Stream4_Handler()           __attribute__( (weak, alias( "Default_Handler" ) ) );
void DMA1_Stream5_Handler()           __attribute__( (weak, alias( "Default_Handler" ) ) );
void DMA1_Stream6_Handler()           __attribute__( (weak, alias( "Default_Handler" ) ) );
void ADC_Handler()                    __attribute__( (weak, alias( "Default_Handler" ) ) );
void EXTI9_5_Handler()                __attribute__( (weak, alias( "Default_Handler" ) ) );
void TIM1_BRK_TIM9_Handler()          __attribute__( (weak, alias( "Default_Handler" ) ) );
void TIM1_UP_TIM10_Handler()          __attribute__( (weak, alias( "Default_Handler" ) ) );
void TIM1_TRG_COM_TIM11_Handler()     __attribute__( (weak, alias( "Default_Handler" ) ) );
void TIM1_CC_Handler()                __attribute__( (weak, alias( "Default_Handler" ) ) );
void TIM2_Handler()                   __attribute__( (weak, alias( "Default_Handler" ) ) );
void TIM3_Handler()                   __attribute__( (weak, alias( "Default_Handler" ) ) );
void TIM4_Handler()                   __attribute__( (weak, alias( "Default_Handler" ) ) );
void I2C1_EV_Handler()                __attribute__( (weak, alias( "Default_Handler" ) ) );
void I2C1_ER_Handler()                __attribute__( (weak, alias( "Default_Handler" ) ) );
void I2C2_EV_Handler()                __attribute__( (weak, alias( "Default_Handler" ) ) );
void I2C2_ER_Handler()                __attribute__( (weak, alias( "Default_Handler" ) ) );
void SPI1_Handler()                   __attribute__( (weak, alias( "Default_Handler" ) ) );
void SPI2_Handler()                   __attribute__( (weak, alias( "Default_Handler" ) ) );
void USART1_Handler()                 __attribute__( (weak, alias( "Default_Handler" ) ) );
void USART2_Handler()                 __attribute__( (weak, alias( "Default_Handler" ) ) );
void EXTI15_10_Handler()              __attribute__( (weak, alias( "Default_Handler" ) ) );
void EXTI17_RTC_Alarm_Handler()       __attribute__( (weak, alias( "Default_Handler" ) ) );
void EXTI18_OTG_FS_WKUP_Handler()     __attribute__( (weak, alias( "Default_Handler" ) ) );
void DMA1_Stream7_Handler()           __attribute__( (weak, alias( "Default_Handler" ) ) );
void SDIO_Handler()                   __attribute__( (weak, alias( "Default_Handler" ) ) );
void TIM5_Handler()                   __attribute__( (weak, alias( "Default_Handler" ) ) );
void SPI3_Handler()                   __attribute__( (weak, alias( "Default_Handler" ) ) );
void DMA2_Stream0_Handler()           __attribute__( (weak, alias( "Default_Handler" ) ) );
void DMA2_Stream1_Handler()           __attribute__( (weak, alias( "Default_Handler" ) ) );
void DMA2_Stream2_Handler()           __attribute__( (weak, alias( "Default_Handler" ) ) );
void DMA2_Stream3_Handler()           __attribute__( (weak, alias( "Default_Handler" ) ) );
void DMA2_Stream4_Handler()           __attribute__( (weak, alias( "Default_Handler" ) ) );
void OTG_FS_Handler()                 __attribute__( (weak, alias( "Default_Handler" ) ) );
void DMA2_Stream5_Handler()           __attribute__( (weak, alias( "Default_Handler" ) ) );
void DMA2_Stream6_Handler()           __attribute__( (weak, alias( "Default_Handler" ) ) );
void DMA2_Stream7_Handler()           __attribute__( (weak, alias( "Default_Handler" ) ) );
void USART6_Handler()                 __attribute__( (weak, alias( "Default_Handler" ) ) );
void I2C3_EV_Handler()                __attribute__( (weak, alias( "Default_Handler" ) ) );
void I2C3_ER_Handler()                __attribute__( (weak, alias( "Default_Handler" ) ) );
void FPU_Handler()                    __attribute__( (weak, alias( "Default_Handler" ) ) );
void SPI4_Handler()                   __attribute__( (weak, alias( "Default_Handler" ) ) );
void SPI5_Handler()                   __attribute__( (weak, alias( "Default_Handler" ) ) );

// Define isr_vector table.
// The section attribute ensures that it ends up in the correct memory section.
uint32_t isr_vector[ISR_VECTOR_SIZE_WORDS] __attribute__( ( section( ".isr_vector" ) ) ) = 
{
    STACK_POINTER_INIT_ADDRESS,            // Main stack pointer address must be the first address stored as the first word in the interrupt vector table (Progamming Manual 2.1.3).
    ( uint32_t )&Reset_Handler                 ,
    ( uint32_t )&NMI_Handler                   ,
    ( uint32_t )&HardFault_Handler             ,
    ( uint32_t )&MemManage_Handler             ,
    ( uint32_t )&BusFault_Handler              ,
    ( uint32_t )&UsageFault_Handler            ,
    0                                          ,   // Zeros indicate reserved words.
    0                                          ,
    0                                          ,
    0                                          ,
    ( uint32_t )&SVCall_Handler                ,
    ( uint32_t )&DebugMonitor_Handler          ,
    0,
    ( uint32_t )&PendSV_Handler                ,
    ( uint32_t )&Systick_Handler               ,
    ( uint32_t )&WWDG_Handler                  ,
    ( uint32_t )&EXTI16_PVD_Handler            ,
    ( uint32_t )&EXTI21_TAMP_STAMP_Handler     ,
    ( uint32_t )&EXTI22_RTC_WKUP_Handler       ,
    ( uint32_t )&FLASH_Handler                 ,
    ( uint32_t )&RCC_Handler                   ,
    ( uint32_t )&EXTI0_Handler                 ,
    ( uint32_t )&EXTI1_Handler                 ,
    ( uint32_t )&EXTI2_Handler                 ,
    ( uint32_t )&EXTI3_Handler                 ,
    ( uint32_t )&EXTI4_Handler                 ,
    ( uint32_t )&DMA1_Stream0_Handler          ,
    ( uint32_t )&DMA1_Stream1_Handler          ,
    ( uint32_t )&DMA1_Stream2_Handler          ,
    ( uint32_t )&DMA1_Stream3_Handler          ,
    ( uint32_t )&DMA1_Stream4_Handler          ,
    ( uint32_t )&DMA1_Stream5_Handler          ,
    ( uint32_t )&DMA1_Stream6_Handler          ,
    ( uint32_t )&ADC_Handler                   ,
    ( uint32_t )&EXTI9_5_Handler               ,
    ( uint32_t )&TIM1_BRK_TIM9_Handler         ,
    ( uint32_t )&TIM1_UP_TIM10_Handler         ,
    ( uint32_t )&TIM1_TRG_COM_TIM11_Handler    ,
    ( uint32_t )&TIM1_CC_Handler               ,
    ( uint32_t )&TIM2_Handler                  ,
    ( uint32_t )&TIM3_Handler                  ,
    ( uint32_t )&TIM4_Handler                  ,
    ( uint32_t )&I2C1_EV_Handler               ,
    ( uint32_t )&I2C1_ER_Handler               ,
    ( uint32_t )&I2C2_EV_Handler               ,
    ( uint32_t )&I2C2_ER_Handler               ,
    ( uint32_t )&SPI1_Handler                  ,
    ( uint32_t )&SPI2_Handler                  ,
    ( uint32_t )&USART1_Handler                ,
    ( uint32_t )&USART2_Handler                ,
    ( uint32_t )&EXTI15_10_Handler             ,
    ( uint32_t )&EXTI17_RTC_Alarm_Handler      ,
    ( uint32_t )&EXTI18_OTG_FS_WKUP_Handler    ,
    ( uint32_t )&DMA1_Stream7_Handler          ,
    ( uint32_t )&SDIO_Handler                  ,
    ( uint32_t )&TIM5_Handler                  ,
    ( uint32_t )&SPI3_Handler                  ,
    ( uint32_t )&DMA2_Stream0_Handler          ,
    ( uint32_t )&DMA2_Stream1_Handler          ,
    ( uint32_t )&DMA2_Stream2_Handler          ,
    ( uint32_t )&DMA2_Stream3_Handler          ,
    ( uint32_t )&DMA2_Stream4_Handler          ,
    ( uint32_t )&OTG_FS_Handler                ,
    ( uint32_t )&DMA2_Stream5_Handler          ,
    ( uint32_t )&DMA2_Stream6_Handler          ,
    ( uint32_t )&DMA2_Stream7_Handler          ,
    ( uint32_t )&USART6_Handler                ,
    ( uint32_t )&I2C3_EV_Handler               ,
    ( uint32_t )&I2C3_ER_Handler               ,
    ( uint32_t )&FPU_Handler                   ,
    ( uint32_t )&SPI4_Handler                  ,
    ( uint32_t )&SPI5_Handler
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




