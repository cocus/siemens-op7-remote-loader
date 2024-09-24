
#include <stdint.h>
#include "80c186es.h"
#include "serial.h"
#include "io.h"

char hex2num(char hex)
{
    if (hex >= 'A')
    {
        if (hex >= 'a')
            hex -= 'a' - 'A'; // tolower
        hex -= 'A' - '9' - 1; // todigit
    }
    return hex - '0'; // tohex
}

uint16_t readhex(int is_16)
{
    uint16_t hex = 0;
    for (uint8_t i = 0; i < (is_16 ? 4 : 2);)
    {
        while(cin_kbhit() == 0);
        char input = cin_buf();
        if (input == '\n')
            return hex;
        if (((input >= '0') && (input <= '9')) ||
            ((input >= 'A') && (input <= 'F')) ||
            ((input >= 'a') && (input <= 'f')))
        {
            uint8_t rd_hex = hex2num(input);
            hex <<= 4;
            hex |= rd_hex;
            i++;
        }
        else
        {
            continue;
        }
    }

    return hex;
}

void cmd_in_port(void)
{
    puts(" IN port? 0x");
    uint16_t port = readhex(1);
    serial_hexnum16(port);
    uint16_t rd = inw(port);
    puts(" = 0x");
    serial_hexnum16(rd);
}

void cmd_out_port(void)
{
    puts(" OUT port? 0x");
    uint16_t port = readhex(1);
    serial_hexnum16(port);
    puts(", what? 0x");

    uint16_t wr = readhex(1);
    serial_hexnum16(wr);

    outw(port, wr);
}

void cmd_pcbdump(void)
{
    uint16_t pcb = PCB_BASE;
    uint16_t cnt = 0;
    uint8_t i = 0;

    cout('\n');

    for (cnt = 0; cnt < 16; cnt++)
    {
        serial_hexnum16(pcb);
        puts(": ");
        for (i = 0; i < 8; i++)
        {
            serial_hexnum16(inw(pcb));
            cout(' ');

            pcb += 2;
        }
        cout('\n');
    }
}

void cmd_dump_mem(void)
{
    puts(" dump from seg? 0x");
    uint16_t from_seg = readhex(1);
    serial_hexnum16(from_seg);

    puts(", addr? 0x");
    uint16_t start_addr = readhex(1);
    serial_hexnum16(start_addr);

    puts(", sz? 0x");
    uint32_t sz1 = readhex(1);
    serial_hexnum16(sz1);
    sz1 <<= 16;
    uint32_t sz = readhex(1);
    serial_hexnum16(sz);

    sz += sz1;
    serial_hexdump(from_seg, start_addr, sz);
}

void cmd_dump_bin(void)
{
    puts(" dump from seg? 0x");
    uint16_t from_seg = readhex(1);
    serial_hexnum16(from_seg);

    puts(", addr? 0x");
    uint16_t start_addr = readhex(1);
    serial_hexnum16(start_addr);

    puts(", sz? 0x");
    uint32_t sz1 = readhex(1);
    serial_hexnum16(sz1);
    sz1 <<= 16;
    uint32_t sz = readhex(1);
    serial_hexnum16(sz);

    sz += sz1;

    uint8_t b;

    while (sz--)
    {
        b = readb(from_seg, start_addr);
        serial_hexnum8(b); cout(' ');
        inc_seg_addr_pair(from_seg, start_addr);
    }
}

void cmd_write(int is16)
{
    puts(" write to seg? 0x");
    uint16_t seg = readhex(1);
    serial_hexnum16(seg);

    puts(", addr? 0x");
    uint16_t addr = readhex(1);
    serial_hexnum16(addr);

    puts(", data? 0x");
    uint16_t data = readhex(is16);
    if (is16) {
        serial_hexnum8(data);
        writeb(seg, addr, data);
    } else {
        serial_hexnum16(data);
        writew(seg, addr, data);
    }
}

void terminal(void)
{
    puts("\n> ");
    while (cin_kbhit() == 0);
    char c = cin_buf();
    
    cout(c);

    switch(c)
    {
        case 'i':
        case 'I':
        {
            cmd_in_port();
            break;
        }

        case 'o':
        case 'O':
        {
            cmd_out_port();
            break;
        }

        case 'p':
        case 'P':
        {
            cmd_pcbdump();
            break;
        }

        case 'b':
        case 'B':
        {
            cmd_dump_bin();
            break;
        }

        case 'd':
        case 'D':
        {
            cmd_dump_mem();
            break;
        }

        case 'w':
        {
            cmd_write(0);
            break;
        }
        case 'W':
        {
            cmd_write(1);
            break;
        }

        case 'f':
        {
            writeb(0x4000, 0x5555, 0xaa);
            writeb(0x4000, 0x2aaa, 0x55);
            writeb(0x4000, 0x5555, 0x90);
            uint8_t id_low = readb(0x4000, 0x0000);

            writeb(0x4000, 0x5555, 0xaa);
            writeb(0x4000, 0x2aaa, 0x55);
            writeb(0x4000, 0x5555, 0x90);
            uint8_t id_high = readb(0x4000, 0x0001);

            puts(" ID low "); serial_hexnum8(id_low);
            puts(" ID high "); serial_hexnum8(id_high); /* doesn't work... TODO: use readw() */

            break;
        }

        default:
            puts(" unknown command!");
    }

}

void root(void)
{
    puts("\nOP7 loader built @ " BUILD_TIMESTAMP "!\n");

    uint16_t seg_reg;
    puts("CS   SS   DS   ES\n");
    asm ("mov %%cs, %0" : "=r"(seg_reg)); serial_hexnum16(seg_reg); cout(' ');
    asm ("mov %%ss, %0" : "=r"(seg_reg)); serial_hexnum16(seg_reg); cout(' ');
    asm ("mov %%ds, %0" : "=r"(seg_reg)); serial_hexnum16(seg_reg); cout(' ');
    asm ("mov %%es, %0" : "=r"(seg_reg)); serial_hexnum16(seg_reg); cout('\n');

    // all leds on
    outw(0x600, 0x0000);

    while (1)
    {
        terminal();
    }

    while(1) { } ;
}
