#include "stdafx.h"
#include "OpenGLControl.h"


COpenGLControl::COpenGLControl()
{
	timerIteration = 0;
}


COpenGLControl::~COpenGLControl()
{
}

void COpenGLControl::oglCreate(CRect rect, CWnd * parent)
{
	CString className = AfxRegisterWndClass(CS_HREDRAW | CS_VREDRAW | CS_OWNDC, NULL, (HBRUSH)GetStockObject(BLACK_BRUSH), NULL);
	CreateEx(0, className, (CString)"Cells", WS_CHILD | WS_VISIBLE | WS_CLIPSIBLINGS | WS_CLIPCHILDREN, rect, parent, 0);
	m_oldWindow = rect;
	m_originalRect = rect;

	hWnd = parent;
};

BEGIN_MESSAGE_MAP(COpenGLControl, CWnd)
	ON_WM_PAINT()
	ON_WM_CREATE()
	ON_WM_TIMER()
	ON_WM_SIZE()
END_MESSAGE_MAP()


void COpenGLControl::OnPaint()
{
	CPaintDC dc(this); // device context for painting
	ValidateRect(NULL);
}


int COpenGLControl::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CWnd::OnCreate(lpCreateStruct) == -1)
		return -1;

	oglInitialize();

	return 0;
}

void COpenGLControl::OnDraw(CDC * pDC)
{
	//glClear(GL_COLOR_BUFFER_BIT);
	// Clear color and depth buffer bits
	//glClear(GL_COLOR_BUFFER_BIT);

	glClearColor(1, 1, 1, 1);
	glClear(GL_COLOR_BUFFER_BIT);

	field->drawField();
	field->drawGrid();

	// Swap buffers
	SwapBuffers(hdc);
	//Invalidate(false);
}

void COpenGLControl::oglInitialize(void)
{
	// Initial Setup:
	//
	static PIXELFORMATDESCRIPTOR pfd =
	{
		sizeof(PIXELFORMATDESCRIPTOR),
		1,
		PFD_DRAW_TO_WINDOW | PFD_SUPPORT_OPENGL | PFD_DOUBLEBUFFER,
		PFD_TYPE_RGBA,
		32,    // bit depth
		0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
		16,    // z-buffer depth
		0, 0, 0, 0, 0, 0, 0,
	};

	// Get device context only once.
	hdc = GetDC()->m_hDC;

	// Pixel format.
	m_nPixelFormat = ChoosePixelFormat(hdc, &pfd);
	SetPixelFormat(hdc, m_nPixelFormat, &pfd);

	// Create the OpenGL Rendering Context.
	hrc = wglCreateContext(hdc);
	wglMakeCurrent(hdc, hrc);

	// Basic Setup:
	//
	// Set color to use when clearing the background.
	glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
	gluOrtho2D(0, 1, 1, 0);
	// Send draw request
	//OnDraw(NULL);
}

HDC COpenGLControl::getHdc()
{
	return hdc;
}

void COpenGLControl::restartTimerIterator() {
	timerIteration = 0;
};

void COpenGLControl::OnTimer(UINT_PTR nIDEvent)
{
	switch (nIDEvent)
	{
	case 1:
	{
		
		OnDraw(NULL);
		if (timerIteration < field->getGenerNum()) {
			field->nextStep();
			timerIteration++;
		}
		//Sleep(900);
		break;
	}

	default:
		break;
	}

	CWnd::OnTimer(nIDEvent);
}


void COpenGLControl::OnSize(UINT nType, int cx, int cy)
{
	CWnd::OnSize(nType, cx, cy);

	if (0 >= cx || 0 >= cy || nType == SIZE_MINIMIZED) return;

	// Map the OpenGL coordinates.
	glViewport(0, 0, cx, cy);

	// Projection view
	//glMatrixMode(GL_PROJECTION);

	//glLoadIdentity();

	// Set our current view perspective
	//gluPerspective(35.0f, (float)cx / (float)cy, 0.01f, 2000.0f);

	// Model view
	//glMatrixMode(GL_MODELVIEW);
}
