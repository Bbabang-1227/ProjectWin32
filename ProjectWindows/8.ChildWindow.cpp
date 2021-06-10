// ProjectWindows.cpp : ���ø����̼ǿ� ���� �������� �����մϴ�.
//
#define ON_MAIN
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

//������ ���ν���
LRESULT CALLBACK    ChildLeftProc(HWND, UINT, WPARAM, LPARAM);
LRESULT CALLBACK    ChildTopProc(HWND, UINT, WPARAM, LPARAM);
LRESULT CALLBACK    ChildBottomProc(HWND, UINT, WPARAM, LPARAM);
//������ �ڵ鷯
HWND hC1, hC2, hC3;

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

	wcex.cbSize = sizeof(WNDCLASSEX); // �ݹ��� �ִ� �Լ��� �ݹ��� ���� �����������

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

	RegisterClassExW(&wcex);
	//////////////////////////////////���ϵ� ������ ���
	//1.���� ���ϵ� Ŭ����
	static HBRUSH hRed = CreateSolidBrush(RGB(255, 0, 0));
	wcex.hbrBackground = hRed;
	wcex.lpfnWndProc = ChildLeftProc;
	wcex.lpszClassName = _T("ChildLeft");
	RegisterClassExW(&wcex);
	//2.���� ���ϵ� Ŭ����
	static HBRUSH hGreen = CreateSolidBrush(RGB(0, 255, 0));
	wcex.hbrBackground = hGreen;
	wcex.lpfnWndProc = ChildTopProc;
	wcex.lpszClassName = _T("ChildTop");
	RegisterClassExW(&wcex);
	//�Ʒ��� ���ϵ� Ŭ����
	static HBRUSH hBlue = CreateSolidBrush(RGB(0, 0, 255));
	wcex.hbrBackground = hBlue;
	wcex.lpfnWndProc = ChildBottomProc;
	wcex.lpszClassName = _T("ChildBottom");
	RegisterClassExW(&wcex);


	return  0;
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
HWND mhWnd;
BOOL InitInstance(HINSTANCE hInstance, int nCmdShow)
{
	hInst = hInstance; // �ν��Ͻ� �ڵ��� ���� ������ �����մϴ�.

	mhWnd = CreateWindowW(szWindowClass, szTitle, WS_OVERLAPPEDWINDOW,
		CW_USEDEFAULT, 0, CW_USEDEFAULT, 0, nullptr, nullptr, hInstance, nullptr); // �����츦 ����

	if (!mhWnd)
	{
		return FALSE;
	}

	ShowWindow(mhWnd, nCmdShow);
	UpdateWindow(mhWnd);

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
	case WM_CREATE:
	{
		hC1 = CreateWindow(
			_T("ChildLeft"), //classname
			NULL, //windowname // ���� Ŭ��������, ��������� ���� �Ѱ��� �ο���
			WS_CHILD | WS_VISIBLE | WS_CLIPCHILDREN, //window style
			0, //x
			0, //y
			0, //width
			0, //height
			hWnd, //�θ��ڵ�
			(HMENU)0, //�޴�
			hInst, //
			NULL
		);
		hC2 = CreateWindow(
			_T("ChildTop"), //classname
			NULL, //windowname // ���� Ŭ��������, ��������� ���� �Ѱ��� �ο���
			WS_CHILD | WS_VISIBLE | WS_CLIPCHILDREN, //window style
			0, //x
			0, //y
			0, //width
			0, //height
			hWnd, //�θ��ڵ�
			(HMENU)0, //�޴�
			hInst, //
			NULL
		);
		hC3 = CreateWindow(
			_T("ChildBottom"), //classname
			NULL, //windowname // ���� Ŭ��������, ��������� ���� �Ѱ��� �ο���
			WS_CHILD | WS_VISIBLE | WS_CLIPCHILDREN, //window style
			0, //x
			0, //y
			0, //width
			0, //height
			hWnd, //�θ��ڵ�
			(HMENU)0, //�޴�
			hInst, //
			NULL
		);
		break;
	}
	case WM_SIZE:
		if (wParam != SIZE_MINIMIZED)
		{
			RECT rct;
			GetClientRect(hWnd, &rct);
			MoveWindow(hC1, 0, 0, 300, rct.bottom, TRUE);
			MoveWindow(hC2, 300, 0, rct.right - 300, 150, TRUE);
			MoveWindow(hC3, 300, 150, rct.right - 300, rct.bottom - 150, TRUE);
		}

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
	case WM_KEYDOWN:
	{
		switch (wParam)
		{
		case VK_SPACE:
			DestroyWindow(hWnd);
			break;
		default:
			break;
		}
	}break;
	case WM_PAINT:
	{
		PAINTSTRUCT ps;
		HDC hdc = BeginPaint(hWnd, &ps);
		// TODO: ���⿡ hdc�� ����ϴ� �׸��� �ڵ带 �߰��մϴ�...
		EndPaint(hWnd, &ps);
	}
	break;
	case WM_DESTROY:
		PostQuitMessage(0);
		break;
	default:
		return DefWindowProc(hWnd, message, wParam, lParam);
	}
	return 0;
}

