#ifndef UTILS_H_
#define UTILS_H_

#include "stdint.h"

uint32_t get_bits_31_22(uint32_t addr);

uint32_t get_bits_21_12(uint32_t addr);

uint32_t get_bits_11_0(uint32_t addr);

uint32_t get_bits_19_10(uint32_t page_number);

uint32_t get_bits_9_0(uint32_t page_number);

#endif
