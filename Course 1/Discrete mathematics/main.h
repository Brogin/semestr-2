#ifndef DISCRETE_MAIN_HEAD
#include <stdio.h>
#include <stdlib.h>
#define DISCRETE_MAIN_HEAD
#define true 1
#define false !true
#define MIN(x, y) ((x) < (y)) ? (x) : (y)
typedef int bool;

//lab1.c
void printmenu(int num, int argc, char* argv[]);
int* arrpow(int* arr, int n, bool mode, int ret);
int arrpowtrail(int* arr, int n);
void printarr(int* arr, int n, int m);
//lab2.c
int* arrmulti(int* arr, int* arrs, int n);
int* arrdistance(int* arr, int n, bool mode);
void metric(int* arr, int n);
void isoleafver(int* arr, int* arrs, int n);
int* floyd_warshall(int* arr, int n, bool mode);
//lab3.c
void printlist(int* arr, int n);
void cycle(int* arr, int n);
int printcycle(int* arr, int n);
int Connectivity(int* arr, int* adjarr, int n, int m);
//lab4.c
typedef struct DFSStack dStack;
typedef struct DFSNode dNode;

struct DFSNode {
  int value;
  dNode* next;
};
struct DFSStack {
  int _size;
  dNode* Head;
};

void DFS(int* arr, int n);
//void DFS(int* arr, dStack* ds, int dfsnum, int n, int m, int* cache);
void DFSRR(int* arr, dStack* ds, int dfsnum, int n, int m, int* cache);
void Spush(dStack* D, int c);
int Sempty(dStack* D);
int Spop(dStack* D);
void Sprint(dStack* D);
//
typedef struct QNode Node;
typedef struct MyQueue Queue;

struct QNode {
  int value;
  Node* next;
};
struct MyQueue {
  int _size;
  Node* Head;
  Node* Tail;
};

void Qprint(Queue* Q);
int Qempty(Queue* Q);
int Qsize(Queue* Q);
void Qpush(Queue* Q, int v);
int Qpop(Queue* Q);
void Qprint(Queue* Q);
void BFS(int* arr, int n);
//lab 5
void TopologicalSorting(int* arr, int n);
void DFSR(int* arr, int* curr, int n, int m, int* cache, int* sort);
//lab 6
void StronglyConnectedComponents(int* arr, int n);
void DFSL(int* arr, int n, int* cache, int* comp, int mode);
void DFSRl(int* arr, int n, int i, int* t, int* cache, int* comp, int mode);

void transposing(int* arr, int* tarr, int n);
//lab 7
void Dijkstra(int* adjarr, int* weightarr, int n, int f, int l);
int Dijkstraint(int* adjarr, int* weightarr, int n, int f, int l);
//lab 8
void BelmanFord(int* adjarr, int* weightarr, int n, int f, int l);
int* BelmanFordint(int* adjarr, int* weightarr, int n, int f, int l);
//lab 9
void FloydWarshall(int* adfarr, int* weightarr, int n, int f, int l);
void Johnson(int* adjarr, int* weightarr, int n);
//lab 10
void Euler(int* adjarr, int n, int m);
//lab 11
void Hamilton(int* adjarr, int n);
//lab 12
void Color(int* adjarr, int n);
//lab 13
void Prim(int* adjarr, int* weightarr, int n);
//lab 14
void FordFalcerson(int* adjarr, int* weightarr, int n);
#endif
