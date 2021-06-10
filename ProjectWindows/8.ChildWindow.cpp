// ProjectWindows.cpp : 애플리케이션에 대한 진입점을 정의합니다.
//
#define ON_MAIN
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

//윈도우 프로시저
LRESULT CALLBACK    ChildLeftProc(HWND, UINT, WPARAM, LPARAM);
LRESULT CALLBACK    ChildTopProc(HWND, UINT, WPARAM, LPARAM);
LRESULT CALLBACK    ChildBottomProc(HWND, UINT, WPARAM, LPARAM);
//윈도우 핸들러
HWND hC1, hC2, hC3;

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
ATOM MyRegisterClass(HINSTANCE hInstance)
{
	WNDCLASSEXW wcex;

	wcex.cbSize = sizeof(WNDCLASSEX); // 콜백이 있는 함수는 콜백을 먼저 실행해줘야함

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
	//////////////////////////////////차일드 윈도우 등록
	//1.왼쪽 차일드 클래스
	static HBRUSH hRed = CreateSolidBrush(RGB(255, 0, 0));
	wcex.hbrBackground = hRed;
	wcex.lpfnWndProc = ChildLeftProc;
	wcex.lpszClassName = _T("ChildLeft");
	RegisterClassExW(&wcex);
	//2.위쪽 차일드 클래스
	static HBRUSH hGreen = CreateSolidBrush(RGB(0, 255, 0));
	wcex.hbrBackground = hGreen;
	wcex.lpfnWndProc = ChildTopProc;
	wcex.lpszClassName = _T("ChildTop");
	RegisterClassExW(&wcex);
	//아래쪽 차일드 클래스
	static HBRUSH hBlue = CreateSolidBrush(RGB(0, 0, 255));
	wcex.hbrBackground = hBlue;
	wcex.lpfnWndProc = ChildBottomProc;
	wcex.lpszClassName = _T("ChildBottom");
	RegisterClassExW(&wcex);


	return  0;
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
HWND mhWnd;
BOOL InitInstance(HINSTANCE hInstance, int nCmdShow)
{
	hInst = hInstance; // 인스턴스 핸들을 전역 변수에 저장합니다.

	mhWnd = CreateWindowW(szWindowClass, szTitle, WS_OVERLAPPEDWINDOW,
		CW_USEDEFAULT, 0, CW_USEDEFAULT, 0, nullptr, nullptr, hInstance, nullptr); // 윈도우를 생성

	if (!mhWnd)
	{
		return FALSE;
	}

	ShowWindow(mhWnd, nCmdShow);
	UpdateWindow(mhWnd);

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
//
LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	switch (message)
	{
	case WM_CREATE:
	{
		hC1 = CreateWindow(
			_T("ChildLeft"), //classname
			NULL, //windowname // 보통 클래스네임, 윈도우네임 둘중 한개만 부여함
			WS_CHILD | WS_VISIBLE | WS_CLIPCHILDREN, //window style
			0, //x
			0, //y
			0, //width
			0, //height
			hWnd, //부모핸들
			(HMENU)0, //메뉴
			hInst, //
			NULL
		);
		hC2 = CreateWindow(
			_T("ChildTop"), //classname
			NULL, //windowname // 보통 클래스네임, 윈도우네임 둘중 한개만 부여함
			WS_CHILD | WS_VISIBLE | WS_CLIPCHILDREN, //window style
			0, //x
			0, //y
			0, //width
			0, //height
			hWnd, //부모핸들
			(HMENU)0, //메뉴
			hInst, //
			NULL
		);
		hC3 = CreateWindow(
			_T("ChildBottom"), //classname
			NULL, //windowname // 보통 클래스네임, 윈도우네임 둘중 한개만 부여함
			WS_CHILD | WS_VISIBLE | WS_CLIPCHILDREN, //window style
			0, //x
			0, //y
			0, //width
			0, //height
			hWnd, //부모핸들
			(HMENU)0, //메뉴
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
		// 메뉴 선택을 구문 분석합니다:
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

//child
LRESULT CALLBACK ChildLeftProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	static HWND hEdit, hBtn;
	switch (message)
	{
	case WM_CREATE:
	{
		hEdit = CreateWindowW( // 윈도우를 생성
			_T("edit"), //클래스네임
			NULL, // 윈도우네임
			WS_CHILD | WS_VISIBLE | WS_BORDER | ES_AUTOHSCROLL, // 윈도우 스타일
			210, 10, 80, 25, // 사이즈
			hWnd, // 부모 
			(HMENU)1, // ID부여
			hInst,
			NULL);
		hBtn = CreateWindowW( // 윈도우를 생성
			_T("button"), //클래스네임
			_T("Add"), // 윈도우네임
			WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON, // 윈도우 스타일
			210, 50, 80, 25, // 사이즈
			hWnd, // 부모 
			(HMENU)2, // ID부여
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

			//1.edit 창의 글자를 읽는다
			GetWindowText(hEdit, str, 256);
			//2. 그 글자를 메인창에쓴다
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
		// TODO: 여기에 hdc를 사용하는 그리기 코드를 추가합니다...
		SetBkMode(hdc, TRANSPARENT);
		TextOut(hdc, 10, 10, _T("집에보내주세요"), 7);
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
		hEdit = CreateWindowW( // 윈도우를 생성
			_T("edit"), //클래스네임
			NULL, // 윈도우네임
			WS_CHILD | WS_VISIBLE | WS_BORDER | ES_AUTOHSCROLL | WS_VSCROLL | ES_MULTILINE, // 윈도우 스타일
			10, 10, 500, 500, // 사이즈
			hWnd, // 부모 
			(HMENU)1, // ID부여
			hInst,
			NULL);
		SetWindowText(hEdit, _T("하고싶은말을 해보십쇼"));
		break;
	}
	default:
		return DefWindowProc(hWnd, message, wParam, lParam);
	}
	return 0;
}

// 정보 대화 상자의 메시지 처리기입니다.


#endif  

