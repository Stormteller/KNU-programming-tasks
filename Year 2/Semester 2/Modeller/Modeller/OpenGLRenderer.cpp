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
bool gluInvertMatrix(const double m[16], double invOut[16])
{
	double inv[16], det;
	int i;

	inv[0] = m[5] * m[10] * m[15] -
		m[5] * m[11] * m[14] -
		m[9] * m[6] * m[15] +
		m[9] * m[7] * m[14] +
		m[13] * m[6] * m[11] -
		m[13] * m[7] * m[10];

	inv[4] = -m[4] * m[10] * m[15] +
		m[4] * m[11] * m[14] +
		m[8] * m[6] * m[15] -
		m[8] * m[7] * m[14] -
		m[12] * m[6] * m[11] +
		m[12] * m[7] * m[10];

	inv[8] = m[4] * m[9] * m[15] -
		m[4] * m[11] * m[13] -
		m[8] * m[5] * m[15] +
		m[8] * m[7] * m[13] +
		m[12] * m[5] * m[11] -
		m[12] * m[7] * m[9];

	inv[12] = -m[4] * m[9] * m[14] +
		m[4] * m[10] * m[13] +
		m[8] * m[5] * m[14] -
		m[8] * m[6] * m[13] -
		m[12] * m[5] * m[10] +
		m[12] * m[6] * m[9];

	inv[1] = -m[1] * m[10] * m[15] +
		m[1] * m[11] * m[14] +
		m[9] * m[2] * m[15] -
		m[9] * m[3] * m[14] -
		m[13] * m[2] * m[11] +
		m[13] * m[3] * m[10];

	inv[5] = m[0] * m[10] * m[15] -
		m[0] * m[11] * m[14] -
		m[8] * m[2] * m[15] +
		m[8] * m[3] * m[14] +
		m[12] * m[2] * m[11] -
		m[12] * m[3] * m[10];

	inv[9] = -m[0] * m[9] * m[15] +
		m[0] * m[11] * m[13] +
		m[8] * m[1] * m[15] -
		m[8] * m[3] * m[13] -
		m[12] * m[1] * m[11] +
		m[12] * m[3] * m[9];

	inv[13] = m[0] * m[9] * m[14] -
		m[0] * m[10] * m[13] -
		m[8] * m[1] * m[14] +
		m[8] * m[2] * m[13] +
		m[12] * m[1] * m[10] -
		m[12] * m[2] * m[9];

	inv[2] = m[1] * m[6] * m[15] -
		m[1] * m[7] * m[14] -
		m[5] * m[2] * m[15] +
		m[5] * m[3] * m[14] +
		m[13] * m[2] * m[7] -
		m[13] * m[3] * m[6];

	inv[6] = -m[0] * m[6] * m[15] +
		m[0] * m[7] * m[14] +
		m[4] * m[2] * m[15] -
		m[4] * m[3] * m[14] -
		m[12] * m[2] * m[7] +
		m[12] * m[3] * m[6];

	inv[10] = m[0] * m[5] * m[15] -
		m[0] * m[7] * m[13] -
		m[4] * m[1] * m[15] +
		m[4] * m[3] * m[13] +
		m[12] * m[1] * m[7] -
		m[12] * m[3] * m[5];

	inv[14] = -m[0] * m[5] * m[14] +
		m[0] * m[6] * m[13] +
		m[4] * m[1] * m[14] -
		m[4] * m[2] * m[13] -
		m[12] * m[1] * m[6] +
		m[12] * m[2] * m[5];

	inv[3] = -m[1] * m[6] * m[11] +
		m[1] * m[7] * m[10] +
		m[5] * m[2] * m[11] -
		m[5] * m[3] * m[10] -
		m[9] * m[2] * m[7] +
		m[9] * m[3] * m[6];

	inv[7] = m[0] * m[6] * m[11] -
		m[0] * m[7] * m[10] -
		m[4] * m[2] * m[11] +
		m[4] * m[3] * m[10] +
		m[8] * m[2] * m[7] -
		m[8] * m[3] * m[6];

	inv[11] = -m[0] * m[5] * m[11] +
		m[0] * m[7] * m[9] +
		m[4] * m[1] * m[11] -
		m[4] * m[3] * m[9] -
		m[8] * m[1] * m[7] +
		m[8] * m[3] * m[5];

	inv[15] = m[0] * m[5] * m[10] -
		m[0] * m[6] * m[9] -
		m[4] * m[1] * m[10] +
		m[4] * m[2] * m[9] +
		m[8] * m[1] * m[6] -
		m[8] * m[2] * m[5];

	det = m[0] * inv[0] + m[1] * inv[4] + m[2] * inv[8] + m[3] * inv[12];

	if (det == 0)
		return false;

	det = 1.0 / det;

	for (i = 0; i < 16; i++)
		invOut[i] = inv[i] * det;

	return true;
}

