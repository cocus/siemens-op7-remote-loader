# What is this?
This is a helper code used while reverse engineering the Siemens OP7 HMI panel.
Turns out that the official tool for programming these panels, Siemens ProTool, uploads an ia16 binary to the panel itself as part of it "programming" sequence.
Because there's NO signature checks, it's possible to upload arbitrary code to it while it's on "PROGRAM MODE".
This repository contains assembly initialization and C code which is built using the `ia16` GCC tolchain and produces a .bin file that can be upload to the OP7 panel using another tool that reproduces the ProTool protocol.

The aim of this code is to dump the main flash of the system, while also testing if the reverse-engineered schematic of the panel is okay or not.


# What can it do?
My unit was scrapped dued to the LCD failing out. Thus, no LCD-related things were tested, although an initialization sequence was obtained from the original firmware on the main flash.

Once the .bin is loaded through the ProTool protocol, a simple "terminal" runs on the same serial port, using the same baudrate (38400bps). Please have a look on `main.c` to figure out the actual commands.

In short, it can input and output words to the IO space, write bytes or words of data into memory space, dump memory regions in hex or hex+ascii.

This kills the OS running on the 80C186 by disabling interruptions and disabling the WDT.

# What does it look like when running?
This is a snippet of the loader being executed right after it being uploaded:
```
0 1 2 3 4 5 6 7 8 9 10 11 12 13 14 15 16 17 ProtocolSync:270: read 1 byte (aa), GetLastError = 0x0000
ProtocolSync:273: SYNCED!!!!
ProtocolWriteMemory:369: Writing from 10000, size 0800, offset is 0000
ProtocolWriteMemory:369: Writing from 10800, size 020c, offset is 0800
main:553: Received CRC d1f6, Calculated CRC d1f6
terminal output from payload:

OP7 loader built @ dom 22 sep 2024 17:01:36 -03!
CS   SS   DS   ES
1000 1000 1000 1000

> p
FF00: FFFF FFFF FFFF FFFF FFFF FFFF FFFF FFFF
FF10: 0061 0000 0020 0070 0026 0000 0000 0000
FF20: 0000 80FF 0000 0000 07FD 0007 0000 0000
FF30: 0000 000F 000F 000F 000F 000F 000F 000F
FF40: 000F 0018 001F 80FF 80FF 80FF 80FF 80FF
FF50: 0000 0000 DFFF 0020 FFFF FDFF FFFF 2000
FF60: 0000 FFFF FFFF 0020 0020 0020 0020 0020
FF70: BC43 0000 D84E 6718 C020 B467 0000 0000
FF80: 0000 0000 0000 0000 0000 0000 0000 0000
FF90: FFFF FFFF FFFF FFFF FFFF FFFF FFFF FFFF
FFA0: 80BB 1FB8 0070 41F8 A0B8 FFFF FFFF FFFF
FFB0: FFFF FFFF FFFF FFFF FFFF FFFF FFFF FFFF
FFC0: 0000 FFF0 0000 FFF0 0000 FFF9 0000 0000
FFD0: 0000 FFF0 0000 FFF0 0000 FFF9 0000 0000
FFE0: 0000 0000 0000 4000 0000 0000 0000 0000
FFF0: 6000 0007 1100 FFFF 0000 0000 0000 20FF

> i IN port? 0x0600 = 0xFFFF
> i IN port? 0x0600 = 0xEFEF
> o OUT port? 0x0600, what? 0xFFFF
> o OUT port? 0x0600, what? 0x0000
>
```


# Additional information about the system

## Memory map and GPIO map
TBD.
* IO 0x600 write -> LEDs
* IO 0x600 read -> keyboard matrix input
* IO 0x0 r/w -> LCD
* IO 0x20 r/w -> LCD but with its pin #4 ON
* MEM 0-0x20000: RAM
* MEM 0x40000-0x5FFFF: User-code `Am29F010`
* MEM 0x80000-0xFFFFF: Main firmware FLASH (16 bits of data)

## PCB values
Dump of the PCB values right after starting the loader (which modifies some of these):
```
       0 1  2 3  4 5  6 7  8 9  A B  C D  E F
FF00: FFFF FFFF FFFF FFFF FFFF FFFF FFFF FFFF
FF10: 0061 0000 0020 0070 0026 0000 0000 0000
FF20: 0000 80FF 0000 0000 07FD 0007 0000 0000
FF30: 0000 000F 000F 000F 000F 000F 000F 000F
FF40: 000F 0018 001F 80FF 80FF 80FF 80FF 80FF
FF50: 0000 0000 5FF2 0020 0800 1FFE FFFF 2004
FF60: 0200 AFD6 FFFF 0020 0200 0200 0200 0200
FF70: BC43 0000 D84E 6718 C020 B467 0000 0000
FF80: 0000 0000 0000 0000 0000 0000 0000 0000
FF90: FFFF FFFF FFFF FFFF FFFF FFFF FFFF FFFF
FFA0: 80BB 1FB8 0070 41F8 A0B8 FFFF FFFF FFFF
FFB0: FFFF FFFF FFFF FFFF FFFF FFFF FFFF FFFF
FFC0: 002A FFF0 0048 FFF0 0008 BFF9 0008 0008
FFD0: 0000 FFF0 0040 FFF0 0028 FFF9 0028 0028
FFE0: 0000 0000 0000 0000 0000 0000 0000 0000
FFF0: 6000 0007 1100 FFFF 0000 0000 0000 20FF
```

