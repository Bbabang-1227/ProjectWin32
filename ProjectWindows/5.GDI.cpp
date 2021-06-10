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
//   함수: InitInstance(HINSTANCE, int)
//
//   용도: 인스턴스 핸들을 저장하고 주 창을 만듭니다.
//
//   주석:
//
//        이 함수를 통해 인스턴스 핸들을 전역 변수에 저장하고
//        주 프로그램 창을 만든 다음 표시합니다.
//
BOOL InitInstance(HINSTANCE hInstance, int nCmdShow)
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
//
LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	switch (message)
	{
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
	case WM_PAINT:
	if(0) // stack object 
	{
		PAINTSTRUCT ps;
		HDC hdc = BeginPaint(hWnd, &ps);
		HBRUSH MyBr = (HBRUSH)GetStockObject(GRAY_BRUSH); //HGDIOBJ GetStockObject(int i); 강제 형변환 필요
		HBRUSH OldBr = (HBRUSH)SelectObject(hdc, MyBr);
		Rectangle(hdc, 0, 0, 300, 300);
		SelectObject(hdc, MyBr);
		// TODO: 여기에 hdc를 사용하는 그리기 코드를 추가합니다...

		HBRUSH MyBr2 = (HBRUSH)GetStockObject(BLACK_BRUSH);
		SelectObject(hdc, MyBr2);
		Rectangle(hdc, 60, 60, 360, 360);
		SelectObject(hdc, OldBr);
		Rectangle(hdc, 120, 120, 420, 420);
		EndPaint(hWnd, &ps);
	}
	if (1) // 나만의 브러쉬 생성
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
	if (0) // 나만의 펜 생성
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

// 정보 대화 상자의 메시지 처리기입니다.


#endif  

