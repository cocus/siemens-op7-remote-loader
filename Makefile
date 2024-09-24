# Based off SYS86 project (https://github.oom/mfld-fr/sys86)

CC = ia16-elf-gcc
AS = ia16-elf-as
LD = ia16-elf-ld

BUILDSTAMP = $(shell date)
DEFINES += -DBUILD_TIMESTAMP='"$(BUILDSTAMP)"'

CFLAGS = -ffunction-sections -Werror -ffreestanding -O1 -std=gnu99 -mtune=i80186 -march=i80186 $(DEFINES)
ASFLAGS = -ffreestanding -O1 -std=gnu99 -nostdinc -mtune=i80186 -march=i80186 $(DEFINES)
LDFLAGS = -nostdlib -T opldr.ld

EXE = op7.bin

OBJS = \
	opldr.o \
	main.o \
	serial.o \
	udivsi3.o \
	divsi3.o \
	ia16-ldivmodu.o \
	ia16-ldivmods.o \
	c-helpers.o \
	# end of list

.PHONY : all clean

all: $(EXE)

$(EXE): $(OBJS)
	$(LD) $(LDFLAGS) -M -o $(EXE) $(OBJS) > $(EXE).map

clean:
	rm -f $(EXE) $(OBJS) $(EXE).map