## F2: AUXCON = 0007

`IOSIZ`: IO 8-bit accesses are performed

`MSIZ`: MIDRANGE 8-bit accesses are performed

`LSIZ`: LCS 8-bit accesses are performed

`RTS0`: configured as RTR0

`ENRX0`: CTS0 pin is CTS0

`RTS1`: RTS1 pin is RTR1

`ENRX1`: CTS1 pin works as CTS1

## F0: SYSCON = 6000
```
PSEN MCSBIT DSDEN PWD CBF CBD CAF CAD       F2 F1 F0
0    1      1     0   0   0   0   0   00000 0  0  0
```

`PSEN`: no power save

`MCSBIT`: MCS0 is active over the entire MCS range

`DSDEN`: data strobe bus mode is enabled, and the DS timing for reads and writes is identical to the normal read cycle DEN timing

`PWD`: no pulse width demodulation

`CBF`: no CLKOUTB output frequency enabled

`CBD`: CLKOUTB is driven as an output

`CAF`: CLKOUTA follows the internal processor frequency (after the clock divisor). 

`CAD`: CLKOUTA is driven as an output

`F2-F0`: division factor 0 for power save mode

## GPIO registers

### 70: PIOMODE0 = BC43

	bit 15: MCS1 = PIO
	bit 13: DRQ1/INT6 = PIO
	bit 12: DRQ0/INT5 = PIO
	bit 11: TMRIN0 = PIO
	bit 10: TMROUT0 = PIO
	bit 06: SRDY = PIO
	bit 01: TMROUT1 = PIO
	bit 00: TMRIN1 = PIO

### 72: PDIR0 = 0000 
All PIOs are set as outputs

### 74: PDATA0 = D84E
Reading the original flash code, it was initially set as 0x004a by the FW.

	bit 15: MCS1 = PIO = 1
	bit 13: DRQ1/INT6 = PIO = 0
	bit 12: DRQ0/INT5 = PIO = 1
	bit 11: TMRIN0 = PIO = 1
	bit 10: TMROUT0 = PIO = 0
	bit 06: SRDY = PIO = 1
	bit 01: TMROUT1 = PIO = 1
	bit 00: TMRIN1 = PIO = 0

### 76: PIOMODE1 = 6718
	30: INT4 = PIO
	29: S6/LOCK = PIO
	26: UZI = PIO
	25: MCS3 = PIO
	24: MCS2 = PIO
	20: RTS0 = PIO
	19: PCS3/RTS1 = PIO

### 78: PDIR1 = C020
	INT2/INTA0/PWD = input (no need?)
	30: INT4 = input
	20: RTS0 = input

### 7A: PDATA1 = B467
TBD. 1011010001100111

## Memory and IO chip select registers

### A4: PACS = 0070
```
BA19-BA11     R3 R2 R1-R0
000000000 111 0  0  00
```
`BA19-BA11`: When the PCS chip selects are mapped to I/O space, BA19–16 must be programmed to 0000b because the I/O address bus is only 16-bits wide.

`R3`: wait states in R1-R0 (0 wait states)

`R2`: PCS3-PCS0 external ready required

`R1-R0`: 0 wait states

| PCS	| Range Low			| Range High |
|-------|-------------------|------------|
| PCS0	| Base Address		| Base Address+255 |
| PCS1	| Base Address+0x100	| Base Address+511 |
| PCS2	| Base Address+0x200	| Base Address+767 |
| PCS3	| Base Address+0x300	| Base Address+1023 |
| PCS5	| Base Address+0x500	| Base Address+1535 |
| PCS6	| Base Address+0x600	| Base Address+0x6FF |

### A6: MMCS = 41F8
```
BA19-BA13        R2 R1-R0
0100000   111111 0  00
```

`BA19-BA11`: 0x40 -> Memory chip selects range starts at 0x40000

The only peripheral connected to `/MCS0` is the "user code" (because this is where the actual HMI config is stored) `Am29F010` flash, which can be read at 0x40000 until 0x5ffff.

### A8: MPCS = A0B8 
```
  M6-M0   EX MS     R2 R1-R0
1 0100000 1  0  111 0  00
```

`M6-M0`: Total Block Size = 256K, Individual Select Size = 64K

`EX`: PCS6/PCS5 are peripheral chip selects

`MS`: PCS outputs active with BUS cycles

`R2`: PCS6/PCS5 external ready is required

`R1-R0`: PCS6/PCS5 0 wait states PCS access
