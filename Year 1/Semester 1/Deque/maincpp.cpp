#include <iostream>
#include "queue.h"

using namespace std;

int main()
{
	TwoSidesQueue<int> twoSidesQueue;
	for(int i = 0; i < 10; i++) {
		twoSidesQueue.PushHead(i);
		twoSidesQueue.PushTail(-i);
	};
	twoSidesQueue.Print();
	for(int i = 0; i < 5; i++) {
		twoSidesQueue.PopHead();
		twoSidesQueue.PopTail();
	};
	twoSidesQueue.Print();
	system("pause");
	return 0;
}