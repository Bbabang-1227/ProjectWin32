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
ATOM MyRegisterClass(HINSTANCE hInstance) // ����� ���� �Լ�
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
BOOL InitInstance(HINSTANCE hInstance, int nCmdShow) // ���� �Լ�
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
HWND hStatic;
HWND hEdi;
HWND hBtn1;
HWND hBtn2;
int nTop = 100;
//
#define ID_EDIT_NAME 100
#define ID_BTN_SAVE 101
#define ID_BTN_PRINT 102

LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	switch (message)
	{
	case WM_CREATE:
	{
		hStatic = CreateWindowW( // �����츦 ����
			_T("STATIC"),
			_T("�̸� : "), // ����
			WS_CHILD | WS_VISIBLE, // ������ ��Ÿ��
			20, 20, 100, 25, // ������
			hWnd, // �θ� 
			(HMENU)-1, // ID�ο�
			hInst,
			NULL);
		hEdi = CreateWindowW( // �����츦 ����
			_T("EDIT"),
			_T("edit"), // ����
			WS_CHILD | WS_VISIBLE | WS_BORDER | WS_VSCROLL | WS_HSCROLL | ES_AUTOHSCROLL, // ������ ��Ÿ��
			10, 25, 200, 25, // ������
			hWnd, // �θ� 
			(HMENU)ID_EDIT_NAME, // ID�ο�
			hInst,
			NULL);
		hBtn1 = CreateWindowW( // �����츦 ����
			_T("BUTTON"),
			_T("save"), // ����
			WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON, // ������ ��Ÿ��
			300, 20, 100, 25, // ������
			hWnd, // �θ� 
			(HMENU)ID_BTN_SAVE, // ID�ο�
			hInst,
			NULL);
		hBtn2 = CreateWindowW( // �����츦 ����
			_T("BUTTON"),
			_T("print"), // ����
			WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON, // ������ ��Ÿ��
			300, 50, 100, 25, // ������
			hWnd, // �θ� 
			(HMENU)ID_BTN_PRINT, // ID�ο�
			hInst,
			NULL);
		break;
	}
	case WM_LBUTTONDOWN:
	{
		SetParent(hBtn1, GetDesktopWindow());
		SetWindowText(hBtn1, _T("��������!"));
		break;
	}
	case WM_RBUTTONDOWN:
	{
		SetParent(hBtn1, hWnd);
		SetWindowText(hBtn1, _T("�׷�����!"));
		break;
	}
	case WM_COMMAND:
	{
		HDC hdc = GetDC(hWnd);
		switch (LOWORD(wParam))
		{
		case ID_BTN_SAVE:
		{
			Rectangle(hdc, 10, 20, 30, 40);
			MessageBox(hWnd, TEXT("������ �����մϴ�"), TEXT("Button"), MB_OK);
			break;
		}
		case ID_BTN_PRINT:
		{
			MessageBox(hWnd, TEXT("�μ� �����մϴ�"), TEXT("Button"), MB_OK);
			break;
		}
		case ID_EDIT_NAME:
		{
			if (HIWORD(wParam) == EN_CHANGE)
			{
				TCHAR str[128];
				GetWindowText(hEdi, str, 128);
				SetWindowText(hWnd, str);
				SetWindowText(hStatic, str);
				SetWindowText(hBtn1, str);

			}
			break;
		}
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
		static BOOL bShow = TRUE;
		switch (wParam)
		{
		case VK_LEFT:
		case VK_RIGHT:
		{
			if (bShow)
			{
				bShow = FALSE;
				ShowWindow(hEdi, SW_HIDE);
				SetWindowText(hWnd, _T("��󠺴�"));
			}
			else
			{
				bShow = TRUE;
				ShowWindow(hEdi, SW_SHOW);
				SetWindowText(hWnd, _T("��Ÿ����"));
			}
			break;
		}
		case VK_UP:
		{
			nTop -= 10;
			break;
		}
		case VK_DOWN:
		{
			nTop += 10;
			break;
		}
		default:
			break;
		}
		MoveWindow(hEdi, 10, nTop, 1000, 250, TRUE);
	}
	break;
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
// ���� ��ȭ ������ �޽��� ó�����Դϴ�.
#endif  