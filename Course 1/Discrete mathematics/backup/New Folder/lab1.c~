#include <stdio.h>
#include <stdlib.h>

int main(int argc, char* argv[])
{
  FILE* pfile;
  int n, m;
  if(argc == 1)
    fprintf(stderr,"no arguments was given");
  else if(!(pfile = fopen(argv[1], "r")))
    {
      fprintf(stderr,"%s can't open %s",argv[0],*argv);
      exit(1);
    }
  else
    {
      fscanf(pfile,"%d %d",&n,&m);
      fprintf(stdout,"%d %d",n,m);
      fclose(pfile);
    }
  exit(0);
}
