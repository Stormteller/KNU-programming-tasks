#include "stdafx.h"
#include "Modeller.h"
#include <stdexcept>

#include "MainFrm.h"

using std::runtime_error;

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

// CMainFrame

IMPLEMENT_DYNCREATE(CMainFrame, CFrameWnd)

BEGIN_MESSAGE_MAP(CMainFrame, CFrameWnd)
	ON_WM_CREATE()
	ON_WM_DESTROY()
	ON_WM_PAINT()
	ON_WM_SIZE()
	ON_WM_MOUSEWHEEL()
	ON_WM_MOUSEMOVE()
//	ON_WM_MOUSELEAVE()
ON_UPDATE_COMMAND_UI(ID_AXISES_MAIN, &CMainFrame::OnUpdateAxisesMain)
ON_UPDATE_COMMAND_UI(ID_AXISES_LOCAL, &CMainFrame::OnUpdateAxisesLocal)
ON_COMMAND(ID_AXISES_LOCAL, &CMainFrame::OnAxisesLocal)
ON_COMMAND(ID_AXISES_MAIN, &CMainFrame::OnAxisesMain)
ON_WM_LBUTTONDBLCLK()
//ON_WM_LBUTTONDOWN()
ON_WM_RBUTTONDBLCLK()
ON_COMMAND(ID_DATABASE_LOAD, &CMainFrame::OnDatabaseLoad)
ON_COMMAND(ID_DATABASE_SAVE, &CMainFrame::OnDatabaseSave)
END_MESSAGE_MAP()


static UINT indicators[] =
{
	ID_SEPARATOR,           
	ID_INDICATOR_CAPS,
	ID_INDICATOR_NUM,
	ID_INDICATOR_SCRL,
};


CMainFrame::CMainFrame()
{
}

CMainFrame::~CMainFrame()
{
}


BOOL CMainFrame::PreCreateWindow(CREATESTRUCT& cs)
{
	if( !CFrameWnd::PreCreateWindow(cs) )
		return FALSE;

	return TRUE;
}


#ifdef _DEBUG
void CMainFrame::AssertValid() const
{
	CFrameWnd::AssertValid();
}

void CMainFrame::Dump(CDumpContext& dc) const
{
	CFrameWnd::Dump(dc);
}
#endif //_DEBUG

int CMainFrame::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CWnd::OnCreate(lpCreateStruct) == -1) {
		return -1;
	}

	Title = lpCreateStruct->lpszName;
	Width = lpCreateStruct->cx;
	Height = lpCreateStruct->cy;

	CDC *cDC = GetDC();

	if (cDC == NULL) {
		throw runtime_error("GetDC failed!");
		return -1;
	}

	PIXELFORMATDESCRIPTOR pfd;

	memset(&pfd, 0, sizeof(PIXELFORMATDESCRIPTOR));

	pfd.nSize = sizeof(PIXELFORMATDESCRIPTOR);
	pfd.nVersion = 1;
	pfd.dwFlags = PFD_DRAW_TO_WINDOW | PFD_SUPPORT_OPENGL | PFD_DOUBLEBUFFER;
	pfd.iPixelType = PFD_TYPE_RGBA;
	pfd.cColorBits = 32;
	pfd.cDepthBits = 24;
	pfd.iLayerType = PFD_MAIN_PLANE;

	int PixelFormat = ChoosePixelFormat(*cDC, &pfd);

	if (PixelFormat == 0)
	{
		throw runtime_error("ChoosePixelFormat failed!");
		return -1;
	}

	if (SetPixelFormat(*cDC, PixelFormat, &pfd) == FALSE)
	{
		throw runtime_error("SetPixelFormat failed!");
		return -1;
	}

	hGLRC = wglCreateContext(*cDC);

	if (hGLRC == NULL)
	{
		throw runtime_error("wglCreateContext failed!");
		return -1;
	}

	if (wglMakeCurrent(*cDC, hGLRC) == FALSE) {
		throw runtime_error("wglMakeCurrent failed!");
		return -1;
	}

	if (OpenGLRenderer.Init() == false) {
		return -1;
	}

	return 0;
}

void CMainFrame::OnDestroy()
{
	OpenGLRenderer.Destroy();
	wglDeleteContext(hGLRC);
}

void CMainFrame::OnPaint()
{
	CPaintDC dc(this);

	OpenGLRenderer.Render();// (FrameTime);

	SwapBuffers(dc);

	Invalidate(FALSE);
}

