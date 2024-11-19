#include "memory_accessor.h"
#include "page_fault_handler.h"
#include "shared_vars.h"
#include "utils.h"

#include <stdint.h>
#include <stdlib.h>

void access_address(uint32_t addr) {
  count_mem_access++; // for LRU

  // splitting address
  uint32_t p1 = get_bits_31_22(addr);
  uint32_t p2 = get_bits_21_12(addr);
  uint32_t d = get_bits_11_0(addr);

  if (outer_table[p1].ptr_inner_table != NULL) {
    if (outer_table[p1].ptr_inner_table[p2].valid_bit == 1) {
      // frame is found
      uint32_t frame_no = outer_table[p1].ptr_inner_table[p2].frame_no;

      // update frame info for LRU
      frame_arr[frame_no].count = count_mem_access;

      // print physical address
      uint32_t physical_address = ((frame_no) << 12) | d;
      if (mode == INFILE) {
        fprintf(fptr_outfile, "0x%08x\n", physical_address);
      } else { // mode == RANDOM
        fprintf(fptr_outfile, "0x%08x 0x%08x\n", addr, physical_address);
      }
    } else { // inner page fault
      handle_page_fault(p1, p2);

      // print physical address
      uint32_t physical_address =
          ((outer_table[p1].ptr_inner_table[p2].frame_no) << 12) | d;
      if (mode == INFILE) {
        fprintf(fptr_outfile, "0x%08x x\n", physical_address);
      } else { // mode == RANDOM
        fprintf(fptr_outfile, "0x%08x 0x%08x x\n", addr, physical_address);
      }
    }

  } else { // page fault, outer table does not point to any inner table
    // create inner table
    outer_table[p1].ptr_inner_table =
        malloc(1024 * sizeof(struct inner_table_entry));
    for (int i = 0; i < 1024; i++) {
      outer_table[p1].ptr_inner_table[i] = DEFAULT_INNER_TABLE_ENTRY;
    }

    handle_page_fault(p1, p2);

    // print physical address
    uint32_t physical_address =
        ((outer_table[p1].ptr_inner_table[p2].frame_no) << 12) | d;

    if (mode == INFILE) {
      fprintf(fptr_outfile, "0x%08x x\n", physical_address);
    } else { // mode == RANDOM
      fprintf(fptr_outfile, "0x%08x 0x%08x x\n", addr, physical_address);
    }
  }
}
