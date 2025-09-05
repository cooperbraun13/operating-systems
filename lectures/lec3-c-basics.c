#include <stdio.h>

/* 
----------------------------------------------------------------------

Programming in C

----------------------------------------------------------------------
*/

int main() {
  printf("Hello, World!\n");
  return 0;
}

/*
----------------------------------------------------------------------

Compile and Run it

ls                    # list files in directory
gcc hello.c           # compile file
./a.out               # execute
gcc -o hello hello.c  # compile with custom output file name
./hello               # execute

----------------------------------------------------------------------
*/

/*
----------------------------------------------------------------------

Make and Makefile

target:
  * name of a file: hw.o
  * name of an action: clean

prerequisite:
  * a file used as input to create the target

command:
  * an action that make carries out

target: prerequisite1 prerequisite2 ...
  command1
  command2
  ....

hw: hw.o helper.o
  gcc -o hw hw.o helper.o -lm

hw.o: hw.c
  gcc -O -Wall -c hw.c

helper.o: helper.c
  gcc -O -Wall -c helper.c

clean:
  rm -rf hw.o helper.o hw

----------------------------------------------------------------------
*/

/*
----------------------------------------------------------------------

Declarations in C

declarations reserve memory space

local variables are unitialized
  * junk: whatever was there before

----------------------------------------------------------------------
*/

int main2() {
  int i ;    // 1435097815
  float f;   // 6.1734e-23
  char c;    // b
  return 0;
}

int main3() {
  int i ;    // 20
  float f;   // 6.1734e-23
  char c;    // b
  i = 20;
  return 0;
}

/*
----------------------------------------------------------------------

Printf

formatting instructions

* special characters
  * \n:  newline
  * \t:  tab
  * \b:  backspace
  * \":  double quote
  * \\:  backslash

* types of arguments
  * %d:  integers
  * %f:  floating-point numbers
  * %c:  characters

----------------------------------------------------------------------
*/

int main4() {
  int i;
  float f;
  char c;
  i = 34;
  c = 'a';
  printf("%d\n", i);
  printf("%d\t%c\n", i, c);
}

// 34
// 34  a

/*
----------------------------------------------------------------------

Scanf

allow users to input data

similar with cin in C++

----------------------------------------------------------------------
*/

int main5() {
  int x;
  scanf("%d", &x);
  return 0;
}

/*
----------------------------------------------------------------------

Data Types

int
  * integer: 16 bits or 32 bits (implementation dependent)

long
  * integer: either 32 bits or 64 bits, depending on the architecture

long long
  * integer: 64 bits

char
  * a single byte (8 bits)

float
  * single-precision floating point

double
  * double-precision floating point

----------------------------------------------------------------------
*/

/*
----------------------------------------------------------------------

Size of Data Types

sizeof
  * returns the size of a variable in bytes
  * very important function in C

----------------------------------------------------------------------
*/

int main6() {
  int i;
  printf("%zu\n", sizeof(i));
}

// 4 (because an integer is 32 bits)

/*
----------------------------------------------------------------------

Arrays in C

C: arrays = storage and indexing
  * no bound checking
  * no initialization

----------------------------------------------------------------------
*/

int main7() {
  int a[100];
  int i;
}

// variable | memory value
//    i     |
//    a[0]  |
//    a[1]  |
//    a[2]  |
//    ...   |
//    a[99] |
//    j     |      8

int main8() {
  int a[100];
  int i;
  for (i = 0; i < 100; i++) {
    a[i] = i;
  }
}

// variable | memory value
//    i     |      100
//    a[0]  |       0
//    a[1]  |       1
//    a[2]  |       2
//    ...   |
//    a[99] |       99


/*
----------------------------------------------------------------------

Functions

----------------------------------------------------------------------
*/

int fact(int i) {
  int k;
  int res;
  for (res = 1, k = 1; k <= i; k++) {
    res = res * k;
  }
  return res;
}

int main8() {
  printf("%d\n", fact(5));
  return 0;
}

// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

int fact(int i); // declares the function

int main9() {
  printf("%d\n", fact(5));
  return 0;
}

float fact(int i) {
  int k;
  int res;
  for (res = 1, k = 1; k <= i; k++) {
    res = res * k;
  }
  return res;
}

/*

* fact.h

int fact(int i );

* fact.c

#include "fact.h"

int main() {
  printf("%d\n", fact(5));
  return 0;
}

float fact(int i) {
  int k;
  int res;
  for (res = 0, k = 1; k <= i; k++) {
    res = res * k
  }
  return res;
}

*/

/*
----------------------------------------------------------------------

#include

standard header file:
  * #include <stdio.h>

your own header file
  * in the current directory

----------------------------------------------------------------------
*/

/*
----------------------------------------------------------------------

C Pointers

what is a C pointer?
  * a variable that holds an address

pointers in C are "typed"
  * pointer to an int
  * point to a char
  * point to a float
  * pointer to <whatever you can define>

----------------------------------------------------------------------
*/