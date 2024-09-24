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
