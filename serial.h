#pragma once

#include <stdint.h>

#define cin_stat() inb(SP1STS)
#define cin_kbhit() (inb(SP1STS) & 128)
#define cin_buf() inb(SP1RD)

void serial_init(void);

void cout(char c);

void puts(char * str);

void serial_hexnum4(uint8_t n);

void serial_hexnum8(uint8_t n);

void serial_hexnum16(uint16_t n);

void serial_hexnum32(uint32_t n);

void serial_decimal(int32_t i);

void serial_hexdump(uint16_t dseg, uint16_t daddr, uint32_t cnt);
