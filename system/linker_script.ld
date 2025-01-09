ENTRY( reset_handler )                                /* 
                                                         Specifies programs entry point. Startup code will 
                                                         have reset_handler() function to handle all memory 
                                                         initialization, so this will be the starting point. 
                                                      */

MEMORY                                                /* Describes location and size of blocks of memory in the target. */
{
    FLASH ( rx ): ORIGIN = 0x08000000, LENGTH = 512K  /* Define start of flash memory and its size. (Found in STM32F411RE Datasheet, Section 3.5) */
    SRAM ( rwx ): ORIGIN = 0x20000000, LENGTH = 128K  /* Define start of sram and its size. (Found in STM32F411RE Datasheet, Section 3.7) */
}

/* 
    The areas where sections should be placed into memory are discussed in the following areas:
      - STM32F411RE Datasheet Section 5
      - ""          Reference Manual Section 3.3
      - STM32 Cortex-M4 Programming Manual Section 2.2.3
*/

                                                      /* Describes the memory layout of the output file. */
SECTIONS                                              /* Controls where input sections are placed into output sections, their order in the output file, and to which output sections they are allocated. */
{
    .isr_vector :                                     /* Defines a section in the output file. */
    {
        KEEP( *( .isr_vector ) )                      /* KEEP() prevents the input section within it from being eliminated during link-time garbage collection. */
    } >FLASH                                          /* Assigns the sections virtual memory address (VMA) and load memory address (LMA) to this previously defined region in memory. */

    .text : 
    {
        . = ALIGN( 4 );                               /* Sets the location counter ('.') to the current location counter value aligned upward to the specified amount of bytes. */

        *( .text     )                                /* States that all input sections by the name ".text" should be placed within this section of the output file. */
        *( .text.*   )
        *( .rodata   )
        *( .rodata.* )
        KEEP( *(.init) )
        KEEP( *(.fini) )
        *( .eh_frame )
        *( .ARM.exidx )

        . = ALIGN( 4 );
        _etext = .;                                   /* Defines a symbol named "_etext" with the value of the current location counter value. */
    } >FLASH

    _sidata = LOADADDR( .data );                      /* Esures the end of the text section will be the same as the load address of the data section. */

    .data :
    {
        . = ALIGN( 4 );
        _sdata = .;

        *( .data   )
        *( .data.* )
        KEEP( *(.init_array) )
        KEEP( *(.fini_array) )

        . = ALIGN( 4 );
        _edata = .;
    } >SRAM AT> FLASH                                 /* Assigns the sections VMA to the SRAM region and the sections LMA to the FLASH region. */

    .bss :
    {
        . = ALIGN( 4 );
        _sbss = .;
        __bss_start__ = _sbss;

        *( .bss   )
        *( .bss.* )

        . = ALIGN( 4 );
        _ebss = .;
        __bss_end__ = _ebss;
    } >SRAM
}

