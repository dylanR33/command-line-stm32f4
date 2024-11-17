ENTRY( reset_handler )    // Specifies programs entry point. Startup code will 
                        // have reset_handler() function to handle all memory 
                        // initialization, so this will be the starting point.

MEMORY                  // Describes location and size of blocks of memory in the target.
{
    FLASH ( rx ): ORIGIN = 0x80000000, LENGTH = 512K  // Define start of flash memory and its size. (Found in STM32F411 Datasheet, Section 2 / Section 5)
    SRAM ( rwx ): ORIGIN = 0x20000000, LENGTH = 128K  // Define start of sram and its size. (Found in STM32F411RE Datasheet, Section 5)
}

SECTIONS                // Controls where input sections are placed into output sections, their order in the output file, and to which output sections they are allocated.
{
    .isr_vector :       // Defines a section
    {
        KEEP( *( .isr_vector ) )
    } >FLASH            // Assigns section to this previously defined section of memory.

    .text : 
    {
    } >FLASH

    .data :
    {
    } >SRAM AT> FLASH

    .bss :
    {
    } >SRAM
}
