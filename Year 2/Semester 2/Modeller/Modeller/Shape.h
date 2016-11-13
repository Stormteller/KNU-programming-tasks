#pragma once
#include <GL\freeglut.h>
class Shape {
public: Shape(GLdouble* M);
	virtual void Render(GLdouble* M, int i) {}
	void Shift(float dx, float dy, float dz);
	void RotateLocal(float dx, float dy, float dz);
	void RotateTotal(float dx, float dy, float dz);
	void Scale(float k);
	void savePos();

	float getLocalAngelX();
	float getLocalAngelY();
	float getLocalAngelZ();

	float getTotalSaveAngelX();
	float getTotalSaveAngelY();
	float getTotalSaveAngelZ();
	float getTotalSaveShiftX();
	float getTotalSaveShiftY();
	float getTotalSaveShiftZ();
	byte getType();
	float getScale();
protected:
	float localAngelX = 0;
	float localAngelY = 0;
	float localAngelZ = 0;


	float totalAngelX = 0;
	float totalAngelY = 0;
	float totalAngelZ = 0;
	float totalShiftX = 0;
	float totalShiftY = 0;
	float totalShiftZ = 0;

	float totalSaveAngelX = 0;
	float totalSaveAngelY = 0;
	float totalSaveAngelZ = 0;
	float totalSaveShiftX = 0;
	float totalSaveShiftY = 0;
	float totalSaveShiftZ = 0;

	float scale = 1;
	byte type;
	GLdouble Matrix[16];
};