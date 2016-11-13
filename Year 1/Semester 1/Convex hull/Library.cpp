#include "Library.h"
#include <cmath>

int pluss(int a, int b)
{ return a + b;  }

bool operator != (const point &a, const point &b)
{
	return !(a.x == b.x && a.y == b.y);
}
double dist(const point &a, const point &b)
{
	return sqrt(0.0 + (a.x - b.x) * (a.x - b.x) + (a.y - b.y) * (a.y - b.y));
}

double Fabs(const double &a)
{
	if (a<0)
		return -a;
	return a;
}
bool Equal(const double &a, const double &b)
{
	return Fabs(a - b) <= 1e-8;
}
bool More(const double &a, const double &b)
{
	return !Equal(a, b) && a > b;
}
bool Less(const double &a, const double &b)
{
	return !Equal(a, b) && a < b;
}
double CosAngle(const point &prev, const point &cur, const point &next)
{
	point v1;
	v1.x = next.x - cur.x;
	v1.y = next.y - cur.y;
	point v2;
	v2.x = prev.x - cur.x;
	v2.y = prev.y - cur.y;
	return (v1.x * v2.x + v1.y * v2.y) / (dist(prev, cur) * dist(cur, next));
}