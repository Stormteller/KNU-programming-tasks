// LabDlg.cpp : implementation file
//

#include "stdafx.h"
#include "Lab.h"
#include "LabDlg.h"
#include "afxdialogex.h"
#include <cstring>
#include <string>

#ifdef _DEBUG
#define new DEBUG_NEW
#endif





// CLabDlg dialog

CLabDlg::CLabDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_LAB_DIALOG, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CLabDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CLabDlg, CDialogEx)
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_START_BTN, &CLabDlg::OnBnClickedStartBtn)
END_MESSAGE_MAP()


// CLabDlg message handlers

BOOL CLabDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon

	CRect rect;
	int width = 600;
	// Get size and position of the picture control
	GetDlgItem(IDC_FIELD)->GetWindowRect(rect);
	rect.bottom = rect.top + width;
	rect.right = rect.left + width;
	GetDlgItem(IDC_FIELD)->MoveWindow(&rect, TRUE);

	// Convert screen coordinates to client coordinates
	ScreenToClient(rect);

	// Create OpenGL Control window
	m_oglWindow.oglCreate(rect, this);


	GetDlgItem(IDC_F_SIZE)->SetWindowTextW((CString)"10");
	GetDlgItem(IDC_RESETTL_RAD)->SetWindowTextW((CString)"2");
	GetDlgItem(IDC_BREED_RAD)->SetWindowTextW((CString)"2");
	GetDlgItem(IDC_FERTILITY)->SetWindowTextW((CString)"3");
	GetDlgItem(IDC_DENSITY)->SetWindowTextW((CString)"0.2");
	GetDlgItem(IDC_N_SPC)->SetWindowTextW((CString)"2");
	GetDlgItem(IDC_N_GEN)->SetWindowTextW((CString)"5");

	CComboBox* cbox = (CComboBox*)GetDlgItem(IDC_BR_TYPE);
	cbox->SetCurSel(1);

	

	return TRUE;  // return TRUE  unless you set the focus to a control
}

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void CLabDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // device context for painting

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// Center icon in client rectangle
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// Draw the icon
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
	/*if (field != NULL)
		field->drawGrid(m_oglWindow.getHdc());*/

}

// The system calls this function to obtain the cursor to display while the user drags
//  the minimized window.
HCURSOR CLabDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

Settings CLabDlg::getSettings() {
	CString data;
	Settings settings;
	char* p;

	GetDlgItem(IDC_F_SIZE)->GetWindowTextW(data);
	settings.fieldSize = _wtoi(data);

	GetDlgItem(IDC_RESETTL_RAD)->GetWindowTextW(data);
	settings.resettlRadius = _wtoi(data);

	GetDlgItem(IDC_BREED_RAD)->GetWindowTextW(data);
	settings.breedRadius = _wtoi(data);

	GetDlgItem(IDC_FERTILITY)->GetWindowTextW(data);
	settings.fertility = _wtoi(data);

	GetDlgItem(IDC_DENSITY)->GetWindowTextW((data));
	settings.density = _wtof(data);

	GetDlgItem(IDC_N_SPC)->GetWindowTextW(data);
	settings.numOfSpecies = _wtoi(data);

	GetDlgItem(IDC_N_GEN)->GetWindowTextW(data);
	settings.numOfGenerations = _wtoi(data);

	CComboBox* cbox = (CComboBox*)GetDlgItem(IDC_BR_TYPE);
	int curSel = cbox->GetCurSel();;
	if (curSel == 0) settings.brType = Syngenesis;
	if (curSel == 1) settings.brType = Agamobium;

	return settings;
}

void CLabDlg::OnBnClickedStartBtn()
{
	Settings settings = getSettings();

	if (m_oglWindow.field) delete m_oglWindow.field;
	m_oglWindow.field = new Field(settings);
	m_oglWindow.restartTimerIterator();
	m_oglWindow.field->init();

	// Setup the OpenGL Window's timer to render
	m_oglWindow.m_unpTimer = m_oglWindow.SetTimer(1, 500, 0);

}
