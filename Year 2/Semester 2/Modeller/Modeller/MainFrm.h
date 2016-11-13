#pragma once
#include "OpenGLRenderer.h"
#include "sqlite3.h"
#include <string>

class CMainFrame : public CFrameWnd
{
	
protected: 
	CMainFrame();
	DECLARE_DYNCREATE(CMainFrame)

public:
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	sqlite3* db;
	virtual ~CMainFrame();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:  
	CStatusBar        m_wndStatusBar;

protected:
	DECLARE_MESSAGE_MAP()
		afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
		afx_msg void OnDestroy();
		afx_msg void OnPaint();
		afx_msg void OnSize(UINT nType, int cx, int cy);
		afx_msg BOOL OnMouseWheel(UINT, short, CPoint);

	CString Title;
	HGLRC hGLRC;
	int Width, Height;
	COpenGLRenderer OpenGLRenderer;

public:
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
//	afx_msg void OnMouseLeave();
	afx_msg void OnUpdateAxisesMain(CCmdUI *pCmdUI);
	afx_msg void OnUpdateAxisesLocal(CCmdUI *pCmdUI);
	afx_msg void OnAxisesLocal();
	afx_msg void OnAxisesMain();
	afx_msg void OnLButtonDblClk(UINT nFlags, CPoint point);
//	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnRButtonDblClk(UINT nFlags, CPoint point);
	afx_msg void OnDatabaseLoad();
	afx_msg void OnDatabaseSave();
};


