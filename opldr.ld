OUTPUT_FORMAT(binary)
OUTPUT_ARCH(i386)
ENTRY(_init8018x_and_start)

/*
 * Code should be loaded to 0x10000 (CS=0x1000, IP=0x0000), which is the RAM.
 */
SECTIONS {
    . = 0x0;
    /* with a CS=0x1000, this should land on 0x10000+0x0000 = 0x10000 */
    .text 0x0000 : AT(0x0000) {
        *(.text);
        *(.text.*);
        *(.rodata*);

        _data_load = . ;

        stack_bottom = . ;
        . = . + 0x100;
        stack_start = . ;

        data_start = . ;
        *(.data*);
        data_end = . ;

        . = ALIGN(4);
        bss_start = . ;
        *(.bss*);
        bss_end = . ;
    }

    /* Throw away everything else. */
    /DISCARD/ : { *(*) }
}
