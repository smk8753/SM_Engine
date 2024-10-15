// Editor_Window.cpp : 애플리케이션에 대한 진입점을 정의합니다.
//

#include "framework.h"
#include "Editor_Window.h"
#include "..\\SMEngine_SOURCE\\smeApplication.h"

//#pragma comment(lib, "..\\x64\\Debug\\SMEngine_Window.lib")

#define MAX_LOADSTRING 100

// 전역 변수:
HINSTANCE hInst;                                // 현재 인스턴스입니다.
WCHAR szTitle[MAX_LOADSTRING];                  // 제목 표시줄 텍스트입니다.
WCHAR szWindowClass[MAX_LOADSTRING];            // 기본 창 클래스 이름입니다.
smeApp::Application application;				// 응용 프로그램

// 이 코드 모듈에 포함된 함수의 선언을 전달합니다:
ATOM                MyRegisterClass(HINSTANCE hInstance);
BOOL                InitInstance(HINSTANCE, int);
LRESULT CALLBACK    WndProc(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK    About(HWND, UINT, WPARAM, LPARAM);

int APIENTRY wWinMain(
	_In_ HINSTANCE hInstance,               // 이 프로그램의 인스턴스 핸들
	_In_opt_ HINSTANCE hPrevInstance,       // 이전 프로그램의 인스턴스 핸들 (현재는 사용 X)
	_In_ LPWSTR    lpCmdLine,               //
	_In_ int       nCmdShow)               // 프로그램이 실행될 형태 (모양 정보 등)
{
	UNREFERENCED_PARAMETER(hPrevInstance);
	UNREFERENCED_PARAMETER(lpCmdLine);

	// TODO: 여기에 코드를 입력합니다.

	// 전역 문자열을 초기화합니다.
	LoadStringW(hInstance, IDS_APP_TITLE, szTitle, MAX_LOADSTRING);
	LoadStringW(hInstance, IDC_EDITORWINDOW, szWindowClass, MAX_LOADSTRING);
	MyRegisterClass(hInstance);

	// 애플리케이션 초기화를 수행합니다:
	if (!InitInstance(hInstance, nCmdShow))
	{
		return FALSE;
	}

	HACCEL hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_EDITORWINDOW));

	MSG msg;

	// 기본 메시지 루프입니다:
	//while (GetMessage(&msg, nullptr, 0, 0))
	//{
	//    if (!TranslateAccelerator(msg.hwnd, hAccelTable, &msg))
	//    {
	//        TranslateMessage(&msg);
	//        DispatchMessage(&msg);
	//    }
	//}

	//
	//  함수: GetMessage(&msg, nullptr, 0, 0)
	//
	//  용도: 프로세스에서 발생한 메세지를 메세지 큐에서 가져옴
	// 

	//
	//  함수: PeekMessage(&msg, nullptr, 0, 0, PM_REMOVE)
	//
	//  용도: 메세지 큐 내의 메세지 유무와 상관없이 함수가 리턴된다.
	//        true  - 메세지 있음 (해당 메세지를 처리하는 코드)
	//        false - 메세지 없음 (게임 로직 코드)
	// 

	while (true)
	{
		if (PeekMessage(&msg, nullptr, 0, 0, PM_REMOVE))
		{
			// 메세지가 있을 경우, 이곳에서 처리
			if (msg.message == WM_QUIT)
				break;

			if (!TranslateAccelerator(msg.hwnd, hAccelTable, &msg))
			{
				TranslateMessage(&msg);
				DispatchMessage(&msg);
			}
		}
		else
		{
			// 메세지가 없을 경우, 이곳에서 처리 (게임로직 등...)
			application.Run();
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
	wcex.hIcon = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_EDITORWINDOW));
	wcex.hCursor = LoadCursor(nullptr, IDC_ARROW);
	wcex.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
	wcex.lpszMenuName = MAKEINTRESOURCEW(IDC_EDITORWINDOW);
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
		CW_USEDEFAULT, 0, CW_USEDEFAULT, 0, nullptr, nullptr, hInstance, nullptr);

	if (!hWnd)
	{
		return FALSE;
	}

	application.Initialize(hWnd);

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
			DialogBox(hInst, MAKEINTRESOURCE(IDD_ABOUTBOX), hWnd, About);
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

		HDC hdc = BeginPaint(hWnd, &ps);        // DC 핸들러
		// DC : 화면 출력에 필요한 모든 정보를 가지는 데이터 구조체
		//      GDI 모듈에 의해서 관리된다.
		//      폰트, 선의 굵기, 색상 등...
		//      WINAPI에서는, 화면 출력에 필요한 모든 것을 DC를 통해 작업 수행

		/**************** example code *****************/

		///* 1. 배경 색 변경 예제 (BRUSH) */
		//// 배경 색 브러쉬
		//HBRUSH pinkBrush = CreateSolidBrush(RGB(255, 0, 255));
		//
		//// 만든 브러쉬 적용, 이전 브러쉬정보 백업
		//HBRUSH oldBrush = (HBRUSH)SelectObject(hdc, pinkBrush);

		//// 도형 그리기
		//Rectangle(hdc, 100, 100, 300, 300);
		//Ellipse(hdc, 1000, 300, 1200, 500);

		//// 메모리(heap)에 할당되었던 브러쉬 정보를 지우기
		//SelectObject(hdc, oldBrush);
		//DeleteObject(pinkBrush);
		///*******************************/

		///* 2. 테두리 색 변경 예제 (PEN) */
		//HPEN redPen = CreatePen(PS_SOLID, 3, RGB(255, 0, 0));
		//HPEN oldPen = (HPEN)SelectObject(hdc, redPen);
		//
		//POINT prevPoint;
		//MoveToEx(hdc, 350, 350, &prevPoint);
		//LineTo(hdc, 500, 500);
		//LineTo(hdc, 700, 100);
		//MoveToEx(hdc, prevPoint.x, prevPoint.y, NULL);

		//SelectObject(hdc, oldPen);
		//DeleteObject(redPen);
		///*******************************/

		///* 3. 스톡 오브젝트 예제 (Stock : 자주 사용하는 것들을 미리 만들어 둔 것 */
		//HBRUSH grayBrush = (HBRUSH)GetStockObject(GRAY_BRUSH);
		//oldBrush = (HBRUSH)SelectObject(hdc, grayBrush);

		//HPEN whitePen = (HPEN)GetStockObject(WHITE_PEN);
		//oldPen = (HPEN)SelectObject(hdc, whitePen);

		//POINT polygonPoints[] = { {700, 50}, {500, 200}, {600, 400}, {800, 400}, {900, 200} };
		//Polygon(hdc, polygonPoints, 5);

		//// 메모리(heap)에 할당되었던 브러쉬 정보를 지우기
		//SelectObject(hdc, oldBrush);
		//SelectObject(hdc, whitePen);
		//DeleteObject(grayBrush);
		//DeleteObject(whitePen);
		///*******************************/

		/**************************************************/

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
INT_PTR CALLBACK About(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
	UNREFERENCED_PARAMETER(lParam);
	switch (message)
	{
	case WM_INITDIALOG:
		return (INT_PTR)TRUE;

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
