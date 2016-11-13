#pragma once
#include <atomic>
#include <windows.h>

class barrier {

	std::atomic_int waitingThreadCounter;	//Number of threads that are waiting

	LONG maxNumOfThreads;	//Number of threads that barrier is waiting, when the last come to barrier it "fall down" 

	HANDLE allThreadsWaiting;	//Event for the last thread came to barrier

public:

	barrier(int maxN);

	void finish();	// Thread came to barrier
};