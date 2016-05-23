#include "main.h"

void printmenu(int num, int argc, char* argv[]) {
  if(num == 0) {
    printf("Menu: \n");
    printf("0) open file %s\n",(argc == 2)?argv[1]:"");
    printf("1) print inc & adj arrs\n");
    printf("2) print distance arr\n");
    printf("3) print tiers\n");
    printf("4) metric\n");
    printf("5) pow\n");
    printf("6) list of isolated and pendant vertices\n");
    printf("7) Floyd-Warshall\n");
    printf("8) reachability - Floyd-Warshall\n");
    printf("9) graph list\n");
    printf("10) cycle\n");
    printf("11) DFS\n");
    printf("12) BFS\n");
    printf("13) Topologycal Sorting\n");
    printf("14) Strongly Connected Components\n");
    printf("15) print weight arr\n");
    printf("16) Dijkstra's algorithm\n");
    printf("17) Belman-Ford algorithm\n");
    printf("18) Floyd-Warshall algorithm\n");
    printf("19) Johnson algorith\n");
    printf("20) backtracking - Euler\n");
    printf("21) backtracking - Hamilton\n");
    printf("22) Color\n");
    printf("23) Prim\n");
    printf("24) Ford-Falcerson\n");
    printf("99) exit\n");
  } else if(num == 1) {
    
  }
}

int* arrpow(int* arr, int n, bool mode, int ret) {
  int c=0, s=0;
  int* arrplus = (int*) malloc (sizeof(int) * n+1);
  int* arrminus = (int*) malloc (sizeof(int) * n+1);
  if(!arrminus || !arrplus) {
    fprintf(stderr,"malloc error in arrpow()");
    exit(1);
  } else {
    for(c=0;c<n;c++) {
      arrplus[c] = 0;
      arrminus[c] = 0;
    }
  }
  for(c=0;c<n;c++) {
    for(s=0;s<n;s++)
      arrminus[c] += arr[s+c*n];
    for(s=0;s<n*n;s+=n)
      arrplus[c] += arr[s+c%n];
  }
  if(ret == 1)
    return arrplus;
  else if(ret == 2)
    return arrminus;
  if(!mode) {
    printf("+\n");
    printarr(arrplus, 1, n);
    printf("-\n");
    printarr(arrminus, 1, n);
  } else if(mode)
    isoleafver(arrplus, arrminus, n);
  return 0;
}

void printarr(int* arr, int n, int m) {
  int i;
  for(i=0;i < m;i++) {
    if(!i)
      printf("   ");
    printf("%2d%s",i+1,((i+1)<m)?" ":"\n");
  }
  for(i=0;i < n*m;i++) {
    if(!(i%m))
      printf("%2d:",i/m+1);
    printf("%2d%s",arr[i],(i !=0 && ((i+1)%m == 0))?"\n":" ");
  }
}

int* arrmulti(int* arr, int* arrs, int n) {
  int c, k, line = 0, row = 0;
  int* multi = (int*) malloc (sizeof(int) * n*n+1);
  if(!multi) {
    fprintf(stderr,"malloc error in arrmulti()");
    exit(1);
  } else {
    for(c=0;c<n*n+1;c++)
      multi[c] = 0;
  }
  for(c=0;c<n*n;c++) {
    line = n*(c/n);
    row = c % n;
    /*if(!c || !((c-(line)/n)%n))
      continue;*/
    for(k = 0;k<n;k++)
      multi[c] += arr[line+k]*arrs[row+(k*n)];
  }
  return multi;
}
