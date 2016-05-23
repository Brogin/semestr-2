#include "main.h"

void Dijkstra(int* adjarr, int* warr, int n, int f, int l) {
  int x, i, c=0, swap = n*n, num;
  int M[n];
  int T[n];
  int L[n];
  int R[n];  
  if(f == l) {
    //printf("length from %d to %d = 0\n",f,l);
    return;
  }
  x = f - 1;
  for(i=0;i<n;i++) {
    R[i] = 0;
    if(i == x) {
      M[i] = 0;
      T[i] = 0;
      L[i] = 0;
    } else {
      M[i] = n*n;
      T[i] = 1;
      L[i] = n*n;
    }
  }  
  while(true) {
    swap = n*n;
    for(i=0;i<n;i++) {
      if(adjarr[n*x+i] && T[i]) {
	if(L[i] > (M[x]+warr[n*x+i]))
	  R[i] = x+1;
	L[i] = MIN(L[i], M[x]+warr[n*x+i]);
      }
    }
    for(i=0;i<n;i++) {
      if(T[i] && swap > L[i]) {
	swap = L[i];
	num = i;
      }
    }
    M[num] = swap;
    T[num] = 0;
    x = num;
    if(x == l-1)
      break;
    }
  printf("length from %d to %d = %d\n",f,l,M[l-1]);
  int line = 1;
  int e = l - 1;
  int W[n];
  while(e+1 != f) {
    W[line] = R[e];
    e = W[line]-1;
    line++;
  }
  W[0] = l;
  for(--line;line>=0;line--)
    printf("%c ",W[line]+96);
  printf("\n");
  //while()
  /*for(i=0;i<n;i++) {
    printf("%5.c ", i+97);
  }
  printf("\n");
  for(i=0;i<n;i++) {
    printf("%5.d ", L[i]);
  }
  printf("\n");
  for(i=0;i<n;i++) {
  printf("%5.c ", R[i]+96);
  }*/
}

int Dijkstraint(int* adjarr, int* warr, int n, int f, int l) {
  int x, i, c=0, swap = n*n, num;
  int M[n];
  int T[n];
  int L[n];
  int R[n];  
  if(f == l) {
    //printf("length from %d to %d = 0\n",f,l);
    return;
  }
  x = f - 1;
  for(i=0;i<n;i++) {
    R[i] = 0;
    if(i == x) {
      M[i] = 0;
      T[i] = 0;
      L[i] = 0;
    } else {
      M[i] = n*n;
      T[i] = 1;
      L[i] = n*n;
    }
  }  
  while(true) {
    swap = n*n;
    for(i=0;i<n;i++) {
      if(adjarr[n*x+i] && T[i]) {
	if(L[i] > (M[x]+warr[n*x+i]))
	  R[i] = x+1;
	L[i] = MIN(L[i], M[x]+warr[n*x+i]);
      }
    }
    for(i=0;i<n;i++) {
      if(T[i] && swap > L[i]) {
	swap = L[i];
	num = i;
      }
    }
    M[num] = swap;
    T[num] = 0;
    x = num;
    if(x == l-1)
      break;
    }
  return M[l-1];
}
