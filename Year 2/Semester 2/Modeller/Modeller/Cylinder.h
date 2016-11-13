#pragma once
#include <GL\freeglut.h>
#include <math.h>
#include "Light.h"
#include "Shape.h"
class Cylinder: public Shape  {
public:
	Cylinder(GLdouble*);
	void Render(GLdouble* globalMatrix, int i);

private:
	float radius = 0.8;
	float height = 0.8;
};