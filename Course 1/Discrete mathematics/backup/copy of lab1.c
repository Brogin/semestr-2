#include <stdio.h>
#include <stdlib.h>

void calcpow(int* arr, int* outpow, int* inpow, int* isolated, int n, bool *homogeneous);

int main(int argc, char* argv[]) {
  FILE* pfile;
  char filename[24];
  int n=0, m=0, x=0, y=0, i=0, c, line=1, column=0;
  int *incarr;
  int *adjarr;
  int *graphpowout;
  int *graphpowin;
  int *isolated;
  bool homogeneous = false;
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
  i = 0;
  while(i < m)
    printf("%2d%s",++i,(i+1==m)?"\n":" ");
  i = 0;
  while(i < n*m) {
    printf("%2d%s",incarr[i],(i !=0 && (i+1)%m == 0)?"\n":" ");
    i++;
  }
  printf("\n");
  i = 0;
  while(i < n)
    printf("%2d%s",++i,(i+1==n)?"\n":" ");
  i = 0;
  while(i < n*n) {
    printf("%2d%s",adjarr[i],(i != 0 && (i+1)%n == 0)?"\n":" ");
    i++;
  }
  graphpowout = (int*) malloc (sizeof(int) * n + 1);
  graphpowin = (int*) malloc (sizeof(int) * n + 1);
  isolated = (int*) malloc (sizeof(int) * n + 1);
  if(!graphpowout || !graphpowin) {
    fprintf(stderr, "%s malloc error", (graphpowout)?"graphpowout":"graphpowin");
    exit(3);
  } else {
    for(c = 0;c<n+1;c++) {
      graphpowout[c] = 0;
      graphpowin[c] = 0;
      isolated[c] = 0;
    }
  }
  calcpow(adjarr,graphpowout,graphpowin,isolated, n, &homogeneous);
  i = 0;
  while(i < n) { 
    printf("d-(%d)=%d%s",i+1,*graphpowout,((i+1)%n == 0 && i != 0)?"\n":" ");
    graphpowout++;
    i++;
  }
  i = 0;
  while(i < n) {
    printf("d+(%d)=%d%s",i+1,*graphpowin,((i+1)%n == 0 && i != 0)?"\n":" ");
    graphpowin++;
    i++;
  }
  if(homogeneous)
    printf("Homogeneous graph K = %d\n",*(--graphpowout));
  i = 0;
  while(i < n) {
    if(isolated[i] != 0)
      printf("%d%s",i+1,(isolated[i] == 1)?"isolated vertex":"dangling vertex");
    i++;
  }
  return 0;
}

void calcpow(int* arr, int* outpow, int* inpow, int* isolated, int n, bool* homogeneous) {
  int column = 0, line = 1, i = 0;
  while(i < n) {
    for(column = 0;column < n;column++) {
      outpow[i] += arr[column];
      inpow[i] += arr[(column)*n];
      line*=n;
    }
    if(i > 0) {
      if(outpow[i] == outpow[i-1])
	*homogeneous = true;
      else
	*homogeneous = false;
    }
    if((outpow[i] == 1 && inpow[i] == 0) || (outpow[i] == 0 && inpow[i] == 1))
      isolated[i] = 1;
    if(outpow[i] == inpow[i] == 0)
      isolated[i] = 2;
    i++;
  }
}
