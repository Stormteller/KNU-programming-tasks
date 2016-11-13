#pragma once
int pluss(int, int);


/*struct point
{
	int x, y;
};*/
struct point
{
	int x, y;
	point()
	{
	x=0;
	y=0;
	}
	point(int X, int Y)
	{
		x = X;
		y = Y;
	}
};

double dist(const point &a, const point &b);
bool operator != (const point &a, const point &b);
double CosAngle(const point &prev, const point &cur, const point &next);
bool Less(const double &a, const double &b);
bool More(const double &a, const double &b);
bool Equal(const double &a, const double &b);
double Fabs(const double &a);
