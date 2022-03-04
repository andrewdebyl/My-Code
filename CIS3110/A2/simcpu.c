#include <stdio.h>
#include "simcpu.h"
#include <stdlib.h>
#include <string.h>

int set=0;

void swap(Thread **a, Thread **b)
{
  	Thread* temp = *b;
  	*b = *a;
  	*a = temp;
}

void heapify(Thread** queue, int size, int i)
{
  	if (size == 1)
  	{
    	printf("Single element in the heap");
  	}
  	else
  	{
    	int largest = i;
    	int l = 2 * i + 1;
    	int r = 2 * i + 2;
    	if (l < size && queue[l]->arriveTime < queue[largest]->arriveTime)
    	{
      		largest = l;
    	}
    	if (r < size && queue[r]->arriveTime < queue[largest]->arriveTime)
    	{
      		largest = r;
    	}
    	if (largest != i)
    	{
      		swap(&queue[i], &queue[largest]);
      		heapify(queue, size, largest);
    	}
  	}
}

Thread* deleteRoot(Thread **queue, int* size)
{
  	Thread* toDelete = queue[0];

  	queue[0] = queue[(*size) - 1];

  	(*size)--;

  	buildMinHeap(queue, (*size));

  	return toDelete;
}

void buildMinHeap (Thread** queue, int size)
{
	int i;

	for (i = size / 2 - 1; i >= 0; i--)
	{
		heapify(queue, size, i);
	}
}

Thread** fcfs (Thread** queue, int size, int switchSame, int switchDiff)
{
	int currTime = 0;
	Thread** finishQueue = malloc(sizeof(Thread*));
	int finishCount = 0;

	while(size != 0)
	{
		Thread* currentThread = queue[0];

		if (currentThread->arriveTime > currTime)
		{
			currTime = currentThread->arriveTime;
		}

		if (currentThread->nextBurst==0)
		{
			if (set==1)
			{
				printf("At time %d: Thread %d of Process %d moves from new to ready\n", currTime, currentThread->threadNum, currentThread->processNum);
			}
			currentThread->startTime = currTime;
		}

		currentThread->arriveTime = currTime + (currentThread->bursts)[currentThread->nextBurst][1] + (currentThread->bursts)[currentThread->nextBurst][2];

		if (set==1)
		{
			printf("At time %d: Thread %d of Process %d moves from ready to running\n", currTime, currentThread->threadNum, currentThread->processNum);
		}

		currTime += (currentThread->bursts)[currentThread->nextBurst][1];

		currentThread->nextBurst++;

		if (currentThread->nextBurst == currentThread->totalBursts)
		{
			finishCount++;
			finishQueue = realloc(finishQueue, sizeof(Thread*) * finishCount);

			if (set==1)
			{
				printf("At time %d: Thread %d of Process %d moves from running to terminated\n",currTime, currentThread->threadNum, currentThread->processNum);
			}

			Thread* finished = deleteRoot(queue, &size);

			finished->finishTime=currTime;
			finishQueue[finishCount - 1] = finished;
		}
		else
		{
			buildMinHeap(queue, size);

			if (set==1)
			{
				printf("At time %d: Thread %d of Process %d moves from running to blocked\n",currTime, currentThread->threadNum, currentThread->processNum);
				printf("\n");
			}
		}

		if (size > 0)
		{
			if (queue[0]->processNum == currentThread->processNum)
			{
				currTime+=switchSame;
			}
			else
			{
				currTime+=switchDiff;
			}
		}
	}

	return finishQueue;
}

