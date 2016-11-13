#include "scene.h"

//Scene's init parameters
float Scene::cameraAngleToRotateX = 45;	//camera angle axis X
float Scene::cameraAngleToRotateY = 45;	//camera angle axis Y
float Scene::depth = -40;	//Camera depth
float Scene::time = 0;	//Current time
const float Scene::G = 0.05f;	//acceleration of gravity
const int Scene::TIMESTEP = 20;	//Milleseconds per timer tick

Cannonball Scene::cannonball;
Ground Scene::ground;


//Scene display function
void Scene::display() {
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glMatrixMode(GL_MODELVIEW);


	glLoadIdentity();
	glTranslatef(0.0f, 0.0f, depth);
	glRotatef(cameraAngleToRotateY, 1.0f, 0.0f, 0.0f);
	glRotatef(cameraAngleToRotateX, 0.0f, 1.0f, 0.0f);

	cannonball.draw();
	ground.draw();

	glutSwapBuffers();

}


//Timer tick function
void Scene::timer(int value) {
	//Calculate new Y coord: y = v0 * sin(alpha) * t - G * t^2 / 2 
	//v0 - start speed | alpha - start angle | t - current time 
	cannonball.setY(cannonball.START_SPEED * sin(cannonball.START_ANGLE / 180 * M_PI) * time - Scene::G * time * time / 2);
	//if ball is not collide ground - move
	if (cannonball.getCenter().getY() >= 0) {
		//Calculate new X coord: y = v0 * cos(alpha) * t
		cannonball.setX(cannonball.START_SPEED * cos(cannonball.START_ANGLE / 180 * M_PI) * time);
	}
	else {
		cannonball.setY(0);
	}

	//Save trajectory point
	cannonball.savePositionToPath();
	//timer tick
	time += 0.5;
	glutPostRedisplay();
	//Keep on move if cannonball is not on the ground
	if (cannonball.getCenter().getY() > 0 || time <= 1) {
		glutTimerFunc(Scene::TIMESTEP, timer, 0);
	}

}

//Move scene by keys
void Scene::keyboardPress(unsigned char key, int x, int y)
{
	switch (key) {
	//To the left
	case('a') : case('A') :
	{
		cameraAngleToRotateX += 5;
		break;
	}
	//To the right
	case('d') : case('D') :
	{
		cameraAngleToRotateX -= 5;
		break;
	}
	//Up
	case('w') : case('W') :
	{
		cameraAngleToRotateY += 5;
		break;
	}
	//Down
	case('s') : case('S') :
	{
		cameraAngleToRotateY -= 5;
		break;
	}
	//Move camera back
	case('q') : case('Q') :
	{
		depth -= 1;
		break;
	}
	//Move camera forward
	case('e') : case('E') :
	{
		depth += 1;
		break;
	}
	//Reset scene
	case('r') : case('R') :
	{
		cannonball.reset();
		time = 0;
		break;
	}
	//Make cannonball fly
	case(' ') :
	{
		glutTimerFunc(0, timer, 0);
	}
	default:
		break;
	}
	glutPostRedisplay();
}

//On window sizes change recalculate display
void Scene::reshape(GLsizei width, GLsizei height) { 
										
	if (height == 0) height = 1;
	GLfloat aspect = (GLfloat)width / (GLfloat)height;

	glViewport(0, 0, width, height);

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(45.0f, aspect, 0.1f, 100.0f);

	glMatrixMode(GL_MODELVIEW);
}
