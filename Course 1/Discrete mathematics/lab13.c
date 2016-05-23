#include "main.h"

void Prim(int* arr, int* w, int n) {
  int i, c, f, t=0, s, l, mw;
  int X[n];
  for(i=0;i<n;i++) {
    X[i] = 0;
  }
  f = 1;
  f = f - 1;
  X[f] = 1;
  while(t!=n-1) {
    mw = n*n;
    for(i=0;i<n;i++) {
      if(X[i]) {
	for(c=0;c<n;c++) {
	  if(!X[c] && arr[i*n+c] && mw>w[i*n+c]) {
	    mw = w[i*n+c];
	    s = c;
	    f = i;
	    l = c;
	  }
	}
      }
    }
    printf(" %d-%d ", f+1, l+1);
    X[l] = 1;
    t++;
  }
  
}
