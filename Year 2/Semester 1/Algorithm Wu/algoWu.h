#pragma once
#include <windows.h>

//Drawing by Wu method
class algoWuEllipse
{
	float xRadius;	//x-axis radius
	float yRadius;	//y-axis radius
	float xCenter;	//ellipse center y coordinate 
	float yCenter;	//ellipse center y coordinate

	void drawPoint (HDC, int, int, COLORREF, float);	//draw point color in RGB with Alpha
	void drawLineX(HDC, float, float, float, float, COLORREF);	//Draw line with smoothing by X with Wu method
	void drawLineY(HDC, float, float, float, float, COLORREF);	//Draw line with smoothing by Y with Wu method
	void drawLine(HDC, float, float, float, float, COLORREF);	//Draw line with smoothed with Wu method

public:
	algoWuEllipse(float, float, float, float);	//Params: x-coord center, y-coord center, x-axis radius, y-axis radius
	void drawEllipse(HDC, COLORREF);	//Draw ellipse with smoothed with Wu method
};
