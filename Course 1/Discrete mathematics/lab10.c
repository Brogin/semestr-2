#include "main.h"

void Euler(int *arr, int n, int m) {
  int W[m];
  int L[n*n];
  int i, c, root, length = 0, cur, first, trail = 0;
  int* arrplus = (int*) malloc (sizeof(int) * n+1);
  int* arrminus = (int*) malloc (sizeof(int) * n+1);
  arrplus = arrpow(arr, n, true, 1);
  arrminus = arrpow(arr, n, true, 2);
  first = 0;
  for(i=0;i<n;i++) {
    if((arrplus[i]+arrminus[i])%2 != 0) {
      trail++;
    }
  }
  if(trail != 0 && trail != 2) {
    printf("Nothing was found!\n");
    return;
  }
  for(i=first;i<n;i++) {
    if((arrplus[i]+arrminus[i])%2 != 0) {
      first = i;
      trail = 1;
      //printf("%d %d\n",first, trail);
      //scanf("%d", &c);
      break;
    }
  }
  if(trail)
    printf("Euler trail \n");
  else
    printf("Euler circle \n");
  bool step = 0;
  for(i=0;i<m;i++) {
    W[i] = 0;
  }
  for(i=0;i<n;i++) {
    for(c=0;c<n;c++) {
      L[i*n+c] = 0;
    }
  }
  for(i=0;i<n;i++) {
    for(c=0;c<n;c++) {
      if(arr[i*n+c]) {
	L[i*n+c] = 1;
	L[c*n+i] = 1;	
      }
    }
  }  
  //first = 4;
  cur = first;
  length = 0;
  W[length] = cur+1;
  while(true) {
    /*if(i == first && length == m-1) {
      printarr(W, 1, m);
      break;
      } else {*/
    step = 0;
      for(i=0;i<n;i++) {
	if(L[cur*n+i]) {
	  length++;
	  if(/*i == first &&*/ length >= m) {
	    printarr(W, 1, m);
	    return;
	  }
	  L[cur*n+i] = 0;
	  L[i*n+cur] = 0;
	  cur = i;
	  W[length] = cur+1;
	  step = 1;
	  //printf("%d %d %d\n", cur, length, i);
	  //scanf("%d", &c);
	  break;
	}
      }
      if(!step) {
	for(i=0;i<n;i++) {
	  if(arr[cur*n+i]) {
	    L[cur*n+i] = 1;
	    L[i*n+cur] = 1;
	  }
	}
	W[length] = 0;
	if(length == 0 || length+1 >= m) {
	  if(first < n) {
	    for(i=0;i<m;i++) {
	      W[i] = 0;
	    }
	    for(i=0;i<n;i++) {
	      for(c=0;c<n;c++) {
		L[i*n+c] = 0;
	      }
	    }
	    for(i=0;i<n;i++) {
	      for(c=0;c<n;c++) {
		if(arr[i*n+c]) {
		  L[i*n+c] = 1;
		  L[c*n+i] = 1;	
		}
	      }
	    }  
	    if(!trail) {
	      first++;
	    } else {
	      for(i=first;i<n;i++) {
		if((arrplus[i]+arrminus[i])%2 != 0) {
		  first = i;
		  break;
		}
	      }
	      if(i == n) {
		printf("Eulerian trail not found\n");
		return;
	      }
	    }
	    cur = first;
	    length = 0;
	    W[length] = cur+1;
	  }
	  else {
	    printf("Eulerian circle not found\n");
	    return;
	  }
	  cur = first;	  
	} else {
	  length--;
	  cur = W[length]-1;
	  //}
      }
    }
  }
}
