#define _USE_MATH_DEFINES
#include <windows.h>
#include <GL/glut.h> 
#include "scene.h"

//OpenGL init
void initGL() {
	glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
	glClearDepth(1.0f);
	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LEQUAL);
	glShadeModel(GL_SMOOTH);
	glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);
}

int main(int argc, char** argv) {
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE);
	glutInitWindowSize(640, 480);
	glutInitWindowPosition(50, 50);
	glutCreateWindow("Cannonball");
	glutDisplayFunc(Scene::display);
	glutReshapeFunc(Scene::reshape);
	glutKeyboardFunc(Scene::keyboardPress);
	initGL();
	glutMainLoop();
	return 0;
}