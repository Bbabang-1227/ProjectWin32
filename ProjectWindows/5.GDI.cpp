// ProjectWindows.cpp : ���ø����̼ǿ� ���� �������� �����մϴ�.
//
//#define ON_MAIN
#ifdef ON_MAIN
// ProjectWindows.cpp : ���ø����̼ǿ� ���� �������� �����մϴ�.
//

#include "framework.h"
#include "ProjectWindows.h"

#define MAX_LOADSTRING 100
#define MAX_LOADSTRING2 'windowkiki'

// ���� ����:
HINSTANCE hInst;                                // ���� �ν��Ͻ��Դϴ�.
WCHAR szTitle[MAX_LOADSTRING];                  // ���� ǥ���� �ؽ�Ʈ�Դϴ�.
WCHAR szWindowClass[MAX_LOADSTRING];            // �⺻ â Ŭ���� �̸��Դϴ�.

// �� �ڵ� ��⿡ ���Ե� �Լ��� ������ �����մϴ�:
ATOM                MyRegisterClass(HINSTANCE hInstance);
BOOL                InitInstance(HINSTANCE, int);
LRESULT CALLBACK    WndProc(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK    About(HWND, UINT, WPARAM, LPARAM);

int APIENTRY wWinMain(// main
	_In_ HINSTANCE hInstance, //�������α׷��� �ĺ��ϴ� �� 
	_In_opt_ HINSTANCE hPrevInstance, // ���� ����� �ν��Ͻ��� �ڵ�
	_In_ LPWSTR    lpCmdLine, //���������� ��ο� ������� ������ ���� ���ڿ� ������
	_In_ int       nCmdShow) // �����츦 ȭ�鿡 �����ִ� ����� ���
{
	UNREFERENCED_PARAMETER(hPrevInstance);
	UNREFERENCED_PARAMETER(lpCmdLine);

	// TODO: ���⿡ �ڵ带 �Է��մϴ�.

	// ���� ���ڿ��� �ʱ�ȭ�մϴ�.
	LoadStringW(hInstance, IDS_APP_TITLE, szTitle, MAX_LOADSTRING);
	LoadStringW(hInstance, IDC_PROJECTWINDOWS, szWindowClass, MAX_LOADSTRING);
	MyRegisterClass(hInstance);

	// ���ø����̼� �ʱ�ȭ�� �����մϴ�:
	if (!InitInstance(hInstance, nCmdShow))
	{

		return FALSE;
	}

	HACCEL hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_PROJECTWINDOWS));

	/*
	C/C++ �� �Լ��� ���� ȣ���Ͽ����� ��ü ���� �帧�� �ڵ忡 ����Ҽ��־���
	�׷��� ������ ���α׷����� �Է��� �����Ҽ�����(�񵿱�)
	���� �߻����� �𸣴� �񵿱� �Է¿� ���� ó���� �����ϸ鼭�� ȭ���� ���������ƾ��Ѵ�
	���� ������ ���α׷��� ���� Message Driven ����� ä��
	*/
	MSG msg;

	// �⺻ �޽��� �����Դϴ�:
	while (GetMessage(&msg, nullptr, 0, 0))
	{
		if (!TranslateAccelerator(msg.hwnd, hAccelTable, &msg))
		{
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
	}

	return (int)msg.wParam;
}



//
//  �Լ�: MyRegisterClass()
//
//  �뵵: â Ŭ������ ����մϴ�.
//
ATOM MyRegisterClass(HINSTANCE hInstance)
{
	WNDCLASSEXW wcex;

	wcex.cbSize = sizeof(WNDCLASSEX);

	wcex.style = CS_HREDRAW | CS_VREDRAW;
	wcex.lpfnWndProc = WndProc;
	wcex.cbClsExtra = 0;
	wcex.cbWndExtra = 0;
	wcex.hInstance = hInstance;
	wcex.hIcon = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_PROJECTWINDOWS));
	wcex.hCursor = LoadCursor(nullptr, IDC_ARROW);
	wcex.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
	wcex.lpszMenuName = MAKEINTRESOURCEW(IDC_PROJECTWINDOWS);
	wcex.lpszClassName = szWindowClass;
	wcex.hIconSm = LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_SMALL));

	return RegisterClassExW(&wcex);
}

//
//   �Լ�: InitInstance(HINSTANCE, int)
//
//   �뵵: �ν��Ͻ� �ڵ��� �����ϰ� �� â�� ����ϴ�.
//
//   �ּ�:
//
//        �� �Լ��� ���� �ν��Ͻ� �ڵ��� ���� ������ �����ϰ�
//        �� ���α׷� â�� ���� ���� ǥ���մϴ�.
//
BOOL InitInstance(HINSTANCE hInstance, int nCmdShow)
{
	hInst = hInstance; // �ν��Ͻ� �ڵ��� ���� ������ �����մϴ�.

	HWND hWnd = CreateWindowW(szWindowClass, szTitle, WS_OVERLAPPEDWINDOW,
		CW_USEDEFAULT, 0, CW_USEDEFAULT, 0, nullptr, nullptr, hInstance, nullptr); // �����츦 ����

	if (!hWnd)
	{
		return FALSE;
	}

	ShowWindow(hWnd, nCmdShow);
	UpdateWindow(hWnd);

	return TRUE;
}

