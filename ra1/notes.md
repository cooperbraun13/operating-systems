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