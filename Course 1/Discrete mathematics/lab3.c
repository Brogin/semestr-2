#include "main.h"

void printlist(int* arr, int n) {
  int i, m;
  printf("\n+\n");
  for(m=0;m<n*n;m+=n) {
    printf("%d: ",m/n+1);
    for(i=0;i<n;i++) {
      if(arr[m+i])
	printf("%d ",i+1);
      printf("%s",(i+1 == n)?"\n":"");
    }
  }
  printf("\n-\n");
  for(i=0;i<n;i++) {
    printf("%d:",i+1);
    for(m=i;m<n*n;m+=n) {
      if(arr[m])
	printf(" %d",m/n+1);
      printf("%s",(m+n >= n*n)?"\n":"");
    }
  }
}

void cycle(int* arr, int n) {
  int c, i, m, a=1, k, p=0;
  int* cyclearr = (int*) malloc (sizeof(int) * n*n);
  if(!cyclearr) {
    fprintf(stderr,"malloc error in cycle()");
    exit(1);
  } else {
    for(c=0;c<n*n;c++)
      cyclearr[c] = arr[c];
  }
  for(k=0;k<n;k++) {
    for(m=0;m<n*n;m+=n) {
      a = 0;
      for(i=0;i<n;i++) {
	a += cyclearr[m+i];
      }
      if(!a) {
	for(i=m/n+1;i<n*n;i+=n)
	  cyclearr[i] = 0;
	k++;
      } else
	p++;
    }
    if(!k)
      break;
  }
  if(!k) {
  for(k=0;k<n;k++) {
    for(i=0;i<n;i++) {
      a = 0;
      for(m=i;m<n*n;m+=n) {
	a += cyclearr[m];
      }
      if(!a) {
	for(m=i*n;m<i*n+n;m++)
	  cyclearr[m] = 0;
	k++;
      } else
	p++;
    }
    if(!k)
      break;
  }
  }
  if(k) {
    printarr(cyclearr,n,n);
    printcycle(cyclearr,n);
  } else if(!(p%n)) {
    printf("Connected graph\n");
  } else
    printf("Acycle graph\n");
}

int printcycle(int* arr, int n) {
  int m=0, i=0, swap = 0;
  while(1) {
    i = 0;
    while(1) {
      if(arr[m+i]) {
	printf("%s%d",(swap)?"-":"",m/n+1);
	if(swap) {
	  if(swap == i+1)
	    return 0;
	}
	m = i*n;
	if(!swap)
	  swap = m/n+1;
	break;
      } else
	i++;
      if(i == 8) {
	m += n;
	break;
      }
    }
  }
}

void Booleantransformation(int* arr, int n, int m) {
  int i;
  for(i=0;i<n*m;i++) {
    if(arr[i])
      arr[i] = 1;
  }
}

int Connectivity(int* arr, int* adjarr, int n, int m) {
  int i, c=0;
  int* newarr = (int*) malloc (sizeof(int) * n * m);
  for(i=0;i<n*m;i++) {
    c += arr[i];
  }
  if(c == i) {
    printf("\nStrongly connected\n");
    return 1;
  }
  transposing(arr, newarr, n);
  for(i=0;i<n*m;i++) {
    newarr[i] += arr[i];
  }
  Booleantransformation(newarr, n, n);
  c = 0;
  for(i=0;i<n*m;i++) {
    c += newarr[i];
  }
  if(c == i) {
    printf("\nUnilaterally connected graph\n");
    return 2;
  }
  transposing(adjarr, newarr, n);
  for(i=0;i<n*m;i++) {
    newarr[i] = adjarr[i] + 1;
  }  
  for(i=0;i<n-1;i++)
    newarr = arrmulti(newarr, newarr, n);
  Booleantransformation(newarr, n, n);
  c = 0;
  for(i=0;i<n*m;i++) {
    c += newarr[i];
  }
  if(c == i) {
    printf("\nWeakly connected digraph\n");
    return 3;
  }
  return 0;
}

