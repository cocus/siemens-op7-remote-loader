/* 
 * Based on 80c186eb.h from Intel, (c) 1995
 *  Copyright (c) 1995, Intel Corporation 
 */ 
/*  80C186EB REGISTER DEFINITIONS */ 
#ifndef _80C186EB_ 
#define _80C186EB_
/* 
  Modify the PCB_BASE symbol to represent 
  the contents of the Relocation register (RELREG). 
 
   Set Default condtion for placement of the Peripheral 
   Control Block. 
*/ 
#ifndef  _MEM_SPACE 
#define  _IO_SPACE_ 
#endif 
 
/*  Note: when placing the Peripheral Control Block(PCB) into 
    the memory space define the PCB_BASE in terms of segment:offset. 
    ie.  a PCB base address of 0x1f000 should define PCB_BASE as 
    #define PCB_BASE  0x1000f000L. 
*/ 
    /* Set Default condition for PCB address */ 
#ifndef PCB_BASE 
#ifndef _MEM_SPACE_ 
#define PCB_BASE    0xff00 
#else 
#define PCB_BASE    0xff00000L 
#endif 
#endif 
 
/* This typedef assumes that an unsigned int is a 16-bit value, if your 
   compiler's "unsigned int" is not a 16-bit value modify the typedef to 
   a data type that is a 16-bit value. 
*/ 
//typedef unsigned int _WORD16_; 
 
  /* Note: The "far" keyword is used to create a far pointer to the 
           registers.  Some compilers may not support the "far" keyword, 
           you will need to modify "_WORD16_ far *" to match what your   
           compiler supports. 
  */ 
#ifdef _MEM_SPACE_ 
#define _MAKE_ADDRESS_(offset) (*((_WORD16_ far *) (PCB_BASE +(offset)))) 
#define _Set186Register(reg,val) ((reg) = (val)) 
#define _Set186RegisterByte(reg,val) _Set186Register(reg,val) 
#define _Get186Register(reg) (reg) 
#else 
#define _MAKE_ADDRESS_(offset) (PCB_BASE + (offset)) 
#define _Set186Register(reg,val) (outpw(reg,val)) 
#define _Set186RegisterByte(reg,val) (outp(reg,val)) 
#define _Get186Register(reg) (inpw(reg)) 
#endif 

