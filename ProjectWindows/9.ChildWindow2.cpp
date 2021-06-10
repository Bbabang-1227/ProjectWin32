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

LRESULT CALLBACK    ChildProc(HWND, UINT, WPARAM, LPARAM); //child
HWND hC1;

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
	//child
	wcex.hCursor = LoadCursor(nullptr, IDC_CROSS);
	wcex.hbrBackground = (HBRUSH)GetStockObject(GRAY_BRUSH);
	wcex.lpfnWndProc = ChildProc;
	wcex.lpszClassName = _T("lpszClass");
	RegisterClassExW(&wcex);

	return 0;
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

	HWND mhWnd = CreateWindowW(szWindowClass, szTitle, WS_OVERLAPPEDWINDOW,
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
HDC hdc;
LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	switch (message)
	{
	case WM_CREATE:
	{
		for (int i = 0; i < 3; i++)
		{
			for (int j = 0; j < 3; j++)
			{
				hC1 = CreateWindow(
					_T("lpszClass"), //classname
					NULL, //windowname // ���� Ŭ��������, ��������� ���� �Ѱ��� �ο���
					WS_CHILD | WS_VISIBLE | WS_CLIPCHILDREN, //window style
					0 + 100 * i, //x
					0 + 100 * j, //y
					100, //width
					100, //height
					hWnd, //�θ��ڵ�
					(HMENU)0, //�޴�
					hInst, //
					NULL
				);
			}
		}
		
		break;
	}
	
	case WM_LBUTTONDOWN:
	{
		RECT rct;
		GetClientRect(hWnd, &rct);
		TextOut(hdc, 320, 20, _T("���������ּ���"), 7);


		break;
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
		hdc = BeginPaint(hWnd, &ps);
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

BOOL bEllipse = TRUE;

LRESULT CALLBACK ChildProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	static HWND hEdit, hBtn;
	BOOL bProp;
	
	switch (message)
	{
	case WM_CREATE:
	{
		SetProp(hWnd, _T("bEllipse"), (HANDLE)TRUE); //1. �Ӽ� ����
		SetProp(hWnd, _T("nCount"), (HANDLE)3); //�Ӽ� ����
		/*
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
		*/
		
		break;
	}
	case WM_PAINT:
	{
		PAINTSTRUCT ps;
		HDC hdc2 = BeginPaint(hWnd, &ps);
		// TODO: ���⿡ hdc�� ����ϴ� �׸��� �ڵ带 �߰��մϴ�...		
		bProp = (BOOL)GetProp(hWnd, _T("bEllipse"));
		if (bProp)
		{
			Ellipse(hdc2, 10, 10, 90, 90);
		}
		else
		{
			MoveToEx(hdc2, 10, 10, NULL);
			LineTo(hdc2, 90, 90);
			MoveToEx(hdc2, 90, 10, NULL);
			LineTo(hdc2, 10, 90);
		}

		EndPaint(hWnd, &ps);
		break;
	}
	case WM_LBUTTONDOWN:
	{
		//bEllipse = !bEllipse;
		bProp = (BOOL)GetProp(hWnd, _T("bEllipse"));
		SetProp(hWnd, _T("bEllipse"),	(HANDLE)!bProp);
		InvalidateRect(hWnd, NULL, TRUE);
		break;
	}
	case WM_DESTROY:
	{
		RemoveProp(hWnd, _T("bEllipse"));
		break;
	}
	default:
		return DefWindowProc(hWnd, message, wParam, lParam);
	}
	return 0;
}
// ���� ��ȭ ������ �޽��� ó�����Դϴ�.


#endif  

