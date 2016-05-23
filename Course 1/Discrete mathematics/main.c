#include "main.h"

int main(int argc, char* argv[]) {
  FILE* pfile;
  char filename[24];
  int n=0, m=0, x=0, y=0, w=0, c, column=0, weight=0, minus = 0;
  int *incarr;
  int *adjarr;
  int *distance;
  int *weightarr;
  /*if(argc == 1) {
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
    }*/
  c = 0;
  while(c != 101) {
    printmenu(0, argc, argv);
    scanf("%d",&c);
    system("clear");
    if(c == 0) {
      if(pfile && incarr && adjarr) {
	close(pfile);
	column = 0;
	minus = 0;
      }
      printf("Graph with weighted edges? (1-yes / 0-no)");
      scanf("%d", &weight);
      if(argc == 1) {
	printf("Enter file name: ");
	scanf("%s", filename);
	pfile = fopen(filename, "r");
      } else if(argc > 2) {
	fprintf(stderr, "%s argc error",argv[0]);
	exit(1);
      } else
	  pfile = fopen(argv[1], "r");
      //while(fscanf(pfile,"%d %d",&x,&y) != EOF) {
      fscanf(pfile,"%d %d",&n,&m);
      incarr = (int*) malloc (sizeof(int) * (n*m+1));
      adjarr = (int*) malloc (sizeof(int) * (n*n+1));
      if(weight)
	weightarr = (int*) malloc (sizeof(int) * (n*n+1));
      if(weight && !weightarr) {
	fprintf(stderr, "%s malloc error weightarr");
	exit(2);
      } else if(!incarr || !adjarr) {
	fprintf(stderr, "%s malloc error", (incarr)?"incarr":"adjarr");
	exit(2);
      } else {
	for(c = 0;c<n*m+1;c++)
	  incarr[c] = 0;
	for(c = 0;c<n*n+1;c++)
	  adjarr[c] = 0;
	if(weight) {
	  for(c = 0;c<n*n+1;c++)
	    weightarr[c] = 0;
	}
      }
      if(!weight) {
	while(fscanf(pfile,"%d %d",&x,&y) != EOF) {
	  incarr[(x-1)*m+(column-1)] = -1;
	  incarr[(y-1)*m+(column-1)] = 1;
	  adjarr[(x-1)*n+(y-1)] = 1;
	  column++;
	}
      } else {
	while(fscanf(pfile,"%d %d %d",&x,&y,&w) != EOF) {
	  incarr[(x-1)*m+(column-1)] = -1;
	  incarr[(y-1)*m+(column-1)] = 1;
	  adjarr[(x-1)*n+(y-1)] = 1;
	  weightarr[(x-1)*n+(y-1)] = w;
	  if(w < 0)
	    minus = 1;
	  column++;
	}
      }
      scanf("%d",&c);
    } else if(c == 1) {
      printarr(incarr, n, m);
      printf("\n");
      printarr(adjarr, n, n);
      scanf("%d",&c);
    } else if(c == 2) {
      distance = arrdistance(adjarr, n, false);
      printarr(distance, n ,n);
      scanf("%d",&c);
    } else if(c == 3) {
      distance = arrdistance(adjarr, n, true);
      scanf("%d",&c);
    } else if(c == 4) {
      distance = arrdistance(adjarr, n, false);
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
      Connectivity(distance, adjarr, n, n);
      scanf("%d",&c);
    } else if(c == 9) {
      printlist(adjarr, n);
      scanf("%d",&c);
    } else if(c == 10) {
      cycle(adjarr, n);
      scanf("%d",&c);
    } else if(c == 11) {
      /*printf("number of the vertex (1-%d): ",n);
      scanf("%d",&c);
      int cache[n];
      int dfsnum = 0;
      dStack ds = {0, 0};
      Spush(&ds, c-1);
      for(i=0;i<n;i++)
      cache[i] = 0;
      DFS(adjarr, &ds, dfsnum, n, c*n, cache);*/
      DFS(adjarr, n);
      scanf("%d",&c);
    } else if(c == 12) {
      BFS(adjarr, n);
      scanf("%d", &c);
    } else if(c == 13) {
      TopologicalSorting(adjarr, n);
      scanf("%d", &c);
    } else if(c == 14) {
      StronglyConnectedComponents(adjarr, n);
      scanf("%d", &c);
    } else if(c == 15) {
      if(weight)
	printarr(weightarr, n, n);
      scanf("%d", &c);
    } else if(c == 16) {
      if(weight && !minus) {
	printf("\nChoose mode:\n1)vertex - vertex\n2)vertex - Everyone\n");
	scanf("%d", &c);
	if(c == 1) {
	  int f, l;
	  printf("Enter start vertex: ");
	  scanf("%d", &f);
	  printf("Enter last vertex: ");
	  scanf("%d", &l);
	  Dijkstra(adjarr, weightarr, n, f, l);	  
	} else {
	  int f, i;
	  printf("Enter start vertex: ");
	  scanf("%d", &f);
	  for(i=0;i<n;i++)
	    Dijkstra(adjarr, weightarr, n, f, i+1);
	}	
      } else if(!weight) {
	printf("only graph with weighted edges\n");
      } else if(minus) {
	printf("no negative edges!");
      }
      scanf("%d", &c);
    } else if(c == 17) {
      if(weight) {
	printf("\nChoose mode:\n1)vertex - vertex\n2)vertex - Everyone\n");
	scanf("%d", &c);
	if(c == 1) {
	  int f, l;
	  printf("Enter start vertex: ");
	  scanf("%d", &f);
	  printf("Enter last vertex: ");
	  scanf("%d", &l);
	  BelmanFord(adjarr, weightarr, n, f, l);  
	} else {
	  int f;
	  printf("Enter start vertex: ");
	  scanf("%d", &f);
	  BelmanFord(adjarr, weightarr, n, f, 0);
	}  
      } else
	printf("only graph with weighted edges\n");
	scanf("%d", &c);
    } else if(c == 18) {
      int f, l;
      printf("Enter start vertex: ");
      scanf("%d", &f);
      printf("Enter last vertex: ");
      scanf("%d", &l);
      FloydWarshall(adjarr, weightarr, n, f, l);
      scanf("%d", &c);
    } else if(c == 19) {
      Johnson(adjarr, weightarr, n);
      scanf("%d", &c);
    } else if(c == 20) {
      Euler(adjarr, n, m);
      scanf("%d", &c);
    } else if(c == 21) {
      Hamilton(adjarr, n);
      scanf("%d", &c);
    } else if(c == 22) {
      Color(adjarr, n);
      scanf("%d", &c);
    } else if(c == 23) {
      Prim(adjarr, weightarr, n);
      scanf("%d", &c);
    } else if(c == 24) {
      FordFalcerson(adjarr, weightarr, n);
      scanf("%d", &c);
    } else if(c == 99)
      return 0;
    else {
      ;
    }
  }
  return 0;
}