#define RELREG	_MAKE_ADDRESS_(0xFE)	// Peripheral control block relocation register
#define RESCON	_MAKE_ADDRESS_(0xF6)	// Reset configuration register
#define PRL	_MAKE_ADDRESS_(0xF4)	// Processor release level register
#define AUXCON	_MAKE_ADDRESS_(0xF2)	// Auxiliary configuration
#define SYSCON	_MAKE_ADDRESS_(0xF0)	// System configuration register
#define WDTCON	_MAKE_ADDRESS_(0xE6)	// Watchdog timer control register
#define EDRAM	_MAKE_ADDRESS_(0xE4)	// Enable RCU register
#define CDRAM	_MAKE_ADDRESS_(0xE2)	// Clock prescaler register
#define MDRAM	_MAKE_ADDRESS_(0xE0)	// Memory partition register
#define D1CON	_MAKE_ADDRESS_(0xDA)	// DMA 1 control register
#define D1TC	_MAKE_ADDRESS_(0xD8)	// DMA 1 transfer count register
#define D1DSTH	_MAKE_ADDRESS_(0xD6)	// DMA 1 destination address high register
#define D1DSTL	_MAKE_ADDRESS_(0xD4)	// DMA 1 destination address low register
#define D1SRCH	_MAKE_ADDRESS_(0xD2)	// DMA 1 source address high register
#define D1SRCL	_MAKE_ADDRESS_(0xD0)	// DMA 1 source address low register
#define D0CON	_MAKE_ADDRESS_(0xCA)	// DMA 0 control register
#define D0TC	_MAKE_ADDRESS_(0xC8)	// DMA 0 transfer count register
#define D0DSTH	_MAKE_ADDRESS_(0xC6)	// DMA 0 destination address high register
#define D0DSTL	_MAKE_ADDRESS_(0xC4)	// DMA 0 destination address low register
#define D0SRCH	_MAKE_ADDRESS_(0xC2)	// DMA 0 source address high register
#define D0SRCL	_MAKE_ADDRESS_(0xC0)	// DMA 0 source address low register
#define MPCS	_MAKE_ADDRESS_(0xA8)	// PCS and MCS auxiliary register
#define MMCS	_MAKE_ADDRESS_(0xA6)	// Midrange memory chip select register
#define PACS	_MAKE_ADDRESS_(0xA4)	// Peripheral chip select register
#define LMCS	_MAKE_ADDRESS_(0xA2)	// Low memory chip select register
#define UMCS	_MAKE_ADDRESS_(0xA0)	// Upper memory chip select register
#define SP0BAUD	_MAKE_ADDRESS_(0x88)	// Serial port 0 baud rate divisor register
#define SP0RD	_MAKE_ADDRESS_(0x86)	// Serial port 0 receive data register
#define SP0TD	_MAKE_ADDRESS_(0x84)	// Serial port 0 transmit data register
#define SP0STS	_MAKE_ADDRESS_(0x82)	// Serial port 0 status register
#define SP0CT	_MAKE_ADDRESS_(0x80)	// Serial port 0 control register
#define PDATA1	_MAKE_ADDRESS_(0x7A)	// PIO data 1 register
#define PDIR1	_MAKE_ADDRESS_(0x78)	// PIO direction 1 register
#define PIOMODE1	_MAKE_ADDRESS_(0x76)	// PIO mode 1 register
#define PDATA0	_MAKE_ADDRESS_(0x74)	// PIO data 0 register
#define PDIR0	_MAKE_ADDRESS_(0x72)	// PIO direction 0 register
#define PIOMODE0	_MAKE_ADDRESS_(0x70)	// PIO mode 0 register
#define T2CON	_MAKE_ADDRESS_(0x66)	// Timer 2 mode/control register
#define T2CMPA	_MAKE_ADDRESS_(0x62)	// Timer 2 maxcount compare A register
#define T2CNT	_MAKE_ADDRESS_(0x60)	// Timer 2 count register
#define T1CON	_MAKE_ADDRESS_(0x5E)	// Timer 1 mode/control register
#define T1CMPB	_MAKE_ADDRESS_(0x5C)	// Timer 1 maxcount compare B register
#define T1CMPA	_MAKE_ADDRESS_(0x5A)	// Timer 1 maxcount compare A register
#define T1CNT	_MAKE_ADDRESS_(0x58)	// Timer 1 count register
#define T0CON	_MAKE_ADDRESS_(0x56)	// Timer 0 mode/control register
#define T0CMPB	_MAKE_ADDRESS_(0x54)	// Timer 0 maxcount compare B register
#define T0CMPA	_MAKE_ADDRESS_(0x52)	// Timer 0 maxcount compare A register
#define T0CNT	_MAKE_ADDRESS_(0x50)	// Timer 0 count register
#define SP0CON	_MAKE_ADDRESS_(0x44)	// Serial port 0 interrupt control register
#define SP1CON	_MAKE_ADDRESS_(0x42)	// Serial port 1 interrupt control register
#define INT4CON	_MAKE_ADDRESS_(0x40)	// INT4 control register
#define INT3CON	_MAKE_ADDRESS_(0x3E)	// INT3 control register
#define INT2CON	_MAKE_ADDRESS_(0x3C)	// INT2 control register
#define INT1CON	_MAKE_ADDRESS_(0x3A)	// INT1 control register
#define INT0CON	_MAKE_ADDRESS_(0x38)	// INT0 control register
#define DMA1CON	_MAKE_ADDRESS_(0x36)	// DMA 1 interrupt control register/INT6
#define DMA0CON	_MAKE_ADDRESS_(0x34)	// DMA 0 interrupt control register/INT5
#define TCUCON	_MAKE_ADDRESS_(0x32)	// Timer interrupt control register
#define INTSTS	_MAKE_ADDRESS_(0x30)	// Interrupt status register
#define REQST	_MAKE_ADDRESS_(0x2E)	// Interrupt request register
#define INSERV	_MAKE_ADDRESS_(0x2C)	// In-service register
#define PRIMSK	_MAKE_ADDRESS_(0x2A)	// Priority mask register
#define IMASK	_MAKE_ADDRESS_(0x28)	// Interrupt mask register
#define POLLST	_MAKE_ADDRESS_(0x26)	// Poll status register
#define POLL	_MAKE_ADDRESS_(0x24)	// Poll register
#define EOI	_MAKE_ADDRESS_(0x22)	// End-of-interrupt register
#define INTVEC	_MAKE_ADDRESS_(0x20)	// Interrupt vector register
#define SP1BAUD	_MAKE_ADDRESS_(0x18)	// Serial port 1 baud rate divisor register
#define SP1RD	_MAKE_ADDRESS_(0x16)	// Serial port 1 receive register
#define SP1TD	_MAKE_ADDRESS_(0x14)	// Serial port 1 transmit register
#define SP1STS	_MAKE_ADDRESS_(0x12)	// Serial port 1 status register
#define SP1CT	_MAKE_ADDRESS_(0x10)	// Serial port 1 control register
#define T2INTCON	_MAKE_ADDRESS_(0x3A)	// Timer 2 interrupt control register
#define T1INTCON	_MAKE_ADDRESS_(0x38)	// Timer 1 interrupt control register
#define INT6CON	_MAKE_ADDRESS_(0x36)	// INT6
#define INT5CON	_MAKE_ADDRESS_(0x34)	// INT5
#define T0INTCON	_MAKE_ADDRESS_(0x32)	// Timer 0 interrupt control register

#ifdef __ASSEMBLY__

