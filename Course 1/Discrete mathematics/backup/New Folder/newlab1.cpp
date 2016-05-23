#include <iostream>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
using namespace std;

int **createarr(int *N, int *M, int **arr, bool act)
{
  int i = 0, n = 0;
  if(act)
    {
      arr = new int *[*N];
      for(i=0;i<*N;i++)
	  arr[i] = new int [*M];
      return arr;
    }
  else
    {
      for(i=0;i<*N;i++)
	delete [] arr[i];
      delete [] arr;
      return arr;
    }
}

int main(int argc, char* argv[])
{
  FILE* pfile;
  char filestr[128];
  int type;
  int **arr;
  char *ps;
  int n = 0, m, x, y, i = 0;
  pfile = fopen("graph_01_1.txt", "r");
  cout << "choise type: \n1 - Incidence matrix\n2 - Adjacency matrix" << endl;
  cin >> type;
  while(fgets(filestr, 128, pfile))
    {
      if(!n)
	{
	  n = atoi(strtok(filestr," "));
	  m = atoi(strtok(NULL," ")); 
	  if(type == 1)
	    arr = createarr(&n, &m, arr, true);
	  else
	    {
	      m = n;
	      arr = createarr(&n, &n, arr, true);
	    }
	}
      else
	{
	  x = atoi(strtok(filestr," "))-1;
	  y = atoi(strtok(NULL,"\n"))-1;
	  if(type == 1)
	    {
	      arr[x][i] = -1;
	      arr[y][i] = 1;
	    }
	  else
	    {
	      arr[x][y] = 1;
	    }
	  i++;
	}      
    }
  
  for(x=0;x<n;x++)
    {
      for(y=0;y<m;y++)
	{
	  cout << arr[x][y] << "  ";
	}
      cout << endl;
    }
  createarr(&n, &m, arr, false);
  return 0;
}
