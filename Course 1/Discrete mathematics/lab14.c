#include "main.h"

void FordFalcerson(int* arr, int* warr, int n) {
  int i, c, s, t, S = 0, T = 0, v, w, last;
  int check;
  int prev[n];
  int res[n];
  int dir[n];
  int M[n];
  int L[n];
  int* F = (int*) malloc (sizeof(int) * n*n);
  if(!F) {
    fprintf(stderr, "malloc error in FordFalcerson()\n");
    exit(1);
  } else {
    for(i=0;i<n*n;i++)
      F[i] = 0;
  }
  for(i=0;i<n;i++) {
    prev[i] = 0;
    res[i] = 0;
    dir[i] = 0;
    M[i] = 0;
    L[i] = 0;
  }
  for(i=1;i<=n;i++) {
    t = 0;
    s = 0;
    for(c=0;c<n;c++) {
      if(arr[(i-1)*n+c])
	t++;
      if(arr[c*n+(i-1)])
	s++;
    }
    if(!S && !s)
      S = i;
    else if(S && !s) {
      printf("error - second S\n");
      return;
    }
    if(!T && !t)
      T = i;
    else if(T && !t){
      printf("error - second T\n");
      return;
    }
  }
  S = S - 1;
  T = T - 1;
  printf("%d %d\n",S+1, T+1);
  M[S] = 1;
  L[S] = 1;
  res[S] = n*n*n;
  while(true) {
    check = 0;
    v = 0;
    for(i=0;i<n;i++) {
      if(!M[i]) {
	check++;
      } else if(!v && M[i]) {
	v = i;
	M[i] = 0;
      }
    }
    if(check == n)
      break;

    for(i=0;i<n;i++) {
      if(!L[i] && arr[v*n+i] && (F[v*n+i] < warr[v*n+i])) {
	res[i] = MIN(warr[v*n+i]-F[v*n+i], res[v]);
	w = i;
	prev[w] = v;
	if(w != T)
	  M[w] = 1;
	L[i] = 1;
      }
      if(!L[i] && arr[i*n+v] && (F[v*n+i] > 0)) {
	res[i] = MIN(F[v*n+i], res[v]);
	w = i;
	prev[w] = v;
	if(w != T)
	  M[w] = 1;
	dir[w] = 1;
	L[i] = 1;
      }
    }
    /*
    printarr(L, 1, n);
    printarr(res, 1, n);
    printarr(F, n, n);
    printarr(M, 1, n);
    printf("-----\n");
    scanf("%d", &c);
    */
    if(L[T]) {
      last = T;
      i = prev[T];
      while(true) {
	if(!dir[last])
	  F[i*n+last] = F[i*n+last] + res[T];
	else
	  F[i*n+last] = F[i*n+last] - res[T];
	last = i;
	if(i == S)
	  break;
	i = prev[last];
      }
      for(i=0;i<n;i++) {
	prev[i] = 0;
	res[i] = 0;
	dir[i] = 0;
	M[i] = 0;
	L[i] = 0;
      }
      M[S] = 1;
      L[S] = 1;
      res[S] = n*n*n;
    }    
  }
  printarr(F, n, n);
  printarr(warr, n, n);
}
