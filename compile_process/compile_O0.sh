#!/bin/bash
# <!-- pro process -->
gcc -E add.c -o add.i

# <!-- compile -->
gcc  -O0 -S add.i -o add_O0.s
# -O0 dont do any optimization.


# <!-- assembler -->
gcc  -O0 -c add_O0.s -o add_O0.o  
# or: gcc -c hello.c 

# <!-- link -->
gcc  -O0 add_O0.o -o add_O0.out

# <!-- get address space from linakable file or executable -->
# <!-- executable will build a virtual linux address space  -->
objdump -d add_O0.o > add_O0.o.s
objdump -t add_O0.o > add_t_O0.o.s

objdump -d add_O0.out > add_O0.out.s
objdump -t add_O0.out > add_t_O0.out.s


