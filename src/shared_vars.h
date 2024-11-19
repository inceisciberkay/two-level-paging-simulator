#ifndef SHARED_VARS_H_
#define SHARED_VARS_H_

#include <stdint.h>
#include <stdio.h>

struct frame {
  uint32_t virtual_page_number;
  int count; // will be used by LRU policy
};
extern struct frame *frame_arr;

struct inner_table_entry {
  uint32_t frame_no;
  int valid_bit;
};
static const struct inner_table_entry DEFAULT_INNER_TABLE_ENTRY = {.valid_bit =
                                                                       0};

struct outer_table_entry {
  struct inner_table_entry *ptr_inner_table;
};
extern struct outer_table_entry outer_table[1024]; // indexed by p1

enum MODE { INFILE, RANDOM };
extern enum MODE mode;
extern int M;
extern int alg;

extern FILE *fptr_outfile;

// for FIFO
extern int earliest_created_frame;

// for LRU
extern int count_mem_access;

#endif
