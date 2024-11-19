#include "random_addr_simulator.h"
#include "memory_accessor.h"

#include <stdint.h>
#include <stdlib.h>
#include <time.h>

extern int addrcount;
extern uint32_t vmsize;

void randomly_generate_addr_and_simulate() {
  srand(time(NULL));

  while (addrcount--) {
    uint32_t random_address = rand() % vmsize;
    access_address(random_address);
  }
}
