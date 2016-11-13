#include "algoWu.h"
#include <algorithm>
#include <math.h>

//Params: x-coord center, y-coord center, x-axis radius, y-axis radius
algoWuEllipse::algoWuEllipse(float centerX, float centerY, float radiusX, float radiusY) {
	xCenter = centerX;
	yCenter = centerY;
	xRadius = radiusX;
	yRadius = radiusY;
}

//draw point color in RGB with Alpha
void algoWuEllipse::drawPoint(HDC hDC, int x, int y, COLORREF color, float alpha) {
	//Recalculating colors ñonsider alpha coef
	//ResultColor = Background * (1 - Alpha) + Foreground * Alpha

	//Get R, G, B components of foreground color
	int foregroundR = color & 0b1111'1111;
	int foregroundG = (color >> 8) & 0b1111'1111;
	int foregroundB = (color >> 16) & 0b1111'1111;
	
	//Get R, G, B components of background color
	COLORREF backgoundColor = GetPixel(hDC, x, y);
	int backgroundR = backgoundColor & 0b1111'1111;
	int backgroundG = (backgoundColor >> 8) & 0b1111'1111;
	int backgroundB = (backgoundColor >> 16) & 0b1111'1111;

	//Recalculating new pixel color ñonsider alpha coef
	int currR = backgroundR * (1 - alpha) + foregroundR * alpha;
	int currG = backgroundG * (1 - alpha) + foregroundG * alpha;
	int currB = backgroundB * (1 - alpha) + foregroundB * alpha;

	COLORREF currColor = RGB(currR, currG, currB);
	SetPixel(hDC, x, y, currColor);
}

//Draw line with smoothing by X with Wu method
void algoWuEllipse::drawLineX(HDC hDC, float x1, float y1, float x2, float y2, COLORREF color) {
	/*
	Draw point in 2 pixels where brightness of pixel color depends on real line point coordinates closer to center of pixel.
	Brightness divide in percentage ratio, real point closer - pixel brighter. Max brightness - 1.
	*/

	if (x2 < x1) {
		std::swap(x1, x2);
		std::swap(y1, y2);
	}

	//function increament x-axis
	float dx = x2 - x1;
	float dy = y2 - y1;
	float gradient = dy / dx;
	
	//Start point
	float xStart = round(x1);
	float yStart = y1 + gradient * (xStart - x1);

	float intPart;
	float xGapStart = 1 - modf(x1 + 0.5, &intPart);

	//Start point's pixel's coord
	int xPixel1 = xStart;
	int yPixel1 = floor(yStart);

	//Brightness = 1 - floatPart(yStart)*xGapStart
	//drawPoint(hDC, xPixel1, yPixel1, color, 1.0f - modf(yStart, &intPart) * xGapStart);
	//drawPoint(hDC, xPixel1, yPixel1 + 1, color, modf(yStart, &intPart) * xGapStart);
	

	//End point
	float xEnd = round(x2);
	float yEnd = y2 + gradient * (xEnd - x2);
	float xGapEnd = 1 - modf(x2 + 0.5, &intPart); 	

	//End point's pixel's coord
	int xPixel2 = xEnd;
	int yPixel2 = floor(yEnd);

	//Brightness = 1 - floatPart(yEnd)*xGapEnd
	drawPoint(hDC, xPixel2, yPixel2, color, 1.0f - modf(yEnd, &intPart) * xGapEnd);
	drawPoint(hDC, xPixel2, yPixel2 + 1, color, modf(yEnd, &intPart) * xGapEnd);

	//Drawing line by points 
	float yCurr = yStart + gradient;	// Y-coord start point
	for (int xCurr = xPixel1 + 1; xCurr < xPixel2; xCurr++) {
		drawPoint(hDC, xCurr, floor(yCurr), color, 1.0f - modf(yCurr, &intPart));
		drawPoint(hDC, xCurr, floor(yCurr) + 1, color, modf(yCurr, &intPart) );
		yCurr += gradient;
	}
}

