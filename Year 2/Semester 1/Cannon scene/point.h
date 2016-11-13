#pragma once


class Point {
	float pointX;
	float pointY;
	float pointZ;
public:
	Point() {
		pointX = 0;
		pointY = 0;
		pointZ = 0;
	}

	Point(int x, int y, int z) {
		pointX = x;
		pointY = y;
		pointZ = z;
	}

	float getX() {
		return pointX;
	}

	float getY() {
		return pointY;
	}

	float getZ() {
		return pointZ;
	}

	void setX(float x) {
		pointX = x;
	}

	void setY(float y) {
		pointY = y;
	}

	void setZ(float z) {
		pointZ = z;
	}
};