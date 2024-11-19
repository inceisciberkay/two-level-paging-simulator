#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "file_addr_simulator.h"
#include "random_addr_simulator.h"
#include "shared_vars.h"

enum MODE mode;

// mandatory parameters
char *out;
int M;
int alg;

// optional parameters
char *in1, *in2;
uint32_t vmsize;
int addrcount;

void read_args(int argc, char **argv) {
  if (argc == 7) {
    mode = INFILE;
    in1 = argv[1];
    in2 = argv[2];
    M = atoi(argv[3]);
    out = argv[4];
    alg = atoi(argv[6]);
  } else if (argc == 9) {
    mode = RANDOM;
    M = atoi(argv[1]);
    out = argv[2];
    alg = atoi(argv[4]);
    vmsize = strtol(argv[6], NULL, 16);
    addrcount = atoi(argv[8]);
  } else {
    fprintf(stderr, "invalid number of arguments\n");
    exit(1);
  }
}

struct frame *frame_arr;
struct outer_table_entry outer_table[1024]; // indexed by p1
FILE *fptr_outfile;

void simulate() {
  // initializations
  fptr_outfile = fopen(out, "w");

  // frame_arr is used to keep information about the relationships between
  // virtual page numbers and corresponding frame numbers
  frame_arr = malloc(M * sizeof(struct frame));

  // initially, outer table entries should be null (there is no inner table)
  for (int i = 0; i < 1024; i++) {
    outer_table[i].ptr_inner_table = NULL;
  }

  // simulation
  if (mode == INFILE) {
    read_addr_from_file_and_simulate();
  } else { // mode == RANDOM
    randomly_generate_addr_and_simulate();
  }

  // freeing used memory
  for (int i = 0; i < 1024; i++) {
    if (outer_table[i].ptr_inner_table != NULL) {
      free(outer_table[i].ptr_inner_table);
    }
  }
  free(frame_arr);

  fclose(fptr_outfile);
}

int main(int argc, char *argv[]) {
  read_args(argc, argv);
  simulate();

  return 0;
}
