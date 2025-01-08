**Running the program:**<br>
``` $ pagesim <in1> <in2> <M> <out> -a <alg> [-r <vmssize> -n <addrcount>]```

* \<in1> is the input file that indicates the used virtual regions of the process. Each line in the file specifies a range [X, Y), where X is the start- address and Y is end-address+1.
* \<in2> is the input file containing virtual addresses that process is referencing.
* \<out> is the output file.
* \<M> is the number of frames that the process can use.
* –a \<alg> parameter indicates the algorithm to use for page replacement: -a 1 indicates LRU, -a 2 indicates FIFO.
* The -r parameter is optional. When –r is specified, the program will not use \<in1> input file but will use a single virtual memory region of size \<vmsize> starting at virtual address 0 (in bytes and as a hexadecimal number) and virtual addresses will be generated randomly according to a random distribution instead of taking them from input file \<in2>. Hence when –r is specified, \<in1> and \<in2> are not specified.
* The -n option is used to specify the number of random addresses (\<addrcount>) that will be generated.

The virtual memory layout of the process should be specified in an input file as follows:
> 0x00000000 0x00010000<br>
> 0x00100000 0x001a0000<br>
> 0x10000000 0x10c00000

Another input file should include a set of virtual addresses that the program is referencing:
> 0x00000000<br>
> 0xd3a01000<br>
> 0x00000010<br>
> 0x00000011<br>
> 0x10000d00<br>
> 0x10000d00<br>
> 0x10000c20

Output file contains a list of physical addresses corresponding to the virtual addresses in the input file. For each virtual/physical address if a reference caused a page fault or not is indicated with an “x” sign. If a virtual address given in <in2> is not falling into one of the ranges of given in <in1>, then the address is indicated with “e” mark (“e” means unused memory access exception):
> 0x00000000 x<br>
> 0xd3a01000 e<br>

* The process is given a number of frames for its use. When all the frames are filled up, page replacement takes place. For that one of the two algorithms are used (1-LRU or 2-FIFO).
* Two level paging address split scheme: [10, 10, 12].
* Virtual addresses and physical addresses are 32 bits long.
* When a page fault occurs, if there is free frame, the frame with smallest number is selected; otherwise a victim page (hence the corresponding victim frame) is chosen according to page replacement algorithm.
