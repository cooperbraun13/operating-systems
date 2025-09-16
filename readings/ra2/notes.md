## 3.2 Program Encodings

**Compilation Flow**

When we compile C programs (e.g., `p1.c`, `p2.c`) with:
`gcc -Og -o p p1.c p2.c`
the compiler runs through several stages:
1. Preprocessor -> expands `#include` and macros
2. Compiler -> generates assembly files (`.s`)
3. Assembler -> translates assembly to object code (`.o`, machine instructions but with unresolved addresses)
4. Linker -> combines object files and libraries into an executable file (final runnable program)
* Object code = machine instructions without fixed addresses
* Executable code = fully linked binary with addresses filled in

**Machine-Level View**

* Controlled by the Instruction Set Architecture (ISA)
* Appears sequential (1 instruction at a time) but CPU executes many concurrently
* Works with virtual addresses (memory looks like one giant array of bytes)
* At this level:
  * Only bytes, registers, and instructions exist
  * No types (`long`, `int`, `pointer`), all treated as raw data
* Registers in x86-64:
  * `%rdi`, `%rsi`, `%rdx`, `%rcx`, `%r8`, `%r9` -> first 6 integer/pointer arguments
  * `%rax` -> function return value
  * `%rbx`, `%rbp`, `%r12-%r15` -> calle-saved (must be restored)

**Example: `multstore`**

```c
long mult2(long, long);

void multstore(long x, long y, long *dest) {
  long t = mult2(x, y);
  *dest = t;
}
```

Assembly (from `gcc -Og -s mstore.c`)

```asm
multstore:
  pushq %rbx
  movq  %rdx, %rbx
  call  mult2
  movq  %rax, (%rbx)
  popq  %rbx
  ret
```

**Step-by-Step Assembly Explanation**


**Object Code**


**Key Takeaways**


## 3.3 Data Formats



## 3.4 Accessing Information



## 3.5 Arithmetic and Logical Operations

