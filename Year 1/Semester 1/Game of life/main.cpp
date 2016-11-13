#include <iostream>

using namespace std;
const int NMAX = 100;


short neighbor(short mas[NMAX][NMAX], short cell_x, short cell_y)
{
	short i = 0;
	if (mas[cell_x - 1][cell_y - 1] > 0) i++;
	if (mas[cell_x - 1][cell_y] > 0) i++;
	if (mas[cell_x][cell_y - 1] > 0) i++;
	if (mas[cell_x + 1][cell_y - 1] > 0) i++;
	if (mas[cell_x - 1][cell_y + 1] > 0) i++;
	if (mas[cell_x + 1][cell_y + 1] > 0) i++;
	if (mas[cell_x + 1][cell_y] > 0) i++;
	if (mas[cell_x][cell_y + 1] > 0) i++;
	return i;
}

void next_step(short mas1[NMAX][NMAX], short mas2[NMAX][NMAX], short cell_x, short cell_y)
{
	if (!((mas1[cell_x][cell_y]>0) && ((neighbor(mas1, cell_x, cell_y) >= 2) && (neighbor(mas1, cell_x, cell_y) <= 3)))) mas2[cell_x][cell_y] = 0;
	if ((mas1[cell_x][cell_y] == 0) && (neighbor(mas1, cell_x, cell_y) == 2)) mas2[cell_x][cell_y] = 1;

}


int main()
{ 
	int n,age;
	cin >> n;
	short matrix1[NMAX][NMAX];
	short matrix2[NMAX][NMAX];
	for (short i = 0; i < n; i++)
		for (short j = 0; j < n; j++)
		{
		cin >> matrix1[i][j];
		matrix2[i][j] = 0;
		}
	cin >> age;
	for (short k = 0; k < age; k++)
		for (short i = 0; i < n; i++)
			for (short j = 0; j < n; j++)
			{
		if (k % 2 == 0) next_step(matrix1, matrix2, i, j);
		if (k % 2 != 0) next_step(matrix2, matrix1, i, j);
			}
	if (age % 2 == 0) 
	{
		for (short i = 0; i < n; i++)
		{
			for (short j = 0; j < n; j++)
				cout << matrix1[i][j] << ' ';
			cout << endl;
		}
	}
	else {
		for (short i = 0; i < n; i++)
		{
			for (short j = 0; j < n; j++)
				cout << matrix2[i][j] << ' ';
			cout << endl;
		}
	}
	system("pause");
	return 0;
}