.equ RELREG, 0xFFFE	// Peripheral control block relocation register
.equ RESCON, 0xFFF6	// Reset configuration register
.equ PRL, 0xFFF4	// Processor release level register
.equ AUXCON, 0xFFF2	// Auxiliary configuration
.equ SYSCON, 0xFFF0	// System configuration register
.equ WDTCON, 0xFFE6	// Watchdog timer control register
.equ EDRAM, 0xFFE4	// Enable RCU register
.equ CDRAM, 0xFFE2	// Clock prescaler register
.equ MDRAM, 0xFFE0	// Memory partition register
.equ D1CON, 0xFFDA	// DMA 1 control register
.equ D1TC, 0xFFD8	// DMA 1 transfer count register
.equ D1DSTH, 0xFFD6	// DMA 1 destination address high register
.equ D1DSTL, 0xFFD4	// DMA 1 destination address low register
.equ D1SRCH, 0xFFD2	// DMA 1 source address high register
.equ D1SRCL, 0xFFD0	// DMA 1 source address low register
.equ D0CON, 0xFFCA	// DMA 0 control register
.equ D0TC, 0xFFC8	// DMA 0 transfer count register
.equ D0DSTH, 0xFFC6	// DMA 0 destination address high register
.equ D0DSTL, 0xFFC4	// DMA 0 destination address low register
.equ D0SRCH, 0xFFC2	// DMA 0 source address high register
.equ D0SRCL, 0xFFC0	// DMA 0 source address low register
.equ MPCS, 0xFFA8	// PCS and MCS auxiliary register
.equ MMCS, 0xFFA6	// Midrange memory chip select register
.equ PACS, 0xFFA4	// Peripheral chip select register
.equ LMCS, 0xFFA2	// Low memory chip select register
.equ UMCS, 0xFFA0	// Upper memory chip select register
.equ SP0BAUD, 0xFF88	// Serial port 0 baud rate divisor register
.equ SP0RD, 0xFF86	// Serial port 0 receive data register
.equ SP0TD, 0xFF84	// Serial port 0 transmit data register
.equ SP0STS, 0xFF82	// Serial port 0 status register
.equ SP0CT, 0xFF80	// Serial port 0 control register
.equ PDATA1, 0xFF7A	// PIO data 1 register
.equ PDIR1, 0xFF78	// PIO direction 1 register
.equ PIOMODE1, 0xFF76	// PIO mode 1 register
.equ PDATA0, 0xFF74	// PIO data 0 register
.equ PDIR0, 0xFF72	// PIO direction 0 register
.equ PIOMODE0, 0xFF70	// PIO mode 0 register
.equ T2CON, 0xFF66	// Timer 2 mode/control register
.equ T2CMPA, 0xFF62	// Timer 2 maxcount compare A register
.equ T2CNT, 0xFF60	// Timer 2 count register
.equ T1CON, 0xFF5E	// Timer 1 mode/control register
.equ T1CMPB, 0xFF5C	// Timer 1 maxcount compare B register
.equ T1CMPA, 0xFF5A	// Timer 1 maxcount compare A register
.equ T1CNT, 0xFF58	// Timer 1 count register
.equ T0CON, 0xFF56	// Timer 0 mode/control register
.equ T0CMPB, 0xFF54	// Timer 0 maxcount compare B register
.equ T0CMPA, 0xFF52	// Timer 0 maxcount compare A register
.equ T0CNT, 0xFF50	// Timer 0 count register
.equ SP0CON, 0xFF44	// Serial port 0 interrupt control register
.equ SP1CON, 0xFF42	// Serial port 1 interrupt control register
.equ INT4CON, 0xFF40	// INT4 control register
.equ INT3CON, 0xFF3E	// INT3 control register
.equ INT2CON, 0xFF3C	// INT2 control register
.equ INT1CON, 0xFF3A	// INT1 control register
.equ INT0CON, 0xFF38	// INT0 control register
.equ DMA1CON, 0xFF36	// DMA 1 interrupt control register/INT6
.equ DMA0CON, 0xFF34	// DMA 0 interrupt control register/INT5
.equ TCUCON, 0xFF32	// Timer interrupt control register
.equ INTSTS, 0xFF30	// Interrupt status register
.equ REQST, 0xFF2E	// Interrupt request register
.equ INSERV, 0xFF2C	// In-service register
.equ PRIMSK, 0xFF2A	// Priority mask register
.equ IMASK, 0xFF28	// Interrupt mask register
.equ POLLST, 0xFF26	// Poll status register
.equ POLL, 0xFF24	// Poll register
.equ EOI, 0xFF22	// End-of-interrupt register
.equ INTVEC, 0xFF20	// Interrupt vector register
.equ SP1BAUD, 0xFF18	// Serial port 1 baud rate divisor register
.equ SP1RD, 0xFF16	// Serial port 1 receive register
.equ SP1TD, 0xFF14	// Serial port 1 transmit register
.equ SP1STS, 0xFF12	// Serial port 1 status register
.equ SP1CT, 0xFF10	// Serial port 1 control register
.equ T2INTCON, 0xFF3A	// Timer 2 interrupt control register
.equ T1INTCON, 0xFF38	// Timer 1 interrupt control register
.equ INT6CON, 0xFF36	// INT6
.equ INT5CON, 0xFF34	// INT5
.equ T0INTCON, 0xFF32	// Timer 0 interrupt control register

#endif

#endif
