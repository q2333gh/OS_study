#!/bin/bash

# <!-- pro process -->
gcc -E add.c -o add.i

# <!-- compile -->
gcc -O3 -S add.i -o add_O3.s

# -O3 do the most aggressive optimization.
# <!-- assembler -->
gcc -O3 -c add_O3.s -o add_O3.o

# <!-- link -->
gcc -O3 add_O3.o -o add_O3.out

# <!-- get address space from linakable file or executable -->
# <!-- executable will build a virtual linux address space -->
objdump -d add_O3.o > add_O3.o.s 
objdump -t add_O3.o > add_t_O3.o.s

objdump -d add_O3.out > add_O3.out.s 
objdump -t add_O3.out > add_t_O3.out.s