void CMainFrame::OnSize(UINT nType, int cx, int cy)
{
	CWnd::OnSize(nType, cx, cy);

	Width = cx;
	Height = cy;

	OpenGLRenderer.Resize(Width, Height);
}

BOOL CMainFrame::OnMouseWheel(UINT nFlags, short zDelta, CPoint pt)
{
	float k = zDelta / (10.0*abs(zDelta)); //coeff of changing
	switch (nFlags)
	{
		case MK_CONTROL:
			glMatrixMode(GL_PROJECTION);
			glTranslatef(k, 0, 0);
			glMatrixMode(GL_MODELVIEW);
			break;
		case MK_SHIFT:
			glMatrixMode(GL_PROJECTION);
			glTranslatef(0, k, 0);
			glMatrixMode(GL_MODELVIEW);
			break;
		default:
			glMatrixMode(GL_PROJECTION);
			if (OpenGLRenderer.mainAxises)
				glScalef(1 + k, 1 + k, 1 + k);
			else OpenGLRenderer.Scale(k);
			glMatrixMode(GL_MODELVIEW);
			break;
	}
	return 0;
}


void CMainFrame::OnMouseMove(UINT nFlags, CPoint point)
{
	switch (nFlags)
	{
	case MK_LBUTTON://rotate
		if(OpenGLRenderer.prevX != -1) {
			if (!OpenGLRenderer.mainAxises) {
				OpenGLRenderer.RotateLocal((OpenGLRenderer.prevY - point.y) / (float)10, (OpenGLRenderer.prevX - point.x) / (float)10, 0);
			}
			else{
				OpenGLRenderer.RotateTotal((OpenGLRenderer.prevY - point.y) / (float)180, (OpenGLRenderer.prevX - point.x) / (float)180, 0);
			}
		}
		OpenGLRenderer.prevX = point.x;
		OpenGLRenderer.prevY = point.y;
		break;
	case MK_RBUTTON://rotate
		if (OpenGLRenderer.prevX != -1) {
			if (!OpenGLRenderer.mainAxises)
				OpenGLRenderer.RotateLocal(0, 0, -(OpenGLRenderer.prevX - point.x) / (float)10);
			else {
				OpenGLRenderer.RotateTotal(0, 0, (OpenGLRenderer.prevX - point.x) / (float)180);
			}
		}
		OpenGLRenderer.prevX = point.x;
		break;
	case MK_CONTROL://Shift
		if (OpenGLRenderer.prevX != -1  && OpenGLRenderer.prevY != -1) {
			OpenGLRenderer.Shift(4 * (OpenGLRenderer.prevX - point.x) / (float)min(Width, Height), 4 * (OpenGLRenderer.prevY - point.y) / (float)min(Width, Height), 0);
		}
		OpenGLRenderer.prevX = point.x;
		OpenGLRenderer.prevY = point.y;
		break;
	case MK_SHIFT://Shift
		if (OpenGLRenderer.prevX != -1) {
			OpenGLRenderer.Shift(0, 0, 4 * (OpenGLRenderer.prevX - point.x) / (float)min(Width, Height));
		}
		OpenGLRenderer.prevX = point.x;
		break;
	default:
		OpenGLRenderer.prevX = -1;;
		break;
	}

	CFrameWnd::OnMouseMove(nFlags, point);
}

void CMainFrame::OnUpdateAxisesMain(CCmdUI *pCmdUI)
{
	// TODO: Add your command update UI handler code here
	pCmdUI->Enable();
	pCmdUI->SetRadio(OpenGLRenderer.mainAxises);
}


void CMainFrame::OnUpdateAxisesLocal(CCmdUI *pCmdUI)
{
	// TODO: Add your command update UI handler code here
	pCmdUI->Enable();
	pCmdUI->SetRadio(!OpenGLRenderer.mainAxises);
}


void CMainFrame::OnAxisesLocal()
{
	OpenGLRenderer.mainAxises = false;
}


void CMainFrame::OnAxisesMain()
{
	// TODO: Add your command handler code here
	OpenGLRenderer.mainAxises = true;
}


void CMainFrame::OnLButtonDblClk(UINT nFlags, CPoint point)
{
	OpenGLRenderer.addShape(0, 4 * (Width/2 - point.x) / (float)min(Width, Height), 4 * (Height/2 - point.y) / (float)min(Width, Height));

	CFrameWnd::OnLButtonDblClk(nFlags, point);
}


