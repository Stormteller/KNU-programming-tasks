#pragma once
#include <GL\freeglut.h>
class Light {
public: static void Lighting(unsigned char color) {
		/****************************************/
		/*       Set up OpenGL lights           */
		/****************************************/
		GLfloat light1_ambient[] = { 1.1f, 1.1f, 1.3f, 1.0f };
		GLfloat light1_diffuse[] = { 1.6f, 1.6f, 1.6f, 1.0f };
		GLfloat light1_position[] = { 1.0f, 100.0f, 1.0f, 0.0f};
		GLfloat dir[] = { 1.0f, -1.0f, 1.0f, 1.0f };
		//glLightfv(GL_LIGHT1, GL_SPOT_DIRECTION, dir);
		GLfloat mat_shininess[] = { 3.0 };
		float r, g, b;
		switch (color)
		{
		case 0:
			r = 0.8;
			g = 0.8;
			b = 0.8;
			break;
		case 1:
			r = 1000;
			g = 0;
			b = 0;
			break;
		case 2:
			r = 0;
			g = 1000;
			b = 0;
			break;
		case 3:
			r = 0;
			g = 0;
			b = 1000;
			break;
		case 4:
			r = 10;
			g = 10;
			b = 10;
			break;
		default:
			break;
		}
		GLfloat mat_specular[] = { r, g, b, 1.0 };

		glEnable(GL_LIGHTING);
		glEnable(GL_NORMALIZE);

		glEnable(GL_LIGHT1);
		glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_specular);
		glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular);
		glMaterialfv(GL_FRONT, GL_SHININESS, mat_shininess);
		glLightfv(GL_LIGHT1, GL_AMBIENT, light1_ambient);
		glLightfv(GL_LIGHT1, GL_DIFFUSE, light1_diffuse);
		glLightfv(GL_LIGHT1, GL_POSITION, light1_position);
	}
};