COpenGLRenderer::COpenGLRenderer()
{
	for (int i = 0; i < 4; i++)
		for (int t = 0; t < 4; t++)
			if (i == t)globalMatrix[4 * i + t] = 1;
			else globalMatrix[4 * i + t] = 0;
	selectedObj = nullptr;
}



COpenGLRenderer::~COpenGLRenderer()
{
}

void COpenGLRenderer::clearMatrix()
{
	for (int i = 0; i < 4; i++)
		for (int t = 0; t < 4; t++)
			if (i == t)globalMatrix[4 * i + t] = 1;
			else globalMatrix[4 * i + t] = 0;
	selectedObj = nullptr;
}

vector<Shape*>& COpenGLRenderer::getShapes() {
	return shape;
}

void COpenGLRenderer::addShape(byte a, float x, float y)
{
	Shape* p;
	GLdouble globalMatrix[16];
	for (int i = 0; i < 4; i++)
		for (int t = 0; t < 4; t++)
			if (i == t)globalMatrix[4 * i + t] = 1;
			else globalMatrix[4 * i + t] = 0;
	if(a==0)
		p= new Cylinder(globalMatrix);
	shape.push_back(p);
	p->Shift(x, y, 0);
	selectedObj = p;
}

void COpenGLRenderer::Shift(float dx, float dy, float dz)
{
	if(selectedObj)
		selectedObj->Shift(dx, dy, dz);
}

void COpenGLRenderer::RotateLocal(float dx, float dy, float dz)
{
	if (selectedObj)
		selectedObj->RotateLocal(dx, dy, dz);
}

void COpenGLRenderer::RotateTotal(float dx, float dy, float dz)
{
	if (selectedObj)
		selectedObj->RotateTotal(dx, dy, dz);
}

void COpenGLRenderer::Scale(float k)
{
	if (selectedObj)
		selectedObj->Scale(k);
}

void COpenGLRenderer::saveSelectedPos() {
	selectedObj->savePos();
}

#define BUFSIZE 512

