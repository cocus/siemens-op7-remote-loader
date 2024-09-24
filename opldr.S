.code16

.include "80c186es.h"

// This should land on 0x1000:0x0000
.section .text, "ax"
.globl _init8018x_and_start
_init8018x_and_start:
    cli // no ints :)

    // disable stupid watchdog :D
    mov $WDTCON, %dx
    // key seq 1 (WDT write)
    mov $0x3333, %ax
    out %ax, %dx

    // key seq 2 (WDT write)
    mov $0xCCCC, %ax
    out %ax, %dx

    // actual data (WDT write)
    mov $0x4000, %ax // ENA = 0 (disabled)
    out %ax, %dx

    // disable dma, flow control, no rsie, no txie, no rxie, no parity sp0
    //mov $SP0CT, %dx
    //in %dx, %ax
    //and $0x460, %ax
    //or $0x61, %ax // transmit, receive, operate in 8 bit
    //out %ax, %dx

    // disable dma sp1
    mov $SP1CT, %dx
    in %dx, %ax
    and $0x460, %ax
    or $0x61, %ax // transmit, receive, operate in 8 bit
    out %ax, %dx

    // disable SP1 ints
    mov $0x18, %ax
    mov $SP1CON, %dx
    out %ax, %dx
    // disable SP0 ints
    //mov $SP0CON, %dx
    //out %ax, %dx

    mov %cs, %ax
    mov %ax, %ds
    mov %ax, %es
    mov %ax, %ss

    movw $stack_start, %sp

    // Clear STS
    mov $SP1STS, %dx
    in %dx, %ax

    //mov $SP0STS, %dx
    //in %dx, %ax

    // Clear the stack
    lea stack_start, %ax
    mov $stack_start,%cx
    sub $stack_bottom,%cx
    mov %ax, %di
    xor %ax, %ax
    std
    rep stosb
    cld

    // Clear bss
    mov $bss_start, %di
    mov $bss_end, %cx
    sub $bss_start, %cx
    mov $0, %al
    rep stosb

    // Initialize rw data
    mov $data_start, %di
    mov $data_end, %cx
    sub %di, %cx
    mov $_data_load, %si
    rep movsb

    jmp root
