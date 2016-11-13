#include <iostream>
#include "Stack.h"

using namespace std;

int main()
{
Stack<int> mas;
for(int i = 0; i < 1000000; i++)
	mas.push(i);
mas.show();
system("pause");
return 0;
}