void COpenGLRenderer::Select(float x, float y)
{
	GLuint selectBuf[BUFSIZE];
	GLint hits;
	GLint viewport[4];

	//glGetIntegerv(GL_VIEWPORT, viewport);
	glSelectBuffer(BUFSIZE, selectBuf);

	glRenderMode(GL_SELECT); // Enter the SELECT render mode
	glInitNames();
	glPushName(-1);
	glDepthRange(0.1, 150);

	glMatrixMode(GL_PROJECTION);
	glPushMatrix();
		glLoadIdentity();
		glGetIntegerv(GL_VIEWPORT, viewport);
		gluPickMatrix((GLdouble)x/Width, (GLdouble)y/Height, 5000.0, 5000.0, viewport);
		gluPerspective(30.0, Width / Height, 0.2, 150.0);
		glTranslatef(0.0, 0.0, -10.0);
		glMatrixMode(GL_MODELVIEW);
		//Render();
	/*float radius = 0.8;
	float height = 0.8;
		glLoadName(5);
		glBegin(GL_TRIANGLE_STRIP);
		for (float i = 0; i < 6.28; i += 0.001) {
			glVertex3f(radius*cos(i), height, radius*sin(i));
			glVertex3f(radius*cos(i), -height, radius*sin(i));
		}
		glVertex3f(radius*cos(0), height, radius*sin(0));
		glVertex3f(radius*cos(0), -height, radius*sin(0));
		glEnd();
		glBegin(GL_TRIANGLE_FAN);
		glVertex3f(0, radius, 0);
		for (float i = 0; i < 6.28; i += 0.001) {
			glVertex3f(radius*cos(i), height, radius*sin(i));
		}
		glVertex3f(radius*cos(0), height, radius*sin(0));
		glEnd();
		glBegin(GL_TRIANGLE_FAN);
		glVertex3f(0, -radius, 0);
		for (float i = 0; i < 6.28; i += 0.001) {
			glVertex3f(radius*cos(i), -height, radius*sin(i));
		}
		glVertex3f(radius*cos(0), -height, radius*sin(0));
		glEnd();*/
		for (int i = 0; i < shape.size(); i++)
			shape[i]->Render(globalMatrix, i);
		hits = glRenderMode(GL_RENDER);
		glMatrixMode(GL_PROJECTION);
	glPopMatrix();

	glMatrixMode(GL_MODELVIEW);
	//hits = glRenderMode(GL_RENDER);

	if (hits)
	{
		int n = 1; double minz = selectBuf[5];
		for (int i = 2; i<hits; i++)
		{
			if (selectBuf[1 + i * 4]<minz)
			{
				n = i; minz = selectBuf[1 + i * 4];
			}
		}
		selectedObj = shape[selectBuf[3 + n * 4]];
	}//only select the object we see (nearest object)!
	Init();
	/*GLdouble pos3D_x, pos3D_y, pos3D_z;

	// arrays to hold matrix information

	GLdouble model_view[16];
	glGetDoublev(GL_MODELVIEW_MATRIX, model_view);

	GLdouble projection[16];
	glGetDoublev(GL_PROJECTION_MATRIX, projection);

	GLint viewport[4];
	glGetIntegerv(GL_VIEWPORT, viewport);

	// get 3D coordinates based on window coordinates
	GLdouble Z;
	glReadPixels(x, y, 1, 1, GL_DEPTH_COMPONENT, GL_FLOAT, &Z);
	gluUnProject(x, y, Z,
		model_view, projection, viewport,
		&pos3D_x, &pos3D_y, &pos3D_z);*/
}

bool COpenGLRenderer::Init()
{
	glClearColor(1, 1, 1, 0);
	glViewport(0, 0, this->Width, this->Height);
	glEnable(GL_DEPTH_TEST);
	glLoadIdentity();
	gluPerspective(30, Width / Height, 0.2, 150);
	glTranslatef(0.0, 0.0, -10.0);
	return true;
}

void COpenGLRenderer::Render(float FrameTime)
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glLineWidth(2);
	glBegin(GL_LINES);
		Light::Lighting(1);
		glVertex3f(-200, 0, 0);
		glVertex3f(200, 0, 0);

		Light::Lighting(2);
		glVertex3f(0, -200, 0);
		glVertex3f(0, 200, 0);

		Light::Lighting(3);
		glVertex3f(0, 0, -200);
		glVertex3f(0, 0, 200);
	glEnd();

	glColor3f(0.2f, 0.2f, 0.2f);
#pragma region cylinder
	glPushMatrix();
		//glGetDoublev(GL_MODELVIEW_MATRIX, globalMatrix);
		for (int i = 0; i < shape.size();i++)
			shape[i]->Render(globalMatrix, 0);
	glPopMatrix();
#pragma endregion drawing

}

void COpenGLRenderer::Resize(int Width, int Height)
{
	this->Width = Width;
	this->Height = Height;
	glViewport(0, 0, Width, Height);
	glEnable(GL_DEPTH_TEST);
	glLoadIdentity();
	gluPerspective(30, Width/Height, 0.2, 150);
	glTranslatef(0.0, 0.0, -10.0);
	glGetDoublev(GL_MODELVIEW_MATRIX, globalMatrix);
}

void COpenGLRenderer::Destroy()
{
}