Thread** rr (Thread** queue, int size, int switchSame, int switchDiff, int quantum)
{
	int currTime = 0;
	Thread** finishQueue = malloc(sizeof(Thread*));
	int finishCount = 0;

	while(size != 0)
	{
		Thread* currentThread = queue[0];

		if (currentThread->arriveTime > currTime)
		{
			currTime = currentThread->arriveTime;
		}

		if (currentThread->started == 0)
		{
			currentThread->startTime = currTime;
			if (set == 1)
			{
				printf("At time %d: Thread %d of Process %d moves from new to ready\n", currTime, currentThread->threadNum, currentThread->processNum);
			}
		}

		currentThread->started=1;

		if (set==1)
		{
			printf("At time %d: Thread %d of Process %d moves from ready to running\n", currTime, currentThread->threadNum, currentThread->processNum);
		}

		if ((currentThread->bursts)[currentThread->nextBurst][1] > quantum)
		{
			(currentThread->bursts)[currentThread->nextBurst][1] -= quantum;
			currentThread->arriveTime = currTime + quantum;

			currTime+=quantum;
		}
		else
		{
			currentThread->arriveTime = currTime + (currentThread->bursts)[currentThread->nextBurst][1] + (currentThread->bursts)[currentThread->nextBurst][2];

			currTime += (currentThread->bursts)[currentThread->nextBurst][1];

			currentThread->nextBurst++;
		}

		if (currentThread->nextBurst == currentThread->totalBursts)
		{
			finishCount++;
			finishQueue = realloc(finishQueue, sizeof(Thread*) * finishCount);

			Thread* finished = deleteRoot(queue, &size);

			if (set == 1)
			{
				printf("At time %d: Thread %d of Process %d moves from running to terminated\n",currTime, currentThread->threadNum, currentThread->processNum);
			}

			finished->finishTime=currTime;

			finishQueue[finishCount - 1] = finished;
		}
		else
		{
			buildMinHeap(queue, size);
			if (set == 1)
			{
				printf("At time %d: Thread %d of Process %d moves from running to blocked\n",currTime, currentThread->threadNum, currentThread->processNum);
				printf("\n");
			}
		}

		if (size > 0)
		{
			if (queue[0]->processNum == currentThread->processNum)
			{
				if (queue[0]->threadNum != currentThread->threadNum)
				{
					currTime+=switchSame;
				}
			}
			else
			{
				currTime+=switchDiff;
			}
		}
	}

	return finishQueue;
}

double getTime(Thread** terminated, int size)
{
	double avgTime = 0;
	int i;

	for (i=0; i<size; i++)
	{
		avgTime += terminated[i]->finishTime - terminated[i]->entryTime;
	}

	return avgTime/size;
}

double cpuUtil (Thread** queue, int size)
{
	int i;
	double total=0;

	for (i=0; i<size; i++)
	{
		total += getThreadTime(queue[i], 1);
	}

	return (total/queue[size-1]->finishTime)*100;
}

int getThreadTime(Thread* thread, int n)
{
	int total=0,i;

	for (i=0; i<thread->totalBursts; i++)
	{
		total+=(thread->bursts)[i][n];
	}
	return total;
}

