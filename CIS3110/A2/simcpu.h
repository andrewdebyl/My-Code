#include <stdio.h>

struct thread
{
	int processNum;
	int threadNum;
	int arriveTime;
	int totalBursts;
	int nextBurst;
	int** bursts;
	int totalIO;
	int totalCPU;
	int startTime;
	int finishTime;
	int entryTime;
	int started;
};
typedef struct thread Thread;

void buildMinHeap (Thread** queue, int size);
Thread* deleteRoot(Thread **queue, int* size);
void heapify(Thread** queue, int size, int i);
void swap(Thread **a, Thread **b);
Thread** fcfs (Thread** queue, int size, int switchSame, int switchDiff);
double getTime(Thread** terminated, int size);
Thread** rr (Thread** queue, int size, int switchSame, int switchDiff, int quantum);
double cpuUtil (Thread** queue, int size);
int getThreadTime(Thread* thread, int n);