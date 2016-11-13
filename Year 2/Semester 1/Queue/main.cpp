#include "queue.h"
#include <time.h>

using namespace std;

int main() {
	srand(time(0));
	Queue queue1;
	Queue queue2;
	for (int i = 0; i < 500; i++) {
		queue1.push((i + rand()) % 100);
		queue2.push((i + rand()) % 100);
	}
	queue1.print();
	clock_t time = clock();
	queue1.qSort(0, queue1.length() - 1);
	time = clock() - time;
	cout << endl << "Time: " << (float)time / CLOCKS_PER_SEC << endl;
	queue1.print();


	queue2.print();
	time = clock();
	queue2.insSort();
	time = clock() - time;
	cout << endl << "Time: " << (float)time / CLOCKS_PER_SEC << endl;
	queue2.print();

	system("pause");
	return 0;
};