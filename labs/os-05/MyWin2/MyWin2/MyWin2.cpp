
#include "stdafx.h"
#include <string>
#include <stdio.h>
#include "Resource.h"

#define MAX_LOADSTRING 100

// Global Variables:
HINSTANCE hInst;								// current instance
TCHAR szTitle[MAX_LOADSTRING];					// The title bar text
TCHAR szWindowClass[MAX_LOADSTRING];			// the main window class name

int dx = 8;
int dy = 8;

// Forward declarations of functions included in this code module:
HWND hPressMeBtn;
HWND hExitBtn;

ATOM MyRegisterClass(HINSTANCE hInstance);
BOOL InitInstance(HINSTANCE, int);
LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK About(HWND, UINT, WPARAM, LPARAM);
LRESULT CALLBACK myF(HWND, UINT, WPARAM, LPARAM);
int row = 1, column = 1;

int APIENTRY _tWinMain(HINSTANCE hInstance,
	HINSTANCE hPrevInstance,
	LPTSTR    lpCmdLine,
	int       nCmdShow)
{
	UNREFERENCED_PARAMETER(hPrevInstance);
	UNREFERENCED_PARAMETER(lpCmdLine);

	// TODO: Place code here.
	MSG msg;
	HACCEL hAccelTable;

	// Initialize global strings
	LoadString(hInstance, IDS_APP_TITLE, szTitle, MAX_LOADSTRING);
	LoadString(hInstance, IDC_MYWIN2, szWindowClass, MAX_LOADSTRING);
	MyRegisterClass(hInstance);

	// Perform application initialization:
	if (!InitInstance(hInstance, nCmdShow))
	{
		return FALSE;
	}

	hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_MYWIN2));

	// Main message loop:
	while (GetMessage(&msg, NULL, 0, 0))
	{
		if (!TranslateAccelerator(msg.hwnd, hAccelTable, &msg))
		{
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
	}

	return (int)msg.wParam;
}


ATOM MyRegisterClass(HINSTANCE hInstance)
{
	WNDCLASSEX wcex;

	wcex.cbSize = sizeof(WNDCLASSEX);

	wcex.style = CS_HREDRAW | CS_VREDRAW;
	wcex.lpfnWndProc = WndProc;
	wcex.cbClsExtra = 0;
	wcex.cbWndExtra = 0;
	wcex.hInstance = hInstance;
	wcex.hIcon = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_MYWIN2));
	wcex.hCursor = LoadCursor(NULL, IDC_ARROW);
	wcex.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
	wcex.lpszMenuName = MAKEINTRESOURCE(IDC_MYWIN2);
	wcex.lpszClassName = szWindowClass;
	wcex.hIconSm = LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_SMALL));

	return RegisterClassEx(&wcex);
}


BOOL InitInstance(HINSTANCE hInstance, int nCmdShow)
{
	HWND hWnd;

	hInst = hInstance; // Store instance handle in our global variable

	hWnd = CreateWindow(szWindowClass, szTitle, WS_OVERLAPPEDWINDOW,
		CW_USEDEFAULT, 0, CW_USEDEFAULT, 0, NULL, NULL, hInstance, NULL);

	if (!hWnd)
	{
		return FALSE;
	}

	HBRUSH brush = CreateSolidBrush(RGB(0, 100, 100));
	SetClassLongPtr(hWnd, GCLP_HBRBACKGROUND, (LONG)brush);
	ShowWindow(hWnd, nCmdShow);
	UpdateWindow(hWnd);

	return TRUE;
}


LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	int wmId, wmEvent;
	PAINTSTRUCT ps;
	HDC hdc;
	TCHAR szHello[MAX_LOADSTRING];
	TCHAR str[] = TEXT("BIG MAG");
	static HBRUSH testBrush = CreateSolidBrush(RGB(0, 0, 255));;

	LoadString(hInst, IDS_HELLO, szHello, MAX_LOADSTRING);

	switch (message)
	{
	case WM_CREATE:
		// create PressButton
		hPressMeBtn = CreateWindowEx(NULL,
			L"BUTTON",
			L"PressMe",
			WS_TABSTOP | WS_VISIBLE |
			WS_CHILD | BS_DEFPUSHBUTTON | BS_OWNERDRAW,
			100,
			100,
			100,
			24,
			hWnd,
			HMENU(IDC_PressMeButton),
			hInst,
			NULL);
		ShowWindow(hPressMeBtn, 1);
		
		// create ExitButton
		hExitBtn = CreateWindowEx(NULL,
			L"BUTTON",
			L"Exit",
			WS_TABSTOP | WS_VISIBLE |
			WS_CHILD | BS_DEFPUSHBUTTON,
			300,
			100,
			100,
			24,
			hWnd,
			HMENU(IDC_ExitButton),
			hInst,
			NULL);
		ShowWindow(hExitBtn, 1);
		break;
	case WM_DRAWITEM:
	{
		LPDRAWITEMSTRUCT Item = (LPDRAWITEMSTRUCT)lParam;

		SetBkMode(Item->hDC, TRANSPARENT);
		SetTextColor(Item->hDC, 0xFFFFFF);

		FillRect(Item->hDC, &Item->rcItem, (HBRUSH)GetStockObject(BLACK_BRUSH));

		int len = GetWindowTextLength(Item->hwndItem);
		char* buf = new char[len + 1];
		GetWindowTextA(Item->hwndItem, buf, len + 1);
		DrawTextA(Item->hDC, buf, len, &Item->rcItem, DT_CENTER);

		return true;
	}
	case WM_COMMAND:
		wmId = LOWORD(wParam);
		wmEvent = HIWORD(wParam);

		// if PressButton has been clicked
		if (LOWORD(wParam) == IDC_PressMeButton &&
			HIWORD(wParam) == BN_CLICKED &&
			(HWND)lParam == hPressMeBtn)
		{
			DialogBox(hInst, (LPCTSTR)IDD_DIALOG1, hWnd, (DLGPROC)myF);
		}

		// if ExitButton has been clicked
		if (LOWORD(wParam) == IDC_ExitButton &&
			HIWORD(wParam) == BN_CLICKED &&
			(HWND)lParam == hExitBtn)
		{
			DestroyWindow(hWnd);
		}

		// Parse the menu selections:
		switch (wmId)
		{

		case IDM_ABOUT:
			DialogBox(hInst, (LPCTSTR)IDD_ABOUTBOX, hWnd, (DLGPROC)About);
			break;

		case IDM_EXIT:
			DestroyWindow(hWnd);
			break;
		default:
			return DefWindowProc(hWnd, message, wParam, lParam);
		}
		break;

	case WM_RBUTTONDOWN:
		DialogBox(hInst, (LPCTSTR)IDD_DIALOG1, hWnd, (DLGPROC)myF);
		break;

	case WM_KEYDOWN:
		hdc = GetDC(hWnd);
		InvalidateRect(hWnd, 0, TRUE);
		UpdateWindow(hWnd);
		SetBkColor(hdc, RGB(255, 0, 0));

		SetTextColor(hdc, RGB(255, 255, 255));
		switch (wParam)
		{
		case VK_DOWN:
			TextOut(hdc, column, row += dy, str, 7);
			break;
		case VK_UP:
			TextOut(hdc, column, row -= dy, str, 7);
			break;
		case VK_RIGHT:
			TextOut(hdc, column += dx, row, str, 7);
			break;
		case VK_LEFT:
			TextOut(hdc, column -= dx, row, str, 7);
			break;
		default:
			TextOut(hdc, column, row, str, sizeof(str) / sizeof(TCHAR));
			break;
		}
	case WM_PAINT:
		hdc = BeginPaint(hWnd, &ps);
		// TODO: Add any drawing code here...
		EndPaint(hWnd, &ps);
		break;
	case WM_DESTROY:
		PostQuitMessage(0);
		break;
	default:
		return DefWindowProc(hWnd, message, wParam, lParam);
	}
	return 0;
}

LRESULT CALLBACK myF(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
	static HBRUSH testBrush;
	static HDC dcOne = NULL;

	UNREFERENCED_PARAMETER(lParam);

	switch (message)
	{
	case WM_INITDIALOG:
		testBrush = CreateSolidBrush(RGB(0, 0, 255));
		return (INT_PTR)TRUE;

	case WM_CTLCOLORDLG:
		return (INT_PTR)(testBrush);

	case WM_CTLCOLORBTN:
		return (INT_PTR)testBrush;

	case WM_COMMAND:
		if (LOWORD(wParam) == IDOK)
		{
			MessageBoxEx(NULL, TEXT("HELLO"), TEXT("DialogWin"), MB_OK, 0x0459);
			EndDialog(hDlg, LOWORD(wParam));
			return (INT_PTR)TRUE;
		}
		else if (LOWORD(wParam) == IDCANCEL)
		{
			EndDialog(hDlg, LOWORD(wParam));
			return (INT_PTR)TRUE;
		}
		break;
	}
	return (INT_PTR)FALSE;
}


// Message handler for about box.
INT_PTR CALLBACK About(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
	static HBRUSH testBrush;

	UNREFERENCED_PARAMETER(lParam);
	switch (message)
	{
	case WM_INITDIALOG:
		testBrush = CreateSolidBrush(RGB(90, 100, 255));
		return (INT_PTR)TRUE;
	case WM_CTLCOLORDLG:
		return (INT_PTR)testBrush;
	case WM_CTLCOLORBTN:
		return (INT_PTR)testBrush;
	case WM_COMMAND:
		if (LOWORD(wParam) == IDOK || LOWORD(wParam) == IDCANCEL)
		{
			EndDialog(hDlg, LOWORD(wParam));
			return (INT_PTR)TRUE;
		}
		break;
	}
	return (INT_PTR)FALSE;
}
