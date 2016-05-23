#include "main.h"

void Hamilton(int* arr, int n) {
  int M[n];
  int W[n];
  int L[n*n];
  int i, c, length, cur, first, prev, ff;
  bool step = 0;
  for(i=0;i<n;i++) {
    W[i] = 0;
    M[i] = 0;
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
  cur = first;
  length = 0;
  W[length] = cur+1;
  while(true) {
    step = 0;
    for(i=0;i<n;i++) {
      if(L[cur*n+i]) {
	length++;
	if(length >= n-1) {
	  cur = i;
	  W[length] = cur+1;
	  //printf("%d %d %d\n", cur, length, i);
	  //printf("%d %d %d\n", cur, length, i);
	  printarr(W, 1, n);
	  return;
	}
	for(c=0;c<n;c++) {
	  L[cur*n+c] = 0;
	  L[c*n+cur] = 0;
	}
	prev = cur;
	cur = i;
	M[cur] = 1;
	W[length] = cur+1;
	step = 1;
	//printf("%d %d %d %d\n", cur, prev, length, i);
	//printarr(M, 1, n);
	//printarr(L, n, n);
	//printarr(W, 1, n);
	//scanf("%d", &ff);
	break;
      }
    }
    if(W[0] == 0) {
      printf("Nothing was found!\n");
      break;
    }
    if(!step) {
      M[W[length]-1] = 0;
      for(i=0;i<n;i++) {
	if(arr[cur*n+i] && !M[i]) {
	  //for(c=0;c<n;c++) {
	  //if(!M[i]) {
	      L[cur*n+i] = 1;
	      L[i*n+cur] = 1;
	      //}
	    //}
	}
      }
      //M[W[length]-1] = 0;
      W[length] = 0;
      if(length-1 == 0 || length+1 >= n) {
	if(first < n) {
	  for(i=0;i<n;i++) {
	    W[i] = 0;
	    M[i] = 0;
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
	  //if(!trail) {
	  first++;
	    /*} else {
	    for(i=first;i<n;i++) {
	      if((arrplus[i]+arrminus[i])%2 != 0) {
		first = i;
		break;
		}
		}*/
	  /*if(i == n) {
	    printf("Hamilton trail not found\n");
	    return;
	      //}
	      }*/
	  cur = first;
	  length = 0;
	  W[length] = cur+1;
	} else {
	  printarr(W, 1, n);
	  printf("Hamoilton circle not found\n");
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
