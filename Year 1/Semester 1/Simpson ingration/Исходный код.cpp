#include "cmath"
#include "iostream"

using namespace std;




double rectangle(double(*function)(double),double a, double b, int n)
{

	double h, i, value = 0;

	h = (b - a) / n;

	for (i = a + h / 2; i<b; i += h)
		value += function(i)*h;

	return value;
}


double trapezoid(double(*function)(double), double a, double b, int n)
{
	double h, i, value = 0;

	h = (b - a) / n;

	for (i = a; i<b - h / 2; i += h)
		value += h*(function(i) + function(i + h)) / 2;

	return value;
}

double Simpsons(double(*function)(double),double a, double b, int n)
{

	double h, i, value = 0;

	h = (b - a) / n;

	for (i = a; i<b - h / 2; i += h)
		value += h*(function(i) + 4 * function(i + h / 2) + function(i + h)) / 6;

	return value;
}


double function(double x)
{

	return x*x*x;
}



int main()
{
	setlocale(LC_ALL, "Russian");
	double a, b, n, eps = 0.001;
	cout << "Введите границы интегрирования" << endl;
	cin >> a >> b;
	cout << "Введите точность (например 0.001)" << endl;
	cin >> eps;
	double(*func)(double);
	func = function;
	n = 3;
	while (fabs(rectangle(func,a, b, n + 2) - rectangle(func,a, b, n))>eps)
		n *= 2;
	cout << "Метод прямоугольников: " << rectangle(func,a, b, n) << endl;
	cout << "Количетсво точек нужных для вычисление интеграла: " << n << endl;

	n = 3;
	while (fabs(trapezoid(func,a, b, n + 2) - trapezoid(func,a, b, n))>eps)
		n *= 2;
	cout << "Метод трапеций: " << trapezoid(func,a, b, n) << endl;
	cout << "Количетсво точек нужных для вычисление интеграла: " << n << endl;

	n = 3;
	while (fabs(Simpsons(func,a, b, n + 2) - Simpsons(func,a, b, n))>eps)
		n *= 2;
	cout << "Метод Симпсона: " << Simpsons(func,a, b, n) << endl;
	cout << "Количетсво точек нужных для вычисление интеграла: " << n << endl;


	system("pause");
	return 0;
}
