#include "stdafx.h"
#include "OpenGLRenderer.h"

GLdouble* multMatrices(GLdouble* a, GLdouble* b) {
	GLdouble res[16];
	for (int i = 0; i < 4; i++)
		for (int t = 0; t < 4; t++) {
			res[i * 4 + t] = 0;
			for (int l = 0; l < 4; l++) {
				res[i * 4 + t] += a[i * 4 + l] * b[l * 4 + t];
			}
		}
	return res;
}

COpenGLRenderer::COpenGLRenderer()
{
}

COpenGLRenderer::~COpenGLRenderer()
{
}

bool COpenGLRenderer::Init()
{
	glClearColor(1, 1, 1, 0);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	glOrtho(-4, 4, -4, 4, -4, 4);
	

	/****************************************/
	/*          Enable z-buferring          */
	/****************************************/

	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LEQUAL);

	return true;
}

void Light(byte color) {
	/****************************************/
	/*       Set up OpenGL lights           */
	/****************************************/
	GLfloat light1_ambient[] = { 0.1f, 0.1f, 0.3f, 1.0f };
	GLfloat light1_diffuse[] = { 0.6f, .6f, 0.6f, 1.0f };
	GLfloat light1_position[] = { -4.0f, -1.0f, -5.0f, 0.0f };
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
		r = 10;
		g = 0;
		b = 0;
		break;
	case 2:
		r = 0;
		g = 10;
		b = 0;
		break;
	case 3:
		r = 0;
		g = 0;
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

void COpenGLRenderer::Render(float FrameTime)
{
	for (int i = 0; i < 4; i++)
		for (int t = 0; t < 4; t++)
			if (i == t)cel[4 * i + t] = 1;
			else cel[4 * i + t] = 0;
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glLineWidth(2);
	glBegin(GL_LINES);
		Light(1);
		glVertex3f(-200, 0, 0);
		glVertex3f(200, 0, 0);

		Light(2);
		glVertex3f(0, -200, 0);
		glVertex3f(0, 200, 0);

		Light(3);
		glVertex3f(0, 0, -200);
		glVertex3f(0, 0, 200);
	glEnd();

	glColor3f(0.2f, 0.2f, 0.2f);
#pragma region cylinder
	glPushMatrix();
		Light(0);
		float radius = 0.8;
		float height = 0.8;
		//glTranslatef(totalShiftX, totalShiftY, -totalShiftZ);//main Axises
		/*glRotatef(totalAngelX, 1, 0, 0);//local Axises
		glRotatef(totalAngelY, 0, 1, 0);//local Axises
		glRotatef(totalAngelZ, 0, 0, 1);//local Axises
		//}
		//glScalef(1 + totalShiftZ, 1 + totalShiftZ, 1 + totalShiftZ);
		/*glPushMatrix();
		glRotatef(-totalAngelX, 1, 0, 0);//local Axises
		glRotatef(-totalAngelY, 0, 1, 0);//local Axises
		glRotatef(-totalAngelZ, 0, 0, 1);//local Axises
		glTranslatef(-totalShiftX, -totalShiftY, totalShiftZ);//main Axises*/
		/*glRotatef(totalAngelX, 1, 0, 0);//local Axises
		glRotatef(totalAngelY, 0, 1, 0);//local Axises
		glRotatef(totalAngelZ, 0, 0, 1);//local Axises*/
			//glTranslatef(localShiftX, localShiftY, -localShiftZ);//local Axises
		GLdouble rotationY[16] = { cos(totalAngelY),0,-sin(totalAngelY),0,0,1,0,0,sin(totalAngelY),0,cos(totalAngelY),0,0,0,0,1 };
		GLdouble rotationYM[16] = { cos(-totalAngelY),0,-sin(-totalAngelY),0,0,1,0,0,sin(-totalAngelY),0,cos(-totalAngelY),0,0,0,0,1 };
		GLdouble translate[16] = { 1,0,0,0,0,1,0,0,0,0,1,0,totalShiftX,totalShiftY,-totalShiftZ,1 };
		GLdouble translateM[16] = { 1,0,0,0,0,1,0,0,0,0,1,0,-totalShiftX,-totalShiftY,totalShiftZ,1 };
		//glMultMatrixd(translate);
		glPushMatrix();
		//glMultMatrixd(rotationY);
		GLdouble* res = multMatrices(rotationY, translate);
		GLdouble r[16];
		for (int i = 0; i < 16; i++)
			r[i] = res[i];
		//glMultMatrixd(r);
		//glMultMatrixd(r);
		glLoadIdentity();
		glMultMatrixd(cel);
		glMultMatrixd(translate);
		glMultMatrixd(rotationY);
		glGetDoublev(GL_MODELVIEW_MATRIX, cel);
		glPopMatrix();
		//glMultMatrixd(rotationY); glMultMatrixd(translate);
		//float abs = sqrtf(pow(totalShiftX, 2) + pow(totalShiftY, 2) + pow(totalShiftZ, 2));
		//glTranslatef(abs*cos(totalAngelY), abs*cos(totalAngelX), -abs*sin(totalAngelY));//main Axises
		glPushMatrix();
		glMultMatrixd(cel);
			glRotatef(localAngelX, 1, 0, 0);//local Axises
			glRotatef(localAngelY, 0, 1, 0);//local Axises
			glRotatef(localAngelZ, 0, 0, 1);//local Axises
			glBegin(GL_TRIANGLE_STRIP);
				for (float i = 0; i < 6.28; i+=0.001) {
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
			glLineWidth(1);
			glBegin(GL_LINES);
				Light(1);
				glVertex3f(-1, 0, 0);
				glVertex3f(1, 0, 0);

				Light(2);
				glVertex3f(0, -1, 0);
				glVertex3f(0, 1, 0);

				Light(3);
				glVertex3f(0, 0, -1);
				glVertex3f(0, 0, 1);
			glEnd();
		glPopMatrix();
		//glPopMatrix();
	glPopMatrix();
#pragma endregion drawing
}

void COpenGLRenderer::Resize(int Width, int Height)
{

	this->Width = Width;
	this->Height = Height;

	glViewport(0, 0, Width, Height);
	gluOrtho2D(-Width / (2 * (float)min(Width, Height)), Width/(2*(float)min(Width, Height)), -Height / (2 * (float)min(Width, Height)), Height / (2*(float)min(Width, Height)));
}

void COpenGLRenderer::Destroy()
{
}