int main (int argc, char* argv[])
{
	char line[50];
	int totalProcess, switchSame, switchDiff, i, currentProcess, numThreads, k,j, totalThreads=0;
	Thread** readyQueue = malloc(sizeof(Thread*));

	fgets(line,50, stdin);
	
	sscanf(line, "%d %d %d\n", &totalProcess, &switchSame, &switchDiff);
	
	for(i = 0; i < totalProcess; i++)
	{
		fgets(line, 50, stdin);
		sscanf(line, "%d %d\n", &currentProcess, &numThreads);

		for (j = 0; j < numThreads; j++)
		{
			totalThreads++;

			readyQueue = realloc(readyQueue, sizeof(Thread*) * totalThreads);

			Thread* thread = malloc(sizeof(Thread));

			thread->processNum = currentProcess;
			thread->nextBurst = 0;
			thread->totalIO = 0;
			thread->totalCPU = 0;
			thread->finishTime = 0;
			thread->started = 0;

			fgets(line, 50, stdin);

			sscanf(line, "%d %d %d\n", &thread->threadNum, &thread->arriveTime, &thread->totalBursts);
			thread->entryTime = thread->arriveTime;

			thread->bursts = malloc(sizeof(int*) * thread->totalBursts);

			for (k=0; k < thread->totalBursts; k++)
			{
				thread->bursts[k] = malloc(sizeof(int) * 3);

				fgets(line, 50, stdin);

				sscanf(line, "%d %d %d\n", &thread->bursts[k][0], &thread->bursts[k][1], &thread->bursts[k][2]);
			}

			readyQueue[totalThreads-1] = thread;
		}
	}
	
	buildMinHeap(readyQueue,totalThreads);

	if (argc == 1)
	{
		printf("FCFS Scheduling\n");
		Thread** terminated = fcfs(readyQueue, totalThreads, switchSame, switchDiff);
		printf("Total Time required is %d units\n", terminated[totalThreads-1]->finishTime);
		printf("Average Turnaround Time is %.1lf units\n", getTime(terminated, totalThreads));
		printf("CPU Utilization is %.1lf%%\n",cpuUtil(terminated, totalThreads));
		exit(-1);
	}

	int a, d=0,v=0,r=0;
	for (a=1; a<argc; a++)
	{
		if (strcmp(argv[a], "-d")==0)
		{
			d=1;
		}
		if (strcmp(argv[a], "-v")==0)
		{
			v=1;
		}
		if (strcmp(argv[a], "-r")==0)
		{
			r=1;
		}
	}

	if (r == 1)
	{
		int q = atoi(argv[argc-1]);

		if (v == 1)
		{
			set=1;
		}

		Thread** terminated = rr(readyQueue,totalThreads,switchSame,switchDiff, q);

		if (d == 1 || v == 1)
		{
			printf("Round Robin Scheduling (quantum = %d time units)\n", q);
			printf("Total Time required is %d units\n", terminated[totalThreads-1]->finishTime);
			printf("Average Turnaround Time is %.1lf units\n", getTime(terminated, totalThreads));
			printf("CPU Utilization is %.1lf%%\n",cpuUtil(terminated, totalThreads));

			for (i=0; i < totalThreads; i++)
			{
				printf("Thread %d of Process %d\n", terminated[i]->threadNum, terminated[i]->processNum);
				printf(" arrival time: %d\n", terminated[i]->entryTime);
				printf(" service time: %d units, I/O time: %d units, turnaround time: %d units, finish time: %d units\n",getThreadTime(terminated[i],1), getThreadTime(terminated[i],2), terminated[i]-> finishTime - terminated[i]->entryTime,terminated[i]->finishTime);
			}
		}
		else
		{
			printf("Round Robin Scheduling (quantum = %d time units)\n", q);
			printf("Total Time required is %d units\n", terminated[totalThreads-1]->finishTime);
			printf("Average Turnaround Time is %.1lf units\n", getTime(terminated, totalThreads));
			printf("CPU Utilization is %.1lf%%\n",cpuUtil(terminated, totalThreads));
		}
	}
	else
	{
		if (v == 1)
		{
			set=1;
		}

		Thread** terminated = fcfs(readyQueue, totalThreads, switchSame, switchDiff);

		if (d == 1 || v == 1)
		{
			printf("FCFS Scheduling\n");
			printf("Total Time required is %d units\n", terminated[totalThreads-1]->finishTime);
			printf("Average Turnaround Time is %.1lf units\n", getTime(terminated, totalThreads));
			printf("CPU Utilization is %.1lf%%\n",cpuUtil(terminated, totalThreads));

			for (i=0; i < totalThreads; i++)
			{
				printf("Thread %d of Process %d\n", terminated[i]->threadNum, terminated[i]->processNum);
				printf(" arrival time: %d\n", terminated[i]->entryTime);
				printf(" service time: %d units, I/O time: %d units, turnaround time: %d units, finish time: %d units\n",getThreadTime(terminated[i],1), getThreadTime(terminated[i],2), terminated[i]-> finishTime - terminated[i]->entryTime,terminated[i]->finishTime);
			}
		}
	}

	return 0;
}