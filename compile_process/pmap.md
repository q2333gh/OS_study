 ```bash
 ./a.out &
 ps  
#  get  pid : xxx
  pmap 80842 > pmap.log
  kill 80842
  
#   this file store the map
  /proc/80842/maps

#!   or use gdb make the program trap into stop status and find the pid of that program.
 ```


 diff of  a running linux-user-program-address-space and a executable a.out file:

  The memory layout of a process includes **not only the code and data from the binary file**, but also any shared libraries the process is using, the process’s stack, and any memory the process has dynamically allocated. 


  a.out parse by objdump get: computation(logic) and data 

 Text segment: This is where the actual code of the program resides.  
Data segment: This is for global and static variables initialized by the programmer.  
BSS (Block Started by Symbol)segment: This holds uninitialized global and static variables.  
Heap: This is for dynamic memory allocation during the process runtime.  
Stack: This is used for local variables and for maintaining the function call-return structure.  

bss: . It’s a term that originated from an IBM assembler program, where it was used to reserve space for variables1. In the context of C programming and many other languages, the BSS segment is a portion of an object file or executable that contains statically allocated variables that are declared but have not been assigned a value yet1.


# Load the a.out into memory and run :
Q:so what kernel program can load a.out and run it in linux ?  
A:when type ./a.out in bash. the bash mainly call fork() and execve()
1.The shell parses the command line and identifies ./a.out as the command to be executed1.
2.The shell calls the fork() system function to create a new process2.
3.In the new child process, the shell calls the execve() system function, passing the path to the a.out file and any arguments2.
4.The execve() function is a system call, so control passes from the shell to the kernel2.
5.Inside the kernel, the program loader takes over3. The loader is part of the kernel and is responsible for loading the program into memory and starting its execution3.
6.The loader checks the file to make sure it’s a valid executable (for example, it might check the “magic number” at the start of the file)1.
7.The loader maps the sections of the executable file into memory. This includes the text segment (the machine code of the program), the data segment (initialized global and static variables), and the BSS segment (uninitialized global and static variables).
8.The loader also sets up the stack and the heap for the new process.
9.Once everything is set up, the loader transfers control to the entry point of the program, which is usually the main() function for C programs3.
10.The a.out program is now running. When it finishes, it will return control to the kernel, which will then clean up the process2.

the "loader" is mianly the syscall: fork() and execve() (execve is more complex and important) 
fork() gives a.out a bunch of regs.(maybe regard it as worker.)
execve gives a.out space to run . and store its code and data (maybe regard it as warehouse)
see exec impl of xv6-riscv 
/kernel/exec.c of int exec(char *path, char **argv)



the running program address-space become: 

The kernel code segment (__KERNEL_CS)   
The kernel data segment (__KERNEL_DS)  
  
and the a.out code ,data segment .

code include : text seg,stack(include part of current point of code and data )  
data include : data seg , heap , 

# modify a running process address space 
ref: https://jyywiki.cn/OS/2023/build/lect17.ipynb.html
```c
// 映射
void *mmap(void *addr, size_t length, int prot, int flags,
           int fd, off_t offset);
int munmap(void *addr, size_t length);

// 修改映射权限
int mprotect(void *addr, size_t length, int prot);
```