void CMainFrame::OnRButtonDblClk(UINT nFlags, CPoint point)
{
	OpenGLRenderer.Select(4 * (Width / 2 - point.x) / (float)min(Width, Height), 4 * (Height / 2 - point.y) / (float)min(Width, Height));

	CFrameWnd::OnRButtonDblClk(nFlags, point);
}

int callback(void *rendererVoid, int argc, char **argv, char **azColName) {
	COpenGLRenderer* OpenGLRenderer = static_cast<COpenGLRenderer*>(rendererVoid);

	string type = argv[0];

	string localAngelX = argv[1];
	string localAngelY = argv[2];
	string localAngelZ = argv[3];

	string totalSaveAngelX = argv[4];
	string totalSaveAngelY = argv[5];
	string totalSaveAngelZ = argv[6];

	string totalSaveShiftX = argv[7];
	string totalSaveShiftY = argv[8];
	string totalSaveShiftZ = argv[9];

	string scale = argv[10];
	OpenGLRenderer->addShape(stoi(type), 0, 0);

	OpenGLRenderer->RotateLocal(-stof(localAngelX), -stof(localAngelY), -stof(localAngelZ));
	OpenGLRenderer->Shift(0, 0, stof(totalSaveShiftZ));
	OpenGLRenderer->Shift(stof(totalSaveShiftX), stof(totalSaveShiftY), 0);
	OpenGLRenderer->RotateTotal(-stof(totalSaveAngelX), -stof(totalSaveAngelY), -stof(totalSaveAngelZ));
	OpenGLRenderer->Scale(stof(scale)-1);

	//OpenGLRenderer->saveSelectedPos();

	return 0;
}


void CMainFrame::OnDatabaseLoad()
{
	vector<Shape*>& shapes = OpenGLRenderer.getShapes();
	shapes.clear();
	//OpenGLRenderer.clearMatrix();

	char* err;
	string SQLReadAll = "SELECT * FROM Shapes;";

	if (sqlite3_open("db.sqlite", &db)) {
		fprintf(stderr, "Open/Create error: %s\n", sqlite3_errmsg(db));
	}
	else if (sqlite3_exec(db, SQLReadAll.c_str(), callback, &OpenGLRenderer, &err)) {
		fprintf(stderr, "SQL error: %s\n", err);
		sqlite3_free(err);
	}
}

void CMainFrame::OnDatabaseSave()
{
	vector<Shape*>& shapes = OpenGLRenderer.getShapes();
	char* err;
	string SQLReCreate = "DROP TABLE IF EXISTS Shapes; CREATE TABLE IF NOT EXISTS Shapes(\
		type,\
		localAngelX,localAngelY,localAngelZ,\
		totalSaveAngelX,totalSaveAngelY,totalSaveAngelZ,\
		totalSaveShiftX,totalSaveShiftY,totalSaveShiftZ,\
		scale);";

	if (sqlite3_open("db.sqlite", &db)) {
		fprintf(stderr, "Open/Create error: %s\n", sqlite3_errmsg(db));
	}
	else
	{
		if (sqlite3_exec(db, SQLReCreate.c_str(), 0, 0, &err)) {
			fprintf(stderr, "SQL error: %s\n", err);
			sqlite3_free(err);
		}
		else {
			for (int i = 0; i < shapes.size(); i++) {
				string SQLSave = "INSERT INTO Shapes VALUES(" + to_string(shapes[i]->getType())
					+ "," + to_string(shapes[i]->getLocalAngelX())
					+ "," + to_string(shapes[i]->getLocalAngelY())
					+ "," + to_string(shapes[i]->getLocalAngelZ())
					+ "," + to_string(shapes[i]->getTotalSaveAngelX())
					+ "," + to_string(shapes[i]->getTotalSaveAngelY())
					+ "," + to_string(shapes[i]->getTotalSaveAngelZ())
					+ "," + to_string(shapes[i]->getTotalSaveShiftX())
					+ "," + to_string(shapes[i]->getTotalSaveShiftY())
					+ "," + to_string(shapes[i]->getTotalSaveShiftZ())
					+ "," + to_string(shapes[i]->getScale())
					+ ");";
				if (sqlite3_exec(db, SQLSave.c_str(), 0, 0, &err)) {
					fprintf(stderr, "SQL error: %s\n", err);
					sqlite3_free(err);
				}
			}
		}
	}
	sqlite3_close(db);
}