//Draw line with smoothing by Y with Wu method
void algoWuEllipse::drawLineY(HDC hDC, float x1, float y1, float x2, float y2, COLORREF color) {
	if (y2 < y1) {
		std::swap(x1, x2);
		std::swap(y1, y2);
	}

	//function increament y-axis
	float dx = x2 - x1;
	float dy = y2 - y1;
	float gradient = dx / dy;

	//Start point
	float yStart = round(y1);
	float xStart = x1 + gradient * (yStart - y1);

	float intPart;
	float yGapStart = 1 - modf(y1 + 0.5, &intPart);

	//Start point's pixel's coord
	int yPixel1 = yStart;
	int xPixel1 = floor(xStart);

	//Brightness = 1 - floatPart(xStart)*yGapStart
	//drawPoint(hDC, xPixel1, yPixel1, color, 1.0f - modf(xStart, &intPart) * yGapStart);
	//drawPoint(hDC, xPixel1 + 1, yPixel1, color, modf(xStart, &intPart) * yGapStart);


	//End point
	float yEnd = round(y2);
	float xEnd = x2 + gradient * (yEnd - y2);
	float yGapEnd = 1 - modf(y2 + 0.5, &intPart);

	//End point's pixel's coord
	int yPixel2 = yEnd;
	int xPixel2 = floor(xEnd);

	//Brightness = 1 - floatPart(xEnd)*xyGapEnd
	drawPoint(hDC, xPixel2, yPixel2, color, 1.0f - modf(xEnd, &intPart) * yGapEnd);
	drawPoint(hDC, xPixel2 + 1, yPixel2, color, modf(xEnd, &intPart) * yGapEnd);

	//Drawing line by points 
	float xCurr = xStart + gradient;	// X-coord start point
	for (int yCurr = yPixel1 + 1; yCurr < yPixel2; yCurr++) {
		drawPoint(hDC, floor(xCurr), yCurr, color, 1.0f - modf(xCurr, &intPart));
		drawPoint(hDC, floor(xCurr) + 1, yCurr, color, modf(xCurr, &intPart));
		xCurr += gradient;
	}
}

//Draw line with smoothed with Wu method
void algoWuEllipse::drawLine(HDC hDC, float x1, float y1, float x2, float y2, COLORREF color) {
	algoWuEllipse::drawLineX(hDC, x1, y1, x2, y2, color);
	algoWuEllipse::drawLineY(hDC, x1, y1, x2, y2, color);
}

//Draw ellipse with smoothed with Wu method
void algoWuEllipse::drawEllipse(HDC hDC, COLORREF color) {

	float xCurr = xCenter - xRadius;	//x-coord of left ellipse point
	float xNext = xCurr + 1;	
	
	//y-coords of 2 points that match to current x-coord
	float yCurr1 = yRadius * sqrt(1 - ((xCurr - xCenter)*(xCurr - xCenter)) / (xRadius*xRadius)) + yCenter;
	float yNext1 = yRadius * sqrt(1 - ((xNext - xCenter)*(xNext - xCenter)) / (xRadius*xRadius)) + yCenter;
	float yCurr2 = -yRadius * sqrt(1 - ((xCurr - xCenter)*(xCurr - xCenter)) / (xRadius*xRadius)) + yCenter;
	float yNext2 = -yRadius * sqrt(1 - ((xNext - xCenter)*(xNext - xCenter)) / (xRadius*xRadius)) + yCenter;

	//Draw ellipse
	for (int i = -xRadius; i <= xRadius; i++) {
		drawLine(hDC, xCurr, yCurr1, xNext, yNext1, color);
		drawLine(hDC, xCurr, yCurr2, xNext, yNext2, color);

		xCurr = xNext;
		yCurr1 = yNext1;
		yCurr2 = yNext2;

		xNext = xNext + 1;
		yNext1 = yRadius * sqrt(1 - ((xNext - xCenter) * (xNext - xCenter)) / (xRadius * xRadius)) + yCenter;
		yNext2 = -yRadius * sqrt(1 - ((xNext - xCenter) * (xNext - xCenter)) / (xRadius * xRadius)) + yCenter;
	}


}
