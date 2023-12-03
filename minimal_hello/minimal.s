# 0 "minimal.S"
# 0 "<built-in>"
# 0 "<command-line>"
# 1 "/usr/include/stdc-predef.h" 1 3 4
# 0 "<command-line>" 2
# 1 "minimal.S"

# 1 "/usr/include/x86_64-linux-gnu/sys/syscall.h" 1 3 4
# 24 "/usr/include/x86_64-linux-gnu/sys/syscall.h" 3 4
# 1 "/usr/include/x86_64-linux-gnu/asm/unistd.h" 1 3 4
# 20 "/usr/include/x86_64-linux-gnu/asm/unistd.h" 3 4
# 1 "/usr/include/x86_64-linux-gnu/asm/unistd_64.h" 1 3 4
# 21 "/usr/include/x86_64-linux-gnu/asm/unistd.h" 2 3 4
# 25 "/usr/include/x86_64-linux-gnu/sys/syscall.h" 2 3 4




# 1 "/usr/include/x86_64-linux-gnu/bits/syscall.h" 1 3 4
# 30 "/usr/include/x86_64-linux-gnu/sys/syscall.h" 2 3 4
# 3 "minimal.S" 2


;
;can not use ; as comments in .S file of somewhere
;this line above is pre processor handled. defination replacement
;use gcc -E minimal.S to extend all the macros and definations in assembly file .
;TODO interesting :how to reverse this behaviour to get all syscall number ? maybe diff ISA have diff sycall.h ?
;use for reverse-compile(binary-> high level languages :such as C ).
;
;the #include <sys/syscall.h> is define at c code with attribute : 1 to tell compiler that the macro is compatible with assembly file.
;
;

.globl _start
_start:
; movq $1, %rax
  movq $1, %rax
  movq $1, %rdi
  movq $st, %rsi
  movq $(ed - st), %rdx
  syscall

; movq $60, %rax
  movq $60, %rax
  movq $1, %rdi
  syscall

st:
  .ascii "\033[01;31mHello, OS World\033[0m\n"
ed:

;
;\033[01;31m ANSI escape sequences that are used to control
;
;`Hello, OS World` to hex:
;48 65 6C 6C 6F 2C 20 4F 53 20 57 6F 72 6C 64 20
;
