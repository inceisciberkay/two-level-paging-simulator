#include "utils.h"

inline uint32_t get_bits_31_22(uint32_t addr) { return addr >> 22; }

inline uint32_t get_bits_21_12(uint32_t addr) { return (addr << 10) >> 22; }

inline uint32_t get_bits_11_0(uint32_t addr) { return (addr << 20) >> 20; }

inline uint32_t get_bits_19_10(uint32_t page_number) {
  return page_number >> 10;
}

inline uint32_t get_bits_9_0(uint32_t page_number) {
  return (page_number << 22) >> 22;
}
