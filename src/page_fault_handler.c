#include "page_fault_handler.h"
#include "shared_vars.h"
#include "utils.h"

int used_frame_count = 0;
// for FIFO
int earliest_created_frame = 0;
// for LRU
int count_mem_access = 0;

void handle_page_fault(uint32_t p1, uint32_t p2) {
  // check if there is a free frame
  if (used_frame_count < M) {
    // save frame into the frame array to use later for page replacement
    frame_arr[used_frame_count] = (struct frame){
        .virtual_page_number = p1 << 10 | p2, .count = count_mem_access};

    // use free frame with the smallest number
    outer_table[p1].ptr_inner_table[p2].frame_no = used_frame_count;
    // set valid bit to 1
    outer_table[p1].ptr_inner_table[p2].valid_bit = 1;

    used_frame_count++;
  } else {
    // perform page replacement
    uint32_t victim_frame;
    uint32_t victim_page_number;

    if (alg == 1) { // alg == LRU
      int min = frame_arr[0].count;
      victim_page_number = frame_arr[0].virtual_page_number;
      victim_frame = 0;

      // find least recently used frame and page number
      // count of a frame number is updated whenever it is accessed
      // therefore the frame number with the smallest count should be replaced
      for (int i = 1; i < M; i++) {
        if (frame_arr[i].count < min) {
          min = frame_arr[i].count;
          victim_page_number = frame_arr[i].virtual_page_number;
          victim_frame = i;
        }
      }
    } else { // alg == FIFO
      victim_frame = earliest_created_frame;
      victim_page_number = frame_arr[victim_frame].virtual_page_number;

      // when the number of free pages becomes equal to 0, earliest created
      // frame is 0 (since 0. frame is created at first). As page replacement is
      // performed, earliest created frame is incremented. its value is between
      // 0 and M-1
      earliest_created_frame = (earliest_created_frame + 1) % M;
    }
    uint32_t p1_victim_page_number = get_bits_19_10(victim_page_number);
    uint32_t p2_victim_page_number = get_bits_9_0(victim_page_number);

    // set valid bit of victim page to 0
    outer_table[p1_victim_page_number]
        .ptr_inner_table[p2_victim_page_number]
        .valid_bit = 0;

    // replace victim frame with the new frame
    frame_arr[victim_frame] = (struct frame){
        .virtual_page_number = p1 << 10 | p2, .count = count_mem_access};

    // use victim frame for the frame number of newly created page
    outer_table[p1].ptr_inner_table[p2].frame_no = victim_frame;
    // set valid bit of new page to 1
    outer_table[p1].ptr_inner_table[p2].valid_bit = 1;
  }
}
