// ProjectWindows.cpp : 애플리케이션에 대한 진입점을 정의합니다.
//
//#define ON_MAIN
#ifdef ON_MAIN
// ProjectWindows.cpp : 애플리케이션에 대한 진입점을 정의합니다.
//

#include "framework.h"
#include "ProjectWindows.h"

#define MAX_LOADSTRING 100
#define MAX_LOADSTRING2 'windowkiki'

// 전역 변수:
HINSTANCE hInst;                                // 현재 인스턴스입니다.
WCHAR szTitle[MAX_LOADSTRING];                  // 제목 표시줄 텍스트입니다.
WCHAR szWindowClass[MAX_LOADSTRING];            // 기본 창 클래스 이름입니다.

// 이 코드 모듈에 포함된 함수의 선언을 전달합니다:
ATOM                MyRegisterClass(HINSTANCE hInstance);
BOOL                InitInstance(HINSTANCE, int);
LRESULT CALLBACK    WndProc(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK    About(HWND, UINT, WPARAM, LPARAM);

int APIENTRY wWinMain(// main
	_In_ HINSTANCE hInstance, //응용프로그램을 식별하는 값 
	_In_opt_ HINSTANCE hPrevInstance, // 먼저 실행된 인스턴스의 핸들
	_In_ LPWSTR    lpCmdLine, //실행파일의 경로와 명령줄의 내용을 담은 문자열 포인터
	_In_ int       nCmdShow) // 윈도우를 화면에 보여주는 방법을 명시
{
	UNREFERENCED_PARAMETER(hPrevInstance);
	UNREFERENCED_PARAMETER(lpCmdLine);

	// TODO: 여기에 코드를 입력합니다.

	// 전역 문자열을 초기화합니다.
	LoadStringW(hInstance, IDS_APP_TITLE, szTitle, MAX_LOADSTRING);
	LoadStringW(hInstance, IDC_PROJECTWINDOWS, szWindowClass, MAX_LOADSTRING);
	MyRegisterClass(hInstance);

	// 애플리케이션 초기화를 수행합니다:
	if (!InitInstance(hInstance, nCmdShow))
	{

		return FALSE;
	}

	HACCEL hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_PROJECTWINDOWS));

	/*
	C/C++ 는 함수를 직접 호출하였으며 전체 실행 흐름을 코드에 명시할수있었음
	그러나 윈도우 프로그래밍은 입력을 예측할수없음(비동기)
	언제 발생할지 모르는 비동기 입력에 대해 처리가 가능하면서도 화면이 멈추지말아야한다
	따라서 윈도우 프로그래밍 모델은 Message Driven 방식을 채택
	*/
	MSG msg;

	// 기본 메시지 루프입니다:
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
//  함수: MyRegisterClass()
//
//  용도: 창 클래스를 등록합니다.
//
ATOM MyRegisterClass(HINSTANCE hInstance) // 등록을 위한 함수
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
//   함수: InitInstance(HINSTANCE, int)
//
//   용도: 인스턴스 핸들을 저장하고 주 창을 만듭니다.
//
//   주석:
//
//        이 함수를 통해 인스턴스 핸들을 전역 변수에 저장하고
//        주 프로그램 창을 만든 다음 표시합니다.
//
BOOL InitInstance(HINSTANCE hInstance, int nCmdShow) // 생성 함수
{
	hInst = hInstance; // 인스턴스 핸들을 전역 변수에 저장합니다.

	HWND hWnd = CreateWindowW(szWindowClass, szTitle, WS_OVERLAPPEDWINDOW,
		CW_USEDEFAULT, 0, CW_USEDEFAULT, 0, nullptr, nullptr, hInstance, nullptr); // 윈도우를 생성

	if (!hWnd)
	{
		return FALSE;
	}

	ShowWindow(hWnd, nCmdShow);
	UpdateWindow(hWnd);

	return TRUE;
}

//
//  함수: WndProc(HWND, UINT, WPARAM, LPARAM)
//
//  용도: 주 창의 메시지를 처리합니다.
//
//  WM_COMMAND  - 애플리케이션 메뉴를 처리합니다.
//  WM_PAINT    - 주 창을 그립니다.
//  WM_DESTROY  - 종료 메시지를 게시하고 반환합니다.
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
		hStatic = CreateWindowW( // 윈도우를 생성
			_T("STATIC"),
			_T("이름 : "), // 제목
			WS_CHILD | WS_VISIBLE, // 윈도우 스타일
			20, 20, 100, 25, // 사이즈
			hWnd, // 부모 
			(HMENU)-1, // ID부여
			hInst,
			NULL);
		hEdi = CreateWindowW( // 윈도우를 생성
			_T("EDIT"),
			_T("edit"), // 제목
			WS_CHILD | WS_VISIBLE | WS_BORDER | WS_VSCROLL | WS_HSCROLL | ES_AUTOHSCROLL, // 윈도우 스타일
			10, 25, 200, 25, // 사이즈
			hWnd, // 부모 
			(HMENU)ID_EDIT_NAME, // ID부여
			hInst,
			NULL);
		hBtn1 = CreateWindowW( // 윈도우를 생성
			_T("BUTTON"),
			_T("save"), // 제목
			WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON, // 윈도우 스타일
			300, 20, 100, 25, // 사이즈
			hWnd, // 부모 
			(HMENU)ID_BTN_SAVE, // ID부여
			hInst,
			NULL);
		hBtn2 = CreateWindowW( // 윈도우를 생성
			_T("BUTTON"),
			_T("print"), // 제목
			WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON, // 윈도우 스타일
			300, 50, 100, 25, // 사이즈
			hWnd, // 부모 
			(HMENU)ID_BTN_PRINT, // ID부여
			hInst,
			NULL);
		break;
	}
	case WM_LBUTTONDOWN:
	{
		SetParent(hBtn1, GetDesktopWindow());
		SetWindowText(hBtn1, _T("집에가자!"));
		break;
	}
	case WM_RBUTTONDOWN:
	{
		SetParent(hBtn1, hWnd);
		SetWindowText(hBtn1, _T("그래가자!"));
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
			MessageBox(hWnd, TEXT("저장을 시작합니다"), TEXT("Button"), MB_OK);
			break;
		}
		case ID_BTN_PRINT:
		{
			MessageBox(hWnd, TEXT("인쇄 시작합니다"), TEXT("Button"), MB_OK);
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
				SetWindowText(hWnd, _T("사라졋다"));
			}
			else
			{
				bShow = TRUE;
				ShowWindow(hEdi, SW_SHOW);
				SetWindowText(hWnd, _T("나타났다"));
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
		// TODO: 여기에 hdc를 사용하는 그리기 코드를 추가합니다...
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
// 정보 대화 상자의 메시지 처리기입니다.
#endif  