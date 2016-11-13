#include "barrier.h"

barrier::barrier(int maxN) {
	this->maxNumOfThreads = maxN;
	this->waitingThreadCounter.store(0);
	this->allThreadsWaiting = CreateEvent(NULL, TRUE, FALSE, NULL);;
}

//Thread came to barrier
void barrier::finish() {
	ResetEvent(allThreadsWaiting);
	int readyThreadCount = waitingThreadCounter++;	//Increase number of threads
	
	//If all threads came to barrier
	if (readyThreadCount >= maxNumOfThreads - 1) {
		waitingThreadCounter.store(0);	//Reset counter
		SetEvent(allThreadsWaiting);	//Resume threads work
	}
	//Else wait the last thread
	else {
		WaitForSingleObject(allThreadsWaiting, INFINITE);
	}
}