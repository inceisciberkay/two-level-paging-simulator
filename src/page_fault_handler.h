#ifndef PAGE_FAULT_HANDLER_H_
#define PAGE_FAULT_HANDLER_H_

#include "stdint.h"

void handle_page_fault(uint32_t p1, uint32_t p2);

#endif
