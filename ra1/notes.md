## A Simple C Program

* Headers: `#include` inserts standard libraries (e.g., stdio.h) so functions like `printf` are available
* Main function: Every C program starts with main(), which returns an integer exit code and can take command-line arguments (`argc`, `argv`)
* Program output: `printf` writes formatted text to standard output; special characters like `\n` control formatting
* Exit status: `return 0;` signals successful completion to the operating system

## Compilation and Execution

* gcc (compiler driver) -> coordinates the process
* cpp (preprocessor) -> handles `#include`, `#define`; outputs C source
* cc1 (compiler) -> converts C source -> assembly code
* as (assembler) -> turns assembly -> object code (machine-readable)
* ld (linker) -> links object code into final executable (`a.out` by default)
* Run -> `a.out`; OS sets up `argc` and `argv` for the program

## Useful Flags

* `gcc -o hw hw.c` # `-o`: to specify the executable name
* `gcc -Wall hw.c` # `-Wall`: gives much better warnings
* `gcc -g hw.c`    # `-g`: to enable debugging with gdb
* `gcc -O hw.c`    # `-O`: to turn on optimization
* Of these flags, always use `-Wall` which gives us lots of extra warnings about possible mistakes

## Linking with Libraries

* Standard libraries: Most functions are available by default through the C library; just `#include` the correct header (check via `man pages`)
* System calls: Functions like `fork()` are wrapped in the C library (e.g., `#include <unistd.h>`)
* Non-default libraries: Some, like the math library, require both an `#include` (e.g., `<math.h>`) and a link flag (e.g., `-lm`)
* Static vs dynamic linking:
  * Static (`.a`) -> code copied into the executable (larger binary)
  * Dynamic (`.so`) -> linked at runtime (smaller, shared across programs, preferred)
* Linker flags:
  * `-lXXX` -> link with `libXXX.so` or `libXXX.a`
  * `-I<path>` -> add custom header search path
  * `-L<path>` -> add custom library search path

## Seperate Compilation

* Splitting code: Large problems can be divided into multiple source files (e.g., `hw.c`, `helper.c`)
* Compile step (`-c`): `gcc -c file.c` produces object files (`.o`), not executables
* Link step: Combine object files with `gcc -o prog file1.o file2.o ...`; this invokes the linker to produce a final executable
* Flags:
  * `-Wall`, `-O` -> used during compilation for warnings/optimization
  * `-lXXX` -> specified only at the linking stages for libraries
* Efficiency: Compiling programs seperately saves time, only changed files need recompiling instead of recompiling/rebuilding the whole program
* Automation: Tools like `make` manage dependencies and recompilation

## Makefiles

* Purpose: `make` automates building programs by recompiling only what has changed, saving time on large projects
* Rules structure:
  * Target -> the file/action to build (e.g., `hw`, `clean`)
  * Prerequisites -> the files the target depends on (e.g., `.c` -> `.o`)
  * Commands -> shell commands to build/update the target (must start with a tab, not spaces)
* Dependency checking: `make` rebuilds targets only if prerequisites are newer or missing
* Special targets: `clean` removes build artifacts (rm -f ...) to force a fresh build
* Variables and shortcuts: Variables (`SRCS`, `TARG`, `CC`, etc.) make makefiles flexible and easier to maintain. Pattern rules (`%.o: %.c`) automate compilation steps
* Advanced tools: `makedepend` can automatically determine file dependencies for larger projects