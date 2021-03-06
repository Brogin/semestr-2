#include "main.h"

void DFSR(int* arr, int* curr, int n, int m, int* cache, int* sort) {
  int c;
  cache[m/n] = 1;
  for(c=0;c<n;c++) {
    if(arr[m+c] && !cache[c]) {
      DFSR(arr, curr, n, c*n, cache, sort);
    }
  }
  sort[*curr-1] = m/n;
  //sort[m/n] = *curr;
  (*curr)--;
}  

void TopologicalSorting(int* arr, int n) {
  int cache[n];
  int sort[n];
  int i, curr = n;
  for(i = 0;i<n;i++) {
    cache[i] = 0;
    sort[i] = 0;
  }
  for(i = 0;i<n;i++) {
    if(!cache[i]) {
      DFSR(arr, &curr, n, i*n, cache, sort);
    }
  }
  for(i=0;i<n;i++) {
    printf("%c ", sort[i]+97);
  }
}
