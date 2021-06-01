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
#define MAX 5

#define WM_CHECKBINGO WM_USER + 1

// ���� ����:
HINSTANCE hInst;                                // ���� �ν��Ͻ��Դϴ�.
WCHAR szTitle[MAX_LOADSTRING];                  // ���� ǥ���� �ؽ�Ʈ�Դϴ�.
WCHAR szWindowClass[MAX_LOADSTRING];            // �⺻ â Ŭ���� �̸��Դϴ�.

// �� �ڵ� ��⿡ ���Ե� �Լ��� ������ �����մϴ�:
ATOM                MyRegisterClass(HINSTANCE hInstance);
BOOL                InitInstance(HINSTANCE, int);
LRESULT CALLBACK    WndProc(HWND, UINT, WPARAM, LPARAM);
LRESULT CALLBACK    ChildProc(HWND, UINT, WPARAM, LPARAM); //child

INT_PTR CALLBACK    About(HWND, UINT, WPARAM, LPARAM);

HWND hC1;
HWND g_mainhWnd;
HWND g_childhWnd[MAX][MAX];
BOOL g_bMyTurn = TRUE;

int fnCheckandSetBingo(HWND, WPARAM, LPARAM, int);

enum modeBINGO {
	bingoNONE = 0,
	bingoMINE,
	bingoMyBINGO,
	bingoYOURS,
	bingoYourBingo
};

enum userInput {
	Horizen = 0,
	Vertical,
	Diagonal,
	DiagonalE
};

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

BOOL InitInstance(HINSTANCE hInstance, int nCmdShow)
{
	hInst = hInstance; // �ν��Ͻ� �ڵ��� ���� ������ �����մϴ�.

	g_mainhWnd = CreateWindowW(szWindowClass, szTitle, WS_OVERLAPPEDWINDOW,
		CW_USEDEFAULT, 0, CW_USEDEFAULT, 0, nullptr, nullptr, hInstance, nullptr); // �����츦 ����

	if (!g_mainhWnd)
	{
		return FALSE;
	}

	ShowWindow(g_mainhWnd, nCmdShow);
	UpdateWindow(g_mainhWnd);

	return TRUE;
}


LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{

	switch (message)
	{
	case WM_CREATE:
	{
		for (int i = 0; i < MAX; i++)
		{
			for (int j = 0; j < MAX; j++)
			{
				g_childhWnd[i][j] = CreateWindow(
					_T("lpszClass"), //classname
					NULL, //windowname // ���� Ŭ��������, ��������� ���� �Ѱ��� �ο���
					WS_CHILD | WS_VISIBLE, //window style
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
	case WM_COMMAND: {
		int wmId = LOWORD(wParam);
		// �޴� ������ ���� �м��մϴ�:
		switch (wmId)
		{
		case IDM_ABOUT:
			//DialogBox(hInst, MAKEINTRESOURCE(IDD_ABOUTBOX), hWnd, About);
			SetProp(hWnd, _T("modeBINGO"), (HANDLE)bingoNONE);
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
	{
		PAINTSTRUCT ps;
		HDC hdc = BeginPaint(hWnd, &ps);

		// TODO: ���⿡ hdc�� ����ϴ� �׸��� �ڵ带 �߰��մϴ�...
		EndPaint(hWnd, &ps);
	}
	break;

	case WM_CHECKBINGO:
	{
		g_bMyTurn = !g_bMyTurn;
		if (g_bMyTurn)
			SetWindowText(hWnd, _T("My Turn"));
		else
			SetWindowText(hWnd, _T("Your Turn"));

		fnCheckandSetBingo(hWnd, wParam, lParam, Vertical);
		fnCheckandSetBingo(hWnd, wParam, lParam, Horizen);
		fnCheckandSetBingo(hWnd, wParam, lParam, Diagonal);
		fnCheckandSetBingo(hWnd, wParam, lParam, DiagonalE);

		break;
	}

	case WM_DESTROY: {
		PostQuitMessage(0);
		break;
	}
	default:
		return DefWindowProc(hWnd, message, wParam, lParam);
	}
	return 0;
}

LRESULT CALLBACK ChildProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	int mState;

	switch (message)
	{
	case WM_CREATE:
	{
		SetProp(hWnd, _T("modeBINGO"), (HANDLE)bingoNONE); //1. �Ӽ� ����
		break;
	}
	case WM_PAINT:
	{
		PAINTSTRUCT ps;
		HDC hdc = BeginPaint(hWnd, &ps);
		// TODO: ���⿡ hdc�� ����ϴ� �׸��� �ڵ带 �߰��մϴ�...	


		mState = (int)GetProp(hWnd, _T("modeBINGO"));
		if (mState == bingoNONE)
		{
			Rectangle(hdc, 10, 10, 80, 80);
		}
		else if (mState == bingoMINE)
		{
			Ellipse(hdc, 10, 10, 80, 80);

		}
		else if (mState == bingoYOURS)
		{
			MoveToEx(hdc, 10, 10, NULL);
			LineTo(hdc, 90, 90);
			MoveToEx(hdc, 90, 10, NULL);
			LineTo(hdc, 10, 90);

		}
		else if (mState == bingoMyBINGO)
		{
			HBRUSH MyBr2 = (HBRUSH)GetStockObject(DKGRAY_BRUSH);
			SelectObject(hdc, MyBr2);
			Ellipse(hdc, 10, 10, 80, 80);

		}
		else
		{
			HBRUSH MyBr2 = CreateSolidBrush(RGB(255, 0, 0));
			SelectObject(hdc, MyBr2);
			Rectangle(hdc, 10, 10, 80, 80);
		}
		EndPaint(hWnd, &ps);
		break;
	}
	case WM_LBUTTONDOWN:
	{

		mState = (int)GetProp(hWnd, _T("modeBINGO"));
		if (mState == bingoNONE)
		{
			int nMode;
			if (g_bMyTurn)
			{
				nMode = bingoMINE;
			}
			else
			{
				nMode = bingoYOURS;
			}
			SetProp(hWnd, _T("modeBINGO"), (HANDLE)nMode);
			SendMessage(g_mainhWnd, WM_CHECKBINGO, (WPARAM)hWnd, nMode);

		}
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

int fnCheckandSetBingo(HWND hWnd, WPARAM wParam, LPARAM lParam, int nUserinput)
{
	HWND hChild = (HWND)wParam;
	int nCurMode = (int)lParam;

	int nx = -1;
	int ny = -1;
	int nTrig = 0;

	//��ġüũ
	for (int i = 0; i < MAX; i++) {
		for (int j = 0; j < MAX; j++) {
			if (g_childhWnd[i][j] == hChild)
			{
				nx = i;
				ny = j;
				break;
			}
		}
	}
	if (nx < 0 || ny < 0) return 0;
	int nTemp;
	int nXParam, nYParam;
	//���� ���� üũ
	for (int i = 0; i < MAX; i++)
	{
		switch (nUserinput)
		{
		case Horizen:
		{
			nXParam = i;
			nYParam = ny;
			break;
		}
		case Vertical:
		{
			nXParam = nx;
			nYParam = i;
			break;
		}
		case Diagonal:
		{
			nXParam = i;
			nYParam = i;
			break;
		}
		case DiagonalE:
		{
			nXParam = i;
			nYParam = MAX - i - 1;
			break;
		}
		default:
			break;
		}

		nTemp = (int)GetProp(g_childhWnd[nXParam][nYParam], _T("modeBINGO"));
		if (nTemp == nCurMode || nTemp == nCurMode + 1)
		{
			nTrig++;
		}
	}

	if (nTrig == MAX)
	{
		for (int i = 0; i < MAX; i++)
		{
			switch (nUserinput)
			{
			case Horizen:
			{
				nXParam = i;
				nYParam = ny;
				break;
			}
			case Vertical:
			{
				nXParam = nx;
				nYParam = i;
				break;
			}
			case Diagonal:
			{
				nXParam = i;
				nYParam = i;
				break;
			}
			case DiagonalE:
			{
				nXParam = i;
				nYParam = MAX - i - 1;
				break;
			}
			default:
				break;
			}
			SetProp(g_childhWnd[nXParam][nYParam], _T("modeBINGO"), (HANDLE)(nCurMode + 1));//����
			InvalidateRect(hWnd, NULL, TRUE);
		}
	}
	nTrig = 0;
	return 0;
}

#endif  


