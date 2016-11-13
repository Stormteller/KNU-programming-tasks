#include "stdafx.h"
#include "Shape.h"

Shape::Shape(GLdouble* M)
{
	for (int i = 0; i < 4; i++)
		for (int t = 0; t < 4; t++)
			Matrix[4 * i + t] = M[4 * i + t];
}

void Shape::Shift(float dx, float dy, float dz)
{
	dx *= 1.2 + totalSaveShiftZ/7.65;
	dy *= 1.2 + totalSaveShiftZ/7.65;
	totalSaveShiftX += dx;
	totalSaveShiftY += dy;
	totalSaveShiftZ += dz;
	totalShiftX += dx;
	totalShiftY += dy;
	totalShiftZ += dz;
}

void Shape::RotateLocal(float dx, float dy, float dz)
{
	localAngelX -= dx;
	localAngelY -= dy;
	localAngelZ -= dz;
}

void Shape::RotateTotal(float dx, float dy, float dz)
{
	totalSaveAngelX -= dx;
	totalSaveAngelY -= dy;
	totalSaveAngelZ -= dz;
	totalAngelX -= dx;
	totalAngelY -= dy;
	totalAngelZ -= dz;
}

void Shape::Scale(float k)
{
	scale += k;
}

void Shape::savePos() {
	totalSaveAngelX = totalAngelX;
	totalSaveAngelY = totalAngelY;
	totalSaveAngelZ = totalAngelZ;
	totalSaveShiftX = totalShiftX;
	totalSaveShiftY = totalShiftY;
	totalSaveShiftZ = totalShiftZ;
}

float Shape::getLocalAngelX() {
	return localAngelX;
};

float Shape::getLocalAngelY() {
	return localAngelY;
};

float Shape::getLocalAngelZ() {
	return localAngelZ;
};

float Shape::getTotalSaveAngelX() {
	return totalSaveAngelX;
};

float Shape::getTotalSaveAngelY() {
	return totalSaveAngelY;
};

float Shape::getTotalSaveAngelZ() {
	return totalSaveAngelZ;
};

float Shape::getTotalSaveShiftX() {
	return totalSaveShiftX/(1.2 + totalSaveShiftZ / 7.65);
};

float Shape::getTotalSaveShiftY() {
	return totalSaveShiftY/(1.2 + totalSaveShiftZ / 7.65);
};

float Shape::getTotalSaveShiftZ() {
	return totalSaveShiftZ;
};

float Shape::getScale() {
	return scale;
};

unsigned char Shape::getType() {
	return type;
}