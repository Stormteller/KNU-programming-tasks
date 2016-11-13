#pragma once
#define _USE_MATH_DEFINES
#include "cannonball.h"
#include "ground.h"
#include <math.h>  

class Scene {
public:
	static float cameraAngleToRotateX;	//camera angle axis X
	static float cameraAngleToRotateY;	//camera angle axis Y
	static float depth;	//camera depth
	static float time;	//Current scene time
	static const float G;	//acceleration of gravity
	static const int TIMESTEP;	//Milleseconds per timer tick

	static Cannonball cannonball;
	static Ground ground;

	static void display();
	static void keyboardPress(unsigned char key, int x, int y);
	static void timer(int value);
	static void reshape(GLsizei width, GLsizei height);
};
