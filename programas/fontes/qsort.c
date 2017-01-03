/// MC548 - PROJETO E ANALISE DE ALGORITMOS II - 1s2010
/// Prof. Flavio Keidi Miyazawa
/// ---------------------------------------------------------------
/// PROJETO PRATICO: PROBLEMA DA MOCHILA COM RESTRICOES DE CONFLITO
/// Haraldo Sergio A. Pereira Filho (003059)


#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "qsort.h"

void quickSort(int vec[], int left, int right, float* w) {
  int r;

  if (right > left) {
    r = partition(vec, left, right, w);
    quickSort(vec, left, r - 1, w);
    quickSort(vec, r + 1, right, w);
  }
}

int partition(int vec[], int left, int right, float* w) {
  int i, j;

  i = left;
  for (j = left + 1; j <= right; ++j) {
    if (w[vec[j]] > w[vec[left]]) {
      ++i;
      swap(&vec[i], &vec[j]);
    }
  }
  swap(&vec[left], &vec[i]);

  return i;
}

void swap(int* a, int* b) {
  int tmp;
  tmp = *a;
  *a = *b;
  *b = tmp;
}
