#include <fstream>
#include <iostream>

using namespace std;

const float EPS = 0.001f;

class Vertex {
	float x;
	float y;
public:
	Vertex* next;
	Vertex* prev;
	Vertex(float, float);
	float getX();
	float getY();
};

class Polygon {
	Vertex* head;
	int len;
public:
	Polygon();
	void push(float, float);
	Vertex remove(Vertex*);
	Vertex pop(float, float);
	Vertex* getHead();
	int length();
};

Vertex* Polygon::getHead() {
	return this->head;
}

Vertex::Vertex(float x, float y) {
	next = NULL;
	prev = NULL;
	this->x = x;
	this->y = y;
}

float Vertex::getX() {
	return this->x;
}

float Vertex::getY() {
	return this->y;
}

Polygon::Polygon() {
	len = 0;
	head = NULL;
}

void Polygon::push(float x, float y) {
	Vertex *newVert = new Vertex(x, y);
	if (head) {
		newVert->next = head;
		newVert->prev = head->prev;
		head->prev->next = newVert;
		head->prev = newVert;
	}
	else {
		newVert->next = newVert;
		newVert->prev = newVert;
	}
	head = newVert;
	len++;
}

Vertex Polygon::remove(Vertex* toDel) {
	len--;
	bool isHead;
	Vertex deleted(toDel->getX(), toDel->getY());
	toDel == head ? isHead = true : isHead = false;

	Vertex* prevDel = toDel->prev;
	Vertex* nextDel = toDel->next;
	if (nextDel == toDel) {
		delete head;
		head = NULL;
	}
	else {
		prevDel->next = nextDel;
		nextDel->prev = prevDel;
		delete toDel;
		isHead ? head = nextDel : 0;
	}
	return deleted;
}

Vertex Polygon::pop(float x, float y) {
	Vertex *curr = head;
	do {
		if (fabs(curr->getX() - x) <= EPS && fabs(curr->getY() - y) <= EPS) {
			return remove(curr);
		}
	} while(curr != head);
	cout << "Not found" << endl;
	return Vertex(0, 0);
}

int Polygon::length() {
	return len;
}

float distance(Vertex v1, Vertex v2) {
	return sqrt((v2.getX() - v1.getX()) * (v2.getX() - v1.getX()) + (v2.getY() - v1.getY()) * (v2.getY() - v1.getY()));
}

double triagulate(Polygon &polygon) {
	if (polygon.length() < 4) return 0;
	Vertex *curr = polygon.getHead();
	float min_diag = 9999999;

	Vertex *toDel = NULL;

	do {
		float dist = distance(curr, curr->next->next);
		if (dist < min_diag) {
			min_diag = dist;
			toDel = curr->next;
		}
		curr = curr->next;
	} while (curr != polygon.getHead());
	cout << "( " << toDel->prev->getX() << " , " << toDel->prev->getY() << " ) " << "( " << toDel->next->getX() << " , " << toDel->next->getY() << " ) " << endl;
	polygon.remove(toDel);
	return min_diag + triagulate(polygon);
}

int main() {
	ifstream fin("input.txt");
	float x, y;
	Polygon polygon;
	while (fin >> x >> y) {
		polygon.push(x, y);
	}

	triagulate(polygon);
	system("pause");
	return 0;
}