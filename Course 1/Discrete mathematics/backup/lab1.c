#include <stdio.h>
#include <stdlib.h>

void printmenu(int num);
int* arrpow(int* arr, int n, bool mode, int ret);
void printarr(int* arr, int n, int m);
int* arrmulti(int* arr, int* arrs, int n);
int* arrdistance(int* arr, int* multi, int n, bool mode);
void metric(int* arr, int n);
void isoleafver(int* arr, int* arrs, int n);
int* floyd_warshall(int* arr, int n, bool mode);


int main(int argc, char* argv[]) {
  FILE* pfile;
  char filename[24];
  int n=0, m=0, x=0, y=0, c, column=0;
  int *incarr;
  int *adjarr;
  int *multi;
  int *distance;
  if(argc == 1) {
    printf("Enter file name: ");
    scanf("%s", filename);
    pfile = fopen(filename, "r");
  } else if(argc > 2) {
    fprintf(stderr, "%s argc error",argv[0]);
    exit(1);
  } else
    pfile = fopen(argv[1], "r");
  while(fscanf(pfile,"%d %d",&x,&y) != EOF) {
    if(n == 0 && m == 0) {
      n = x;
      m = y;
      incarr = (int*) malloc (sizeof(int) * (n*m+1));
      adjarr = (int*) malloc (sizeof(int) * (n*n+1));
      if(!incarr || !adjarr) {
	fprintf(stderr, "%s malloc error", (incarr)?"incarr":"adjarr");
	exit(2);
      } else {
	for(c = 0;c<n*m+1;c++)
	  incarr[c] = 0;
	for(c = 0;c<n*n+1;c++)
	  adjarr[c] = 0;
      }
    } else {
      incarr[(x-1)*m+(column-1)] = -1;
      incarr[(y-1)*m+(column-1)] = 1;
      adjarr[(x-1)*n+(y-1)] = 1;
      column++;
    }
  }
  c = 0;
  while(c != 101) {
    printmenu(0);
    scanf("%d",&c);
    system("clear");
    if(c == 1) {
      printarr(incarr, n, m);
      printf("\n");
      printarr(adjarr, n, n);
      scanf("%d",&c);
    } else if(c == 2) {
      distance = arrdistance(adjarr, multi, n, false);
      printarr(distance, n ,n);
      scanf("%d",&c);
    } else if(c == 3) {
      distance = arrdistance(adjarr, multi, n, true);
      scanf("%d",&c);
    } else if(c == 4) {
      distance = arrdistance(adjarr, multi, n, false);
      metric(distance, n);
      scanf("%d",&c);
    } else if(c == 5) {
      arrpow(adjarr,n,false,0);
      scanf("%d",&c);
    } else if(c == 6) {
      arrpow(adjarr,n,true,0);
      scanf("%d",&c);
    } else if(c == 7) {
      distance = floyd_warshall(adjarr, n, false);
      printarr(distance, n ,n);
      scanf("%d",&c);
    } else if(c == 8) {
      distance = floyd_warshall(adjarr, n, true);
      printarr(distance, n ,n);
      scanf("%d",&c);
    } else if(c == 99)
      break;
    else {
      ;
    }
  }
  return 0;
}
void printmenu(int num) {
  if(num == 0) {
    printf("123: \n");
    printf("1) print inc & adj arrs\n");
    printf("2) print distance arr\n");
    printf("3) print tiers\n");
    printf("4) metric\n");
    printf("5) pow\n");
    printf("6) list of isolated and pendant vertices\n");
    printf("7) Floyd-Warshall\n");
    printf("8) reachability - Floyd-Warshall\n");
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

int* arrdistance(int* arr, int* multi, int n, bool mode) {
  int i = 2, c, d = 0, p = 0;;
  multi = arrmulti(arr, arr, n);
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
  int i = 0;
  for(int c=0;c<n;c++) {
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
  int c;
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
    for(int k=0;k<n;++k) {
      for(int i=0;i<n;++i) {
	for(int j=0;j<n;++j) {
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
    for(int k=0;k<n;++k) {
      for(int i=0;i<n;++i) {
	for(int j=0;j<n;++j) {
	  //if(dist[j*n+i] < dist[i+k*n] + dist[k+j*n])
	    dist[j*n+i] = dist[j*n+i] | (dist[i+k*n] & dist[k+j*n]);
	    //else
	    //  dist[j*n+i] = dist[i+k*n] + dist[k+j*n];
	}
      }
    }
  }
  return dist;
}
