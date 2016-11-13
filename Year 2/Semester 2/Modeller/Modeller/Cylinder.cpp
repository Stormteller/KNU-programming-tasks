#include "stdafx.h"
#include "Cylinder.h"

Cylinder::Cylinder(GLdouble* M):Shape(M)
{
	type = 0;
}

void Cylinder::Render(GLdouble * cylinderMatrix1, int i)
{
	GLdouble rotationY[16] = { cos(totalAngelY),0,-sin(totalAngelY),0,0,1,0,0,sin(totalAngelY),0,cos(totalAngelY),0,0,0,0,1 };
	GLdouble rotationX[16] = { 1,0,0,0,0,cos(totalAngelX),sin(totalAngelX),0,0,-sin(totalAngelX),cos(totalAngelX),0,0,0,0,1 };
	GLdouble rotationZ[16] = { cos(totalAngelZ),sin(totalAngelZ),0,0,-sin(totalAngelZ),cos(totalAngelZ),0,0,0,0,1,0,0,0,0,1 };
	GLdouble translate[16] = { 1,0,0,0,0,1,0,0,0,0,1,0,-totalShiftX,totalShiftY,-totalShiftZ,1 };
	glPushMatrix();
		glLoadIdentity();
		//glMultMatrixd(rotationY);
		//glMultMatrixd(rotationX);
		//glMultMatrixd(rotationZ);
		//glMultMatrixd(Matrix);
		/*if (totalAngelX || totalAngelY || totalAngelZ) {
			totalAngelX = 0;
			totalAngelY = 0;
			totalAngelZ = 0;
		}
		else {
			glMultMatrixd(translate);
			totalShiftX = 0;
			totalShiftY = 0;
			totalShiftZ = 0;
		}*/
		if (totalShiftX || totalShiftY || totalShiftZ) {
			glMultMatrixd(translate);
			totalShiftX = 0;
			totalShiftY = 0;
			totalShiftZ = 0;
		}
		else {
			glMultMatrixd(rotationY);
			glMultMatrixd(rotationX);
			glMultMatrixd(rotationZ);
			totalAngelX = 0;
			totalAngelY = 0;
			totalAngelZ = 0;
		}
		glMultMatrixd(Matrix);
		glGetDoublev(GL_MODELVIEW_MATRIX, Matrix);
	glPopMatrix();

	glPushMatrix();
		glScalef(scale, scale, scale);
		glColor3f(1, 0, 0);
		glPushMatrix();
			glMultMatrixd(Matrix);
			glRotatef(localAngelX, 1, 0, 0);//local Axises
			glRotatef(localAngelY, 0, 1, 0);//local Axises
			glRotatef(localAngelZ, 0, 0, 1);//local Axises
			glLineWidth(1);
			glBegin(GL_LINES);
			//glColor3f(1, 0, 0);
			//glPushMatrix();
			//glLoadIdentity();
			Light::Lighting(1);
			//glPopMatrix();
			glVertex3f(-1, 0, 0);
			glVertex3f(1, 0, 0);

			//glColor3f(0, 1, 0);
			//glPushMatrix();
			//glLoadIdentity();
			Light::Lighting(2);
			//glPopMatrix();
			glVertex3f(0, -1, 0);
			glVertex3f(0, 1, 0);

			//glColor3f(0, 0, 1);
			//glPushMatrix();
			//glLoadIdentity();
			Light::Lighting(3);
			//glPopMatrix();
			glVertex3f(0, 0, -1);
			glVertex3f(0, 0, 1);
			glEnd();
		glPopMatrix();

		Light::Lighting(4);
		glMultMatrixd(Matrix);
		glRotatef(localAngelX, 1, 0, 0);//local Axises
		glRotatef(localAngelY, 0, 1, 0);//local Axises
		glRotatef(localAngelZ, 0, 0, 1);//local Axises
		glLoadName(i);
		glBegin(GL_TRIANGLE_STRIP);
		for (float i = 0; i < 6.28; i += 0.001) {
			glNormal3f(cos(i), 0, sin(i));
			glVertex3f(radius*cos(i), height, radius*sin(i));
			glNormal3f(cos(i), 0, sin(i));
			glVertex3f(radius*cos(i), -height, radius*sin(i));
		}
		glNormal3f(cos(0), 0, sin(0));
		glVertex3f(radius*cos(0), height, radius*sin(0));
		glNormal3f(cos(0), 0, sin(0));
		glVertex3f(radius*cos(0), -height, radius*sin(0));
		glEnd();
		glBegin(GL_TRIANGLE_FAN);
		glNormal3f(0, 1, 0);
		glVertex3f(0, radius, 0);
		for (float i = 0; i < 6.28; i += 0.001) {
			glNormal3f(0, 1, 0);
			glVertex3f(radius*cos(i), height, radius*sin(i));
		}
		glNormal3f(0, 1, 0);
		glVertex3f(radius*cos(0), height, radius*sin(0));
		glEnd();
		glBegin(GL_TRIANGLE_FAN);
		glNormal3f(0, -1, 0);
		glVertex3f(0, -radius, 0);
		for (float i = 0; i < 6.28; i += 0.001) {
			glNormal3f(0, -1, 0);
			glVertex3f(radius*cos(i), -height, radius*sin(i));
		}
		glNormal3f(0, -1, 0);
		glVertex3f(radius*cos(0), -height, radius*sin(0));
		glEnd();
	glPopMatrix();
}
