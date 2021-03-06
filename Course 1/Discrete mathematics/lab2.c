#include "main.h"

int* arrdistance(int* arr, int n, bool mode) {
  int i = 2, c, d = 0, p = 0;
  int* multi = arrmulti(arr, arr, n);
  int* arrplus = (int*) malloc (sizeof(int) * n);
  arrplus = arrpow(arr, n, false, 1);
  int* arrminus = (int*) malloc (sizeof(int) * n);
  arrminus = arrpow(arr, n, false, 2);
  for(c=0;c<n;c++) {
    if(!arrminus[c])
      p += arrplus[c];
    if(!arrplus[c])
      p++;
  }
  int* dist = (int*) malloc (sizeof(int) * n*n+1);
  if(!dist) {
    fprintf(stderr,"malloc error in arrdistance()");
    exit(1);
  } else {
    if(mode)
      printf("Tier %2d: ", i-1);
    for(c=0;c<n*n+1;c++) {
      if(arr[c]) {
	if(mode)
	  printf("%2d - %2d; ", c/n+1, c%n+1);
	dist[c] = 1;
      } else {
	dist[c] = 0;
	d++;
      }
    }
  }
  while(d > n && i+p < n) {
    if(mode)
      printf("\nTier %2d: ", i);
    for(c=0;c<n*n;c++) {
      if(!(dist[c]) && multi[c]) {
	if(mode)
	  printf("%2d - %2d; ", c/n+1, c%n+1);
	dist[c] = i;
	d--;
      }
    }
    i++;
    multi = arrmulti(multi, arr, n);
  }
  return dist;
}

void metric(int* arr, int n){
  int r=n, d=0, c, s=1, t=0;
  int* metric = (int*) malloc (sizeof(int) * n+1);
  if(!metric) {
    fprintf(stderr,"malloc error in metric()");
    exit(1);
  }
  for(c=0;c<n*n;c+=n) {
    for(s=1,t=0;s<n;s++) {
      if(arr[s+c] > t)
	t = arr[s+c];
      metric[c/n] = t;
    }
    if(r > t)
      r = t;
    if(d < t)
      d = t;
  }
  for(c=0;c<n;c++) {
    if(metric[c] == r) {
      printf("central vertex: %2d\n",c+1);
    }
  }
  //printarr(metric, 1, n);
  printf("radius: %2d\ndiameter: %2d\n",r,d);
}

void isoleafver(int* arr, int* arrs, int n) {
  int i = 0, c;
  for(c=0;c<n;c++) {
    if(!(arr[c]) && !(arrs[c])) {
      printf("Vertex %2d -  isolated\n", c+1);
      i++;
    } else if((!(arr[c]) && arrs[c] == 1) || (arr[c] == 1 && !(arrs[c]))) {
      printf("Vertex %2d - pendant\n", c+1);
      i++;
    }
  }
    if(!i)
      printf("nothing was found\n");
}

int* floyd_warshall(int* arr, int n, bool mode) {
  int c, k, i, j;
  int* dist = (int*) malloc (sizeof(int) * n*n+1);
  if(!dist) {
    fprintf(stderr,"error malloc in floyd_warshall");
    exit(1);
  } else {
    for(c = 0;c<n*n;c++) {
      if(!mode) {
	/*if(c%n == c/n)
	  dist[c] = 0;*/
	/*else */if(!(arr[c]))
	  dist[c] = n*n;
	else
	  dist[c] = arr[c];
      } else {
	if(!arr[c])
	  dist[c] = 0;
	else
	  dist[c] = 1;
      }
    }
  }
  if(!mode) {
    for(k=0;k<n;++k) {
      for(i=0;i<n;++i) {
	for(j=0;j<n;++j) {
	  if(dist[j*n+i] < dist[i+k*n] + dist[k+j*n])
	    dist[j*n+i] = dist[j*n+i];
	  else
	    dist[j*n+i] = dist[i+k*n] + dist[k+j*n];
	}
      }
    }
    for(c = 0;c<n*n;c++) {
      if(dist[c] == n*n)
	dist[c] = 0;
    }
  } else {
    for(k=0;k<n;++k) {
      for(i=0;i<n;++i) {
	for(j=0;j<n;++j) {
	  //if(dist[j*n+i] < dist[i+k*n] + dist[k+j*n])
	    dist[j*n+i] = dist[j*n+i] | (dist[i+k*n] & dist[k+j*n]);
	    //else
	    //  dist[j*n+i] = dist[i+k*n] + dist[k+j*n];
	}
      }
    }
  }
  for(i=0;i<n;i++)
    dist[i*n+i] = 1;
  return dist;
}
