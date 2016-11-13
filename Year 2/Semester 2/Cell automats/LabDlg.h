
// LabDlg.h : header file
//

#pragma once
#include "OpenGLControl.h"
#include "utils.h"
#include "Field.h"

// CLabDlg dialog
class CLabDlg : public CDialogEx
{
private:
	COpenGLControl m_oglWindow;
// Construction
public:
	CLabDlg(CWnd* pParent = NULL);	// standard constructor

// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_LAB_DIALOG };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support


// Implementation
protected:
	HICON m_hIcon;

	Settings getSettings();
	// Generated message map functions
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedStartBtn();
};
