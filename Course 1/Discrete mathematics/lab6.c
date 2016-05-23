#include "main.h"

void DFSL(int* arr, int n, int* cache, int* comp, int mode) {
  int i, t=0;
  for(i=0;i<n;i++) {
    cache[i] = 0;
    comp[i] = 0;
  }
  for(i=0;i<n;i++) {
    if(!cache[i])
      DFSRl(arr, n, i, &t, cache, comp, mode);
  }
}

void DFSRl(int* arr, int n, int i, int* t, int* cache, int* comp, int mode) {
  int c;
  cache[i] = 1;
  for(c=0;c<n;c++) {
    if(arr[i*n+c] && !cache[c])
      DFSRl(arr, n, c, t, cache, comp, mode);
  }
  (*t)++;
  comp[i] = *t;
  if(mode)
    printf("%c ",i+97);
}

void StronglyConnectedComponents(int* arr, int n) {
  int* tarr = (int*) malloc (sizeof(int) * (n*n+1));
  int cache[n];
  int comp[n];
  int trcomp[n];
  int i, c;
  for(i=0;i<n;i++) {
    cache[i] = 0;
    comp[i] = 0;
  }
  int t=0;
  transposing(arr, tarr, n);
  for(i=0;i<n;i++) {
    if(!cache[i]) {
      DFSRl(tarr, n, i, &t, cache, comp, false);
    }
  }
  //DFSL(arr, n, cache, comp);
  for(i=0;i<n;i++) {
    trcomp[i] = comp[i];
    //printf("%d ",trcomp[i]);
  }
  //printf("\n");
  //transposing(arr, tarr, n);
  //printarr(tarr, n, n);
  for(i=0;i<n;i++) {
    cache[i] = 0;
    comp[i] = 0;
  }
  t=0;
  for(i=0;i<n;i++) {
    for(c=0;c<n;c++) {
      if(trcomp[c] == n-i && !cache[c]) {
	DFSRl(arr, n, c, &t, cache, comp, true);
	printf("\n");
      }
    }
  }
  /*for(i=0;i<n;i++) {
    trcomp[i] = comp[i];
    printf("%d ",trcomp[i]);
    }*/
  //printf("\n");
}

void transposing(int* arr, int* tarr, int n) {
  int i, c;
  for(i=0;i<n;i++) {
    tarr[i*n+i] = arr[i*n+i];
    for(c=i+1;c<n;c++) {
      tarr[c*n+i] = arr[i*n+c];
      tarr[i*n+c] = arr[c*n+i];
    }
  }
}
