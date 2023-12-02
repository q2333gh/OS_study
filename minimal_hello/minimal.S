#include <sys/syscall.h>
/*
* can not use ; as comments in .S file of somewhere 
* this line above is pre processor handled. defination replacement 
* use  gcc -E minimal.S  to extend all the macros and definations in assembly file .
* TODO interesting :how to reverse this behaviour to get all syscall number ? maybe diff ISA have diff sycall.h ? 
* use for reverse-compile(binary-> high level languages :such as C ).
*
* the #include <sys/syscall.h> is define at c code with attribute : __ASSEMBLER__ to tell compiler that the macro is compatible with assembly file.
*/



.globl _start
_start:
;   movq $1, %rax
  movq $SYS_write, %rax   // write(
  movq $1,         %rdi   //   fd=1,
  movq $st,        %rsi   //   buf=st,
  movq $(ed - st), %rdx   //   count=ed-st
  syscall                 // );

;   movq $60, %rax
  movq $SYS_exit,  %rax   // exit(
  movq $1,         %rdi   //   status=1
  syscall                 // );

st:
  .ascii "\033[01;31mHello, OS World\033[0m\n"
ed:
