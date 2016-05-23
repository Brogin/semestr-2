#include "main.h"

void BFS(int* arr, int n) {
  int c, m=0, i=0;
  Queue bq = {0, 0, 0};
  int cache[n];
  for(i=0;i<n;i++)
    cache[i] = 0;
  cache[0] = 1;
  printf("%6s\t%7s\t%5s\n","Vertex","BFS-num","Queue");
  while(1) {
  while(1) {
    printf("%c\t%d\t",(m<n)?(m+97):(m/n+97),i+1-n);
    for(c=0;c<n;c++) {
      if(arr[m+c] && !cache[c]) {
	Qpush(&bq, c);
	cache[c] = 1;
      }
    }
    if(Qempty(&bq))
      break;
    else {
      Qprint(&bq);
      m = Qpop(&bq)*n;
    }
    i++;
  }
  printf("\n");
    if(i+1-n != n){
      for(m=0;m<n;m++) {
	if(!cache[m]) {
	  cache[m] = 1;
	  m++;
	  i++;
	  printf("--- next segment ---\n");
	  break;
	}
      }
    } else
      break;
  }
}

int Qempty(Queue* Q) {
  return(!Q->Head);
}

int Qsize(Queue* Q) {
  return Q->_size;
}

void Qpush(Queue* Q, int v) {
  Node* T = (Node*) malloc (sizeof(Node*));
  T->value = v;
  if(!Qsize(Q))
    Q->Head = T;
  else
    Q->Tail->next = T;
  (Q->_size)++;
  Q->Tail = T;
}

int Qpop(Queue* Q) {
  int v;
  if(Qempty(Q))
    return 0;
  (Q->_size)--;
  Node* T = Q->Head;
  if(Q->Head == Q->Tail)
    Q->Head = Q->Tail = 0;
  else
    Q->Head = Q->Head->next;
  v = T->value;
  T->value = 0;
  T->next = 0;
  free(T);
  return v;
}

void Qprint(Queue* Q) {
  Node* T;
  for(T=Q->Head;T!=0;T=T->next)
    printf("%c%s",T->value+97,(T->next)?" ":"\n");
}

void DFS(int* arr, int n) {
  int c, i, dfsnum = 0;
  dStack ds = {0, 0};
  int cache[n];
  for(i=0;i<n;i++)
    cache[i] = 0;
  printf("number of the vertex (1-%d): ",n);
  scanf("%d",&c);
  Spush(&ds, c-1);
  cache[c-1] = 1;
  printf("%6s\t%7s\t%5s\n","Vertex","DFS-num","Stack");
  while(!Sempty(&ds)) {
    c = Spop(&ds);
    printf("%c\t%d\t",(c<n)?(c+97):(c/n+97),dfsnum+1);
    for(i=n;i!=-1;i--) {
      if(arr[c*n+i] && !cache[i]) {
	dfsnum++;
	cache[i] = 1;
	Spush(&ds, i);
      } 
    }
    Sprint(&ds);
  }
}

void DFSRR(int* arr, dStack* ds, int dfsnum, int n, int m, int* cache) {
  int c;
  /*int c, i=0;
  dStack ds = {0, 0};
  int cache[n];
  for(i=0;i<n;i++)
    cache[i] = 0;*/
  cache[m/n] = 1;
  if(!dfsnum)
    printf("%6s\t%7s\t%5s\n","Vertex","DFS-num","Stack");
  //while(1) {
    while(!Sempty(ds)) {
      m = Spop(ds)*n;
      printf("%c\t%d\t",(m<n)?(m+97):(m/n+97),dfsnum+1);
      for(c=0;c<n;c++) {
	if(arr[m+c] && !cache[c]) {
	  Spush(ds, c);
	  cache[c] = 1;
	}
      }
      //if(Sempty(&ds))
      //	break;
      // else {
	Sprint(ds);
	//m = Spop(ds)*n;
	//DFS(arr, ds, dfsnum+1, n, m, cache);
	//}
      //i++;
    }/*
    printf("\n");
    if(i+1-n != n){
      for(m=0;m<n;m++) {
	if(!cache[m]) {
	  cache[m] = 1;
	  m++;
	  i++;
	  printf("--- next segment ---\n");
	  break;
	}
      }
    } else
    break;*/
    //}
}

void Spush(dStack* D, int c) {
  (D->_size)++;
  dNode* T = (dNode*) malloc (sizeof(dNode));
  T->value = c;
  T->next = 0;
  if(D->_size > 0)
    T->next = D->Head;
  D->Head = T;
}

int Sempty(dStack* D) {
  return (!D->Head);
}

int Spop(dStack* D) {
  int m;
  if(Sempty(D))
    return 0;
  (D->_size)--;
  dNode* T = D->Head;
  D->Head = D->Head->next;
  T->next = 0;
  m = T->value;
  T->value = 0;
  free(T);
  return m;
}

void Sprint(dStack* D) {
  dNode* T;
  for(T=D->Head;T!=0;T=T->next)
    printf("%c%s",T->value+97,(T->next)?" ":"\n");
}
