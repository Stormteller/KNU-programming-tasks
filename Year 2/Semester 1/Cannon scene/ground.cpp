#include "ground.h"

//Draw ground
void Ground::draw()
{
	glPushMatrix();


	glLineWidth(2.0);
	glColor3f(0.2, 1, 0.5);

	glBegin(GL_TRIANGLE_STRIP);
	glVertex3f(-GROUND_SIZE, 0, -GROUND_SIZE);
	glVertex3f(-GROUND_SIZE, 0, GROUND_SIZE);
	glVertex3f(GROUND_SIZE, 0, -GROUND_SIZE);
	glVertex3f(GROUND_SIZE, 0, GROUND_SIZE);
	glEnd();

	glColor3f(1, 0, 0);
	glBegin(GL_LINES);
	glVertex3f(0, 0, 0);
	glVertex3f(1, 0, 0);;
	glEnd();

	glColor3f(0, 1, 0);
	glBegin(GL_LINES);
	glVertex3f(0, 0, 0);
	glVertex3f(0, 1, 0);;
	glEnd();

	glColor3f(0, 0, 1);
	glBegin(GL_LINES);
	glVertex3f(0, 0, 0);
	glVertex3f(0, 0, 1);;
	glEnd();


	glPopMatrix();

}