#include <iostream>
#include <cstdio>
#include <vector>
#include <cmath>
#include "Library.h"
#include <locale>
using namespace std;



int main()
{
	setlocale(LC_ALL,"Russian");
	vector<point> mas;
	vector<point> answer;
	int n;
	cout << "Введите количество точек" << endl;
	cin >> n;
	mas.resize(n);
	cout << "Введите точки заданые координатами (пары Х и Y)" << endl;
	for (int i = 0; i < n; i++)
		cin >> mas[i].x >> mas[i].y;



	if (n != 1)
	{

		int base = 0;
		for (int i = 1; i < n; i++)
		{
			if (mas[i].y < mas[base].y)
				base = i;
			else
				if (mas[i].y == mas[base].y &&
					mas[i].x < mas[base].x)
					base = i;
		}
		answer.push_back(mas[base]);   

		point first = mas[base];
		point cur = first;
		point prev;
		prev.x = first.x - 1; prev.y = first.y;
		do
		{
			double minCosAngle = 1e9;
			double maxLen = 1e9;
			int next = -1;
			for (int i = 0; i < n; i++)
			{
				double curCosAngle = CosAngle(prev, cur, mas[i]);
				if (Less(curCosAngle, minCosAngle))
				{
					next = i;
					minCosAngle = curCosAngle;
					maxLen = dist(cur, mas[i]);
				}
				else if (Equal(curCosAngle, minCosAngle))
				{
					double curLen = dist(cur, mas[i]);
					if (More(curLen, maxLen))
					{
						next = i;
						maxLen = curLen;
					}
				}
			}
			prev = cur;
			cur = mas[next];
			answer.push_back(cur);
		} while (cur != first);

		cout << "________________________________" << endl;
		cout << "Точки которые входят в выпуклую оболочку" << endl;
		for (int i = 0; i < answer.size() - 1; i++)
		{
			cout << answer[i].x << "  " << answer[i].y << endl;
		}
	}
	else
	{
		cout << "Точки которые входят в выпуклую оболочку" << endl;
		cout << mas[0].x << "  " << mas[0].y << endl;
	}
	
	//cout << answer[0].x << answer[0].y << endl;
	system("pause");
	return 0;
}