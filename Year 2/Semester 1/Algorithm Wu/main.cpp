#include <windows.h> 
#include "math.h"
#include "algoWu.h"

LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);

										 
int WINAPI WinMain(HINSTANCE hInst, 
	HINSTANCE hPrevInst,
	LPSTR lpCmdLine,
	int nCmdShow)
{
	//WinAPI window initialzation
	TCHAR szClassName[] = L"Ellipse Wu";
	HWND hMainWnd; 
	MSG msg; 
	WNDCLASSEX wc; 
	wc.cbSize = sizeof(wc);
	wc.style = CS_HREDRAW | CS_VREDRAW;
	wc.lpfnWndProc = WndProc; 
	wc.lpszMenuName = NULL; 
	wc.lpszClassName = szClassName; 
	wc.cbWndExtra = NULL; 
	wc.cbClsExtra = NULL;
	wc.hIcon = LoadIcon(NULL, IDI_WINLOGO);
	wc.hIconSm = LoadIcon(NULL, IDI_WINLOGO);
	wc.hCursor = LoadCursor(NULL, IDC_ARROW);
	wc.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH);
	wc.hInstance = hInst;
	if (!RegisterClassEx(&wc)) {
		MessageBox(NULL, L"Cant register class", L"Error", MB_OK);
		return NULL;
	}
	hMainWnd = CreateWindow(
		szClassName,
		L"Ellipse",
		WS_OVERLAPPEDWINDOW | WS_VSCROLL,
		CW_USEDEFAULT,
		NULL, 
		CW_USEDEFAULT,
		NULL, 
		(HWND)NULL,
		NULL, 
		HINSTANCE(hInst),
		NULL); 
	if (!hMainWnd) {
		MessageBox(NULL, L"Can't create window", L"Error", MB_OK);
		return NULL;
	}
	ShowWindow(hMainWnd, nCmdShow); 
	UpdateWindow(hMainWnd); 
	while (GetMessage(&msg, NULL, NULL, NULL)) { 
		TranslateMessage(&msg); 
		DispatchMessage(&msg);
	}
	return msg.wParam;
}

//Window processing function
LRESULT CALLBACK WndProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam) {
	HDC hDC;
	PAINTSTRUCT ps; 
	RECT rect;
	switch (uMsg) {
	case WM_PAINT: {
		hDC = BeginPaint(hWnd, &ps);
		GetClientRect(hWnd, &rect);

		//Ellipse's params
		const float centerX = 400;
		const float centerY = 200;
		const float radX = 200;
		const float radY = 100;

		algoWuEllipse ellipse(centerX, centerY, radX, radY);
		ellipse.drawEllipse(hDC, RGB(0, 0, 0));

		EndPaint(hWnd, &ps);
	}
		break;
	case WM_DESTROY: 
		PostQuitMessage(NULL);
		break;
	default:
		return DefWindowProc(hWnd, uMsg, wParam, lParam); 
	}
	return NULL;
}
