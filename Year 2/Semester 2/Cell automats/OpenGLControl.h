#pragma once
#include "afxwin.h"
#include <gl/gl.h>
#include <gl/glu.h>
#include "Field.h"

class Field;

class COpenGLControl :public CWnd
{
	CWnd *hWnd;
	HDC hdc;
	HGLRC hrc;
	int m_nPixelFormat;
	CRect m_rect;
	CRect m_oldWindow;
	CRect m_originalRect;

	int timerIteration;

public:
	Field* field;

	UINT_PTR m_unpTimer;

	COpenGLControl();
	virtual ~COpenGLControl();

	void oglCreate(CRect, CWnd *parent);

	void oglInitialize(void);

	HDC getHdc();

	void restartTimerIterator();

	DECLARE_MESSAGE_MAP()
	afx_msg void OnPaint();
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnDraw(CDC *pDC);
	afx_msg void OnTimer(UINT_PTR nIDEvent);
	afx_msg void OnSize(UINT nType, int cx, int cy);
};

