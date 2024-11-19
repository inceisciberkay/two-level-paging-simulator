#include "file_addr_simulator.h"
#include "memory_accessor.h"
#include "shared_vars.h"

#include <stdint.h>
#include <stdio.h>

extern char *in1, *in2;

void read_addr_from_file_and_simulate() {
  FILE *fptr_infile2 = fopen(in2, "r");

  uint32_t query_address;
  while (fscanf(fptr_infile2, "%x", &query_address) != EOF) {
    FILE *fptr_infile1 = fopen(in1, "r");
    uint32_t start_address;
    uint32_t end_address;
    int in_range = 0;
    // checking if the query address falls into the region
    while (fscanf(fptr_infile1, "%x %x", &start_address, &end_address) != EOF) {
      if (query_address >= start_address && query_address < end_address) {
        in_range = 1;
        break;
      }
    }
    fclose(fptr_infile1);

    if (in_range) {
      access_address(query_address);
    } else {
      // virtual address does not belong to the address space of the process
      fprintf(fptr_outfile, "0x%08x e\n", query_address);
    }
  }
  fclose(fptr_infile2);
}
