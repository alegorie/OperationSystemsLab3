#include <windows.h>													
#include <tchar.h>


LRESULT CALLBACK WndProc(HWND hwnd, UINT Message, WPARAM wParam, LPARAM lParam);
HINSTANCE g_hInst;

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)														//Markov KM-42
{
	HWND    hwnd;
	MSG     Msg;
	HICON   hIcon;
	HCURSOR hCursor;
	TCHAR chClassName[] = TEXT("ClassName");
	WNDCLASSEX wcx;
	g_hInst = hInstance;

	hIcon = (HICON)LoadImage(0, IDI_APPLICATION, IMAGE_ICON, 0, 0, LR_SHARED); //ExtractIcon(hInstance, "icon.ico", 1); 
	hCursor = (HCURSOR)LoadImage(0, IDC_ARROW, IMAGE_CURSOR, 1, 1, LR_SHARED);
	wcx.cbSize = sizeof(WNDCLASSEX);					// size of structure 
	wcx.style = CS_HREDRAW | CS_VREDRAW;				//redraw if size changes
	wcx.lpfnWndProc = (WNDPROC)WndProc;					// points to window procedure
	wcx.cbClsExtra = 0;									// no extra class memory 
	wcx.cbWndExtra = 0;									// no extra window memory 
	wcx.hInstance = hInstance;							// handle to instance
	wcx.hIcon = hIcon;									// predefined app. icon 
	wcx.hCursor = hCursor;								// predefined arrow 
	wcx.hbrBackground = (HBRUSH)(COLOR_BTNFACE - 14);	// background brush https://msdn.microsoft.com/ru-ru/library/windows/desktop/ms724371(v=vs.85).aspx
	wcx.lpszMenuName = NULL;							// name of menu resource 
	wcx.lpszClassName = chClassName;					// name of window class 
	wcx.hIconSm = NULL;									// small class icon 

	RegisterClassEx(&wcx);

	hwnd = CreateWindowEx(0,
		chClassName,
		TEXT("TextEditor v 0.4"),
		WS_OVERLAPPEDWINDOW,
		GetSystemMetrics(SM_CXSCREEN) / 4,
		GetSystemMetrics(SM_CYSCREEN) / 4,
		GetSystemMetrics(SM_CXSCREEN) / 2.5,
		GetSystemMetrics(SM_CYSCREEN) / 2.5,
		NULL,
		NULL,
		hInstance,
		NULL);

	ShowWindow(hwnd, nCmdShow);
	UpdateWindow(hwnd);
	
	

	while (GetMessage(&Msg, NULL, 0, 0) > 0)
	{
		TranslateMessage(&Msg);
		DispatchMessage(&Msg);
	}
	return Msg.wParam;
}

//-----------------------------------------------------------------------------

LRESULT CALLBACK WndProc(HWND hwnd, UINT Message, WPARAM wParam, LPARAM lParam)
{
	RECT rct;
	// UINT Message = 0;
	//UINT Message = RegisterWindowMessage(Message);

	switch (Message)
	{
	case WM_CREATE:
		GetClientRect(hwnd, &rct);
		CreateWindowEx(WS_EX_CLIENTEDGE,                      //_In_     DWORD     dwExStyle,
			TEXT("EDIT"),									  //_In_opt_ LPCTSTR   lpClassName,
			TEXT("������ ��� �����"),						  //_In_opt_ LPCTSTR   lpWindowName,
			WS_CHILD | WS_VISIBLE | WS_BORDER |ES_MULTILINE,  //_In_     DWORD     dwStyle,
			10,												  //_In_     int       x,
			15,												  //_In_     int       y,
			rct.right - 20,									  //_In_     int       nWidth,
			rct.bottom - 25,								  //_In_     int       nHeight,
			hwnd,											  //_In_opt_ HWND      hWndParent,
			NULL,											  //_In_opt_ HMENU     hMenu,
			g_hInst,										  //_In_opt_ HINSTANCE hInstance,
			NULL);											  //_In_opt_ LPVOID    lpParam
		return 0;
	case WM_DESTROY:
		PostQuitMessage(0);
		return 0;
	default:
		return DefWindowProc(hwnd, Message, wParam, lParam);
	}
}

/*Ex4_Menu MENU
{
POPUP "&File"
{
MENUITEM "&Open...\tCtrl-O", 2
MENUITEM "&Save", 3
MENUITEM "Save &As...", 4
MENUITEM SEPARATOR
MENUITEM "&Hex view", 5, CHECKED GRAYED
MENUITEM "&Exit\tAlt-F4", 6
}
POPUP "&Edit"
{
MENUITEM "&Copy", 7
MENUITEM "&Paste", 8
POPUP "Popup"
{
MENUITEM "1", 9
MENUITEM "2", 10
MENUITEM "3", 11
}
MENUITEM SEPARATOR
MENUITEM "Search", 12
}
POPUP "&Help"
{
MENUITEM "&About...\tF1", 13
}
*/