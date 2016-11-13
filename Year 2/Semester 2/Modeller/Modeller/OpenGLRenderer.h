#pragma once
#include <GL\freeglut.h>
#include <math.h>
#include <vector>
#include "Shape.h"
#include "Cylinder.h"
#include "Light.h"
using namespace std;
class COpenGLRenderer
{
protected:
	int Width, Height;
	GLdouble globalMatrix[16];
	vector<Shape*> shape;
	Shape* selectedObj=nullptr;
public:
	int prevX = -1;
	int prevY = -1;

	bool mainAxises=true;
	COpenGLRenderer();
	~COpenGLRenderer();
	void clearMatrix();
	vector<Shape*>& getShapes();
	void addShape(byte a, float x, float y);
	void Shift(float dx, float dy, float dz);
	void RotateLocal(float dx, float dy, float dz);
	void RotateTotal(float dx, float dy, float dz);
	void Scale(float k);
	void Select(float x, float y);
	void saveSelectedPos();
	bool Init();
	void Render(float FrameTime = 0);
	void Resize(int Width, int Height);
	void Destroy();
};