//child
LRESULT CALLBACK ChildLeftProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	static HWND hEdit, hBtn;
	switch (message)
	{
	case WM_CREATE:
	{
		hEdit = CreateWindowW( // �����츦 ����
			_T("edit"), //Ŭ��������
			NULL, // ���������
			WS_CHILD | WS_VISIBLE | WS_BORDER | ES_AUTOHSCROLL, // ������ ��Ÿ��
			210, 10, 80, 25, // ������
			hWnd, // �θ� 
			(HMENU)1, // ID�ο�
			hInst,
			NULL);
		hBtn = CreateWindowW( // �����츦 ����
			_T("button"), //Ŭ��������
			_T("Add"), // ���������
			WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON, // ������ ��Ÿ��
			210, 50, 80, 25, // ������
			hWnd, // �θ� 
			(HMENU)2, // ID�ο�
			hInst,
			NULL);

	}
	case WM_COMMAND:
	{
		switch (LOWORD(wParam))
		{
		case 2:
		{
			TCHAR str[256];

			//1.edit â�� ���ڸ� �д´�
			GetWindowText(hEdit, str, 256);
			//2. �� ���ڸ� ����â������
			SetWindowText(mhWnd, str);
			//3. edit init
			SetWindowText(hEdit, NULL);

			break;
		}
		default:
			break;
		}
		break;
	}
	default:
		return DefWindowProc(hWnd, message, wParam, lParam);
	}
	return 0;
}

LRESULT CALLBACK ChildTopProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	switch (message)
	{
	case WM_PAINT:
	{
		PAINTSTRUCT ps;
		HDC hdc = BeginPaint(hWnd, &ps);
		// TODO: ���⿡ hdc�� ����ϴ� �׸��� �ڵ带 �߰��մϴ�...
		SetBkMode(hdc, TRANSPARENT);
		TextOut(hdc, 10, 10, _T("���������ּ���"), 7);
		EndPaint(hWnd, &ps);
		break;
	}
	default:
		return DefWindowProc(hWnd, message, wParam, lParam);
	}
	return 0;
}

LRESULT CALLBACK ChildBottomProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	static HWND hEdit;
	switch (message)
	{
	case WM_CREATE:
	{
		hEdit = CreateWindowW( // �����츦 ����
			_T("edit"), //Ŭ��������
			NULL, // ���������
			WS_CHILD | WS_VISIBLE | WS_BORDER | ES_AUTOHSCROLL | WS_VSCROLL | ES_MULTILINE, // ������ ��Ÿ��
			10, 10, 500, 500, // ������
			hWnd, // �θ� 
			(HMENU)1, // ID�ο�
			hInst,
			NULL);
		SetWindowText(hEdit, _T("�ϰ�������� �غ��ʼ�"));
		break;
	}
	default:
		return DefWindowProc(hWnd, message, wParam, lParam);
	}
	return 0;
}

// ���� ��ȭ ������ �޽��� ó�����Դϴ�.


#endif  

