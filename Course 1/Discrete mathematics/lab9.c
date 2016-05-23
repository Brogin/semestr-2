#include "main.h"

void FloydWarshall(int* arr, int* warr, int n, int f, int l) {
  int c, k, i, j, t=-1;
  int Tr[n];
  for(c=0;c<n;c++)
    Tr[c] = 0;
  int* dist = (int*) malloc (sizeof(int) * n*n+1);
  int* way = (int*) malloc (sizeof(int) * n*n+1);
  if(!dist || !way) {
    fprintf(stderr,"error malloc in FloydWarshall");
    exit(1);
  } else {
    for(c = 0;c<n*n;c++) {
      way[c] = c/n+1;
      if(c%n == c/n) {
	dist[c] = 0;
	way[c] = 0;
      } else if(!(arr[c]))
	dist[c] = n*n;
      else {
	dist[c] = warr[c];	
      }	
    }
  }
  for(k=1;k<=n;k++) {
    for(i=0;i<n;i++) {
      for(j=0;j<n;j++) {
	//if(arr[n*j+i]) {
	if(dist[j*n+i] < dist[i+(k-1)*n] + dist[(k-1)+j*n])
	  dist[j*n+i] = dist[j*n+i];
	else {
	  if(dist[j*n+i] > dist[i+(k-1)*n] + dist[(k-1)+j*n]) {
	    way[j*n+i] = way[i+(k-1)*n];
	    printarr(way,n,n);
	    //printf("%d, %d, %d, %d, %d \n ",i, j, k, dist[j*n+i], dist[i+(k-1)*n] + dist[(k-1)+j*n]);
	  }
	  dist[j*n+i] = dist[i+(k-1)*n] + dist[(k-1)+j*n];
	}
	//}
      }
    }
    for(c=0;c<n;c++) {
      if(dist[c*n+c] < 0){
	printf("minus circle! EXIT");
	return;
      }
    }
  }
  printarr(dist,n,n);
  printarr(way,n,n);
  printf("length from %d to %d = %d\n",f,l,dist[(l-1)+(f-1)*n]);
  //printf("%c ", f+96);
  Tr[0] = l;
  int ll;
  ll = l-1;
  c = 1;
  while(ll != f-1) {
    Tr[c] = way[(f-1)*n+ll];
    ll = Tr[c]-1;
    c++;
  }
  for(--c;c>=0;c--)
    printf("%d ",Tr[c]);
}

void Johnson(int* arr, int* warr, int n) {
  int i, v, u, c;
  int H[n];
  int* adjN = (int*) malloc(sizeof(int) * (n+1)*(n+1));
  int* warrN = (int*) malloc(sizeof(int) * (n+1)*(n+1));
  int* M = (int*) malloc(sizeof(int) * n*n);
  int* Ml = (int*) malloc(sizeof(int) * n*n);
  if(!adjN || !warrN || !M) {
    fprintf(stderr,"malloc error in Johnson()");
    exit(1);
  } else {
    for(c=0;c<(n+1)*(n+1);c++) {
      if(c<(n+1)*n) {
	adjN[c] = 0;
	warrN[c] = 0;
      } else if(c != (n+1)*(n+1)-1){
	adjN[c] = 1;
      } else
	adjN[c] = 0;
    }
    for(c=0;c<n;c++) {
      M[c] = 0;
      for(i=0;i<n;i++){
	adjN[c*(n+1)+i] = arr[c*n+i];
	warrN[c*(n+1)+i] = warr[c*n+i];
      }
    }
  }
  //printarr(adjN, n+1, n+1);
  //printarr(warrN, n+1, n+1);
  /*printarr(arr, n, n);
  printarr(warr, n, n);*/
  warrN = BelmanFordint(adjN, warrN, n+1, n+1, 0);
  for(c=0;c<n;c++)
    H[c] = warrN[(n+1)*(n)+c];
  //printarr(H, 1, n);
  for(v=0;v<n;v++) {
    for(u=0;u<n;u++) {
      warr[v*n+u] = warr[v*n+u] + H[v] - H[u];
    }
  }
  //printarr(warr, n, n);
  for(v=0;v<n;v++) {
    for(u=0;u<n;u++) {
      Ml[v*n+u] = Dijkstraint(arr, warr, n, v+1, u+1);
    }
  }
  //printarr(Ml, n, n);
  for(v=0;v<n;v++) {
    for(u=0;u<n;u++) {
      M[v*n+u] = Ml[v*n+u] - H[v]+ H[u];
    }
  }
  printarr(M, n, n);
}
