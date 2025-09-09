#include <stdio.h>

/* 
1. what is printed for the value of j when the following program is run?
we continue to use the same drawing of memory as in the lecture. we assume j is allocated right below a[99],
and i is allocated right above a[0]
*/

int main() {
  int j = 8;
  int a[100];
  int i;
  for (i = 0; i <= 100; i++) {
    a[i] = i;
  }
  printf("%d\n", j);
}

/*
2. write a 'swap' function to swap two entries of an array
*/

void swap(int a[], int i, int j) {
  int temp = a[i];
  a[i] = a[j];
  a[j] = temp;
}

/*
3. write a 'selection sort' function to make an array sorted
*/

void selectionSort(int a[], int n) {
  int i, j, minIndex;

  // move boundary of unsorted array
  for (i = 0; i < n - 1; i++) {
    // find the minimum element in remaining unsorted array
    minIndex = i;
    for (j = i + 1; j < n; j++) {
      if (a[j] < a[minIndex]) {
        minIndex = j;
      }
    }

    // swap the found minimum element with the first element
    if (minIndex != i) {
      swap(a, i, minIndex);
    }
  }
}