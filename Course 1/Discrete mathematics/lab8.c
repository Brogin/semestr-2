#include "main.h"

void BelmanFord(int* adjarr, int* warr, int n, int f, int last) {
  int i, v, u, x, check;
  int P[n];
  int* l = (int*) malloc(sizeof(int) * n*n+1);
  if(!l) {
    fprintf(stderr,"malloc error in BelmanFord()");
    exit(1);
  } else {
    for(i=0;i<n*n;i++)
      l[i] = n*n;
    for(i=0;i<n;i++)
      P[i] = 0;
  }
  x = f - 1;
  l[x] = 0;
  for(i=1;i<=n;i++) {
    //check = 0;
    if(i != n) {
      for(v=0;v<n;v++) {
	l[n*i+v] = l[n*(i-1)+v];
	for(u=0;u<n;u++) {
	  if(adjarr[n*u+v]) {
	    if(l[n*(i-1)+u]+warr[n*u+v] < l[n*i+v]) {
	      l[n*i+v] = l[n*(i-1)+u]+warr[n*u+v];
	      P[v] = u+1;
	      //check++;
	    }
	  }
	}
      }
    } else {
      for(v=0;v<n;v++) {
	for(u=0;u<n;u++) {
	  if(adjarr[n*u+v]) {
	    if(l[n*(n-1)+u]+warr[n*u+v] < l[n*(n-1)+v]) {
	      printf("\nnegative cycle!");
	      return;
	    }
	  }
	}
      }
    }
    /*if(!check)
      break;*/
  }
  if(!last) {
    for(i=0;i<n;i++) {
      if(i+1 != f) {
	int line = 1;
	int e = i;
	int W[n];
	while(e+1 != f) {
	  W[line] = P[e];
	  e = W[line]-1;
	  line++;
	}
	W[0] = i+1;
	printf("length from %d to %d = %d\n",f,i+1,l[n*(n-1)+i]);
	for(--line;line>=0;line--)
	  printf("%c ",W[line]+96);
	printf("\n");
      }
    }
  } else {
    int line = 1;
    int e = last - 1;
    int W[n];
    while(e+1 != f) {
      W[line] = P[e];
      e = W[line]-1;
      line++;
    }
    W[0] = last;
    printf("length from %d to %d = %d\n",f,last,l[n*(n-1)+last-1]);
    for(--line;line>=0;line--)
      printf("%c ",W[line]+96);
    printf("\n");
  }
  //printarr(l, n, n);
  //printarr(P, 1, n);
}

int* BelmanFordint(int* adjarr, int* warr, int n, int f, int last) {
  int i, v, u, x, check;
  int P[n];
  int* l = (int*) malloc(sizeof(int) * n*n+1);
  if(!l) {
    fprintf(stderr,"malloc error in BelmanFord()");
    exit(1);
  } else {
    for(i=0;i<n*n;i++)
      l[i] = n*n;
    for(i=0;i<n;i++)
      P[i] = 0;
  }
  x = f - 1;
  l[x] = 0;
  for(i=1;i<=n;i++) {
    //check = 0;
    if(i != n) {
      for(v=0;v<n;v++) {
	l[n*i+v] = l[n*(i-1)+v];
	for(u=0;u<n;u++) {
	  if(adjarr[n*u+v]) {
	    if(l[n*(i-1)+u]+warr[n*u+v] < l[n*i+v]) {
	      l[n*i+v] = l[n*(i-1)+u]+warr[n*u+v];
	      P[v] = u+1;
	      //check++;
	    }
	  }
	}
      }
    } else {
      for(v=0;v<n;v++) {
	for(u=0;u<n;u++) {
	  if(adjarr[n*u+v]) {
	    if(l[n*(n-1)+u]+warr[n*u+v] < l[n*(n-1)+v]) {
	      printf("\nnegative cycle!");
	      return;
	    }
	  }
	}
      }
    }
    /*if(!check)
      break;*/
  }
  if(!last) {
    for(i=0;i<n;i++) {
      if(i+1 != f) {
	int line = 1;
	int e = i;
	int W[n];
	while(e+1 != f) {
	  W[line] = P[e];
	  e = W[line]-1;
	  line++;
	}
	W[0] = i+1;
	/*printf("length from %d to %d = %d\n",f,i+1,l[n*(n-1)+i]);
	for(--line;line>=0;line--)
	  printf("%c ",W[line]+96);
	  printf("\n");*/
      }
    }
  } else {
    int line = 1;
    int e = last - 1;
    int W[n];
    while(e+1 != f) {
      W[line] = P[e];
      e = W[line]-1;
      line++;
    }
    W[0] = last;
    /*printf("length from %d to %d = %d\n",f,last,l[n*(n-1)+last-1]);
    for(--line;line>=0;line--)
      printf("%c ",W[line]+96);
      printf("\n");*/
  }
  //printarr(l, n, n);
  //printarr(P, 1, n);
  return l;
}
