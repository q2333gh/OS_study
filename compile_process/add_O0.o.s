
add_O0.o:     file format elf64-x86-64


Disassembly of section .text:

0000000000000000 <plus>:
   0:	f3 0f 1e fa          	endbr64 
   4:	55                   	push   %rbp
   5:	48 89 e5             	mov    %rsp,%rbp
   8:	89 7d ec             	mov    %edi,-0x14(%rbp)
   b:	89 75 e8             	mov    %esi,-0x18(%rbp)
   e:	8b 55 ec             	mov    -0x14(%rbp),%edx
  11:	8b 45 e8             	mov    -0x18(%rbp),%eax
  14:	01 d0                	add    %edx,%eax
  16:	89 45 fc             	mov    %eax,-0x4(%rbp)
  19:	8b 45 fc             	mov    -0x4(%rbp),%eax
  1c:	5d                   	pop    %rbp
  1d:	c3                   	ret    

000000000000001e <main>:
  1e:	f3 0f 1e fa          	endbr64 
  22:	55                   	push   %rbp
  23:	48 89 e5             	mov    %rsp,%rbp
  26:	48 83 ec 10          	sub    $0x10,%rsp
  2a:	c7 45 f4 04 00 00 00 	movl   $0x4,-0xc(%rbp)
  31:	c7 45 f8 08 00 00 00 	movl   $0x8,-0x8(%rbp)
  38:	8b 55 f8             	mov    -0x8(%rbp),%edx
  3b:	8b 45 f4             	mov    -0xc(%rbp),%eax
  3e:	89 d6                	mov    %edx,%esi
  40:	89 c7                	mov    %eax,%edi
  42:	e8 00 00 00 00       	call   47 <main+0x29>
  47:	89 45 fc             	mov    %eax,-0x4(%rbp)
  4a:	8b 45 fc             	mov    -0x4(%rbp),%eax
  4d:	89 c6                	mov    %eax,%esi
  4f:	48 8d 05 00 00 00 00 	lea    0x0(%rip),%rax        # 56 <main+0x38>
  56:	48 89 c7             	mov    %rax,%rdi
  59:	b8 00 00 00 00       	mov    $0x0,%eax
  5e:	e8 00 00 00 00       	call   63 <main+0x45>
  63:	b8 00 00 00 00       	mov    $0x0,%eax
  68:	c9                   	leave  
  69:	c3                   	ret    
