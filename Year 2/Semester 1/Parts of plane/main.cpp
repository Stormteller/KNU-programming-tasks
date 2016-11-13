#include <iostream>
#include <fstream>
#include <vector>

using namespace std;

struct Point {
	int x, y;

	Point(int x = 0, int y = 0) {
		this->x = x;
		this->y = y;
	}
};

struct Rect {
	Point topLeft;
	Point botRight;

	Rect(Point topLeft, Point botRight) {
		this->botRight = botRight;
		this->topLeft = topLeft;
	}
};

int main() {
	ifstream fin("input.txt");
	int x1, y1, x2, y2;
	vector<Rect> rects;
	while (fin >> x1 >> y1 >> x2 >> y2) {
		rects.push_back( Rect( Point(x1, y1), Point(x2, y2) ) );
	}


	system("pause");
	return 0;
}