//
//  �Լ�: WndProc(HWND, UINT, WPARAM, LPARAM)
//
//  �뵵: �� â�� �޽����� ó���մϴ�.
//
//  WM_COMMAND  - ���ø����̼� �޴��� ó���մϴ�.
//  WM_PAINT    - �� â�� �׸��ϴ�.
//  WM_DESTROY  - ���� �޽����� �Խ��ϰ� ��ȯ�մϴ�.
//
//
LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	switch (message)
	{
	case WM_COMMAND:
	{
		int wmId = LOWORD(wParam);
		// �޴� ������ ���� �м��մϴ�:
		switch (wmId)
		{
		case IDM_ABOUT:
			//DialogBox(hInst, MAKEINTRESOURCE(IDD_ABOUTBOX), hWnd, About);
			break;
		case IDM_EXIT:
			DestroyWindow(hWnd);
			break;
		default:
			return DefWindowProc(hWnd, message, wParam, lParam);
		}
	}
	break;
	case WM_PAINT:
	if(0) // stack object 
	{
		PAINTSTRUCT ps;
		HDC hdc = BeginPaint(hWnd, &ps);
		HBRUSH MyBr = (HBRUSH)GetStockObject(GRAY_BRUSH); //HGDIOBJ GetStockObject(int i); ���� ����ȯ �ʿ�
		HBRUSH OldBr = (HBRUSH)SelectObject(hdc, MyBr);
		Rectangle(hdc, 0, 0, 300, 300);
		SelectObject(hdc, MyBr);
		// TODO: ���⿡ hdc�� ����ϴ� �׸��� �ڵ带 �߰��մϴ�...

		HBRUSH MyBr2 = (HBRUSH)GetStockObject(BLACK_BRUSH);
		SelectObject(hdc, MyBr2);
		Rectangle(hdc, 60, 60, 360, 360);
		SelectObject(hdc, OldBr);
		Rectangle(hdc, 120, 120, 420, 420);
		EndPaint(hWnd, &ps);
	}
	if (1) // ������ �귯�� ����
	{
		PAINTSTRUCT ps;
		HDC hdc = BeginPaint(hWnd, &ps);

		CreateSolidBrush(RGB(255,0,0));
		HBRUSH MyBr2 = CreateSolidBrush(RGB(255, 0, 0));
		HBRUSH MyBr3 = CreateHatchBrush(HS_BDIAGONAL,RGB(255, 0, 0));
		HBRUSH OldBr = (HBRUSH)SelectObject(hdc, MyBr2);
		
		SelectObject(hdc, OldBr);
		Rectangle(hdc, 60, 60, 360, 360);
		SelectObject(hdc, MyBr2);
		Rectangle(hdc, 0, 0, 300, 300);

		EndPaint(hWnd, &ps);
	}
	if (0) // ������ �� ����
	{
		PAINTSTRUCT ps;
		HDC hdc = BeginPaint(hWnd, &ps);
				
		HPEN MyPen = CreatePen(PS_DASHDOTDOT, 1, RGB(255, 0, 0));
		HPEN OldPen = (HPEN)SelectObject(hdc, MyPen);
		SelectObject(hdc, MyPen);
		Rectangle(hdc, 20, 20, 300, 300);
		SelectObject(hdc, OldPen);
		Rectangle(hdc, 100, 100, 400, 400);

		EndPaint(hWnd, &ps);
	}
	break;
	case WM_MOUSEMOVE:
	{
		if (0)
		{
		HDC hdc;
		hdc = GetDC(hWnd);
		int x, y, hr;
		x = rand() % 440;
		y = rand() % 240;
		hr = rand() % 100;
		HBRUSH MyBr2 = CreateSolidBrush(RGB(rand()%256, rand() % 256, rand() % 256));
		HBRUSH OldBr = (HBRUSH)SelectObject(hdc, MyBr2);
		HPEN MyPen = CreatePen(PS_SOLID, rand()%11, RGB(rand() % 256, rand() % 256, rand() % 256));
		HPEN OldPen = (HPEN)SelectObject(hdc, MyPen);
		SelectObject(hdc, MyBr2);
		SelectObject(hdc, MyPen);

		Rectangle(hdc, x - hr, y - hr, x + hr, y + hr);
		Ellipse(hdc, x - hr/2, y - hr/2, x + hr/2, y + hr/2);
		Arc(hdc, x - hr / 3, y - hr / 3, x + hr / 3, y + hr / 4 , x - hr / 4, y - hr / 4, x + hr / 4, y + hr / 4);

		ReleaseDC(hWnd , hdc);
		}
		break;
	}
	case WM_LBUTTONDOWN:
	{
		InvalidateRect(hWnd, NULL, TRUE);
		break;
	}
	case WM_DESTROY:
		PostQuitMessage(0);
		break;
	default:
		return DefWindowProc(hWnd, message, wParam, lParam);
	}
	return 0;
}

// ���� ��ȭ ������ �޽��� ó�����Դϴ�.


#endif  

