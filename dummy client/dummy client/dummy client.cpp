// dummy client.cpp : 응용 프로그램에 대한 진입점을 정의합니다.
//

#include "stdafx.h"
#include "dummy client.h"

#define MAX_LOADSTRING 100
#define BUFSIZE	   512

// 전역 변수:
HINSTANCE hInst;                                // 현재 인스턴스입니다.
WCHAR szTitle[MAX_LOADSTRING];                  // 제목 표시줄 텍스트입니다.
WCHAR szWindowClass[MAX_LOADSTRING];            // 기본 창 클래스 이름입니다.

void DisplayText(LPWSTR fmt, ...);
// 이 코드 모듈에 들어 있는 함수의 정방향 선언입니다.
ATOM                MyRegisterClass(HINSTANCE hInstance);
BOOL                InitInstance(HINSTANCE, int);
LRESULT CALLBACK    WndProc(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK    About(HWND, UINT, WPARAM, LPARAM);

int APIENTRY wWinMain(_In_ HINSTANCE hInstance,
                     _In_opt_ HINSTANCE hPrevInstance,
                     _In_ LPWSTR    lpCmdLine,
                     _In_ int       nCmdShow)
{
    UNREFERENCED_PARAMETER(hPrevInstance);
    UNREFERENCED_PARAMETER(lpCmdLine);

    // TODO: 여기에 코드를 입력합니다.

    // 전역 문자열을 초기화합니다.
    LoadStringW(hInstance, IDS_APP_TITLE, szTitle, MAX_LOADSTRING);
    LoadStringW(hInstance, IDC_DUMMYCLIENT, szWindowClass, MAX_LOADSTRING);
    MyRegisterClass(hInstance);

    // 응용 프로그램 초기화를 수행합니다.
    if (!InitInstance (hInstance, nCmdShow))
    {
        return FALSE;
    }

    HACCEL hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_DUMMYCLIENT));

    MSG msg;

    // 기본 메시지 루프입니다.
    while (GetMessage(&msg, nullptr, 0, 0))
    {
        if (!TranslateAccelerator(msg.hwnd, hAccelTable, &msg))
        {
            TranslateMessage(&msg);
            DispatchMessage(&msg);
        }
    }

    return (int) msg.wParam;
}



//
//  함수: MyRegisterClass()
//
//  목적: 창 클래스를 등록합니다.
//
ATOM MyRegisterClass(HINSTANCE hInstance)
{
    WNDCLASSEXW wcex;

    wcex.cbSize = sizeof(WNDCLASSEX);

    wcex.style          = CS_HREDRAW | CS_VREDRAW;
    wcex.lpfnWndProc    = WndProc;
    wcex.cbClsExtra     = 0;
    wcex.cbWndExtra     = 0;
    wcex.hInstance      = hInstance;
    wcex.hIcon          = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_DUMMYCLIENT));
    wcex.hCursor        = LoadCursor(nullptr, IDC_ARROW);
    wcex.hbrBackground  = (HBRUSH)(COLOR_WINDOW+2);
	wcex.lpszMenuName   = NULL;//MAKEINTRESOURCEW(IDC_DUMMYCLIENT);
    wcex.lpszClassName  = szWindowClass;
    wcex.hIconSm        = LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_SMALL));

    return RegisterClassExW(&wcex);
}

//
//   함수: InitInstance(HINSTANCE, int)
//
//   목적: 인스턴스 핸들을 저장하고 주 창을 만듭니다.
//
//   설명:
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

   ShowWindow(hWnd, nCmdShow);
   UpdateWindow(hWnd);

   return TRUE;
}

//
//  함수: WndProc(HWND, UINT, WPARAM, LPARAM)
//
//  목적:  주 창의 메시지를 처리합니다.
//
//  WM_COMMAND  - 응용 프로그램 메뉴를 처리합니다.
//  WM_PAINT    - 주 창을 그립니다.
//  WM_DESTROY  - 종료 메시지를 게시하고 반환합니다.
//
//
#pragma warning(disable: 4996)
dummyClientWindow dm;
LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    switch (message)
    {
	case WM_CREATE:
	{
		SetWindowPos(hWnd, NULL, 100, 100, 420, 400, 0);
		dm.CreateDummyClientWindow(hWnd, hInst);
	}
	break;
    case WM_COMMAND:
        {
            int wmId = LOWORD(wParam);
            // 메뉴 선택을 구문 분석합니다.
            switch (wmId)
            {
			case CreateClientButton:
			{
				WCHAR wcharIP[20] = L"";
				char charIP[20] = "";
				WCHAR wcharPORT[20] = L"";
				int intPORT = 0;
				GetWindowText(dm.GethServerIpEdit(), wcharIP, 20);
				wcstombs(charIP, wcharIP, 20);
				GetWindowText(dm.GethServerPortEdit(), wcharPORT, 20);
				intPORT = _wtoi(wcharPORT);

				WCHAR clientNum[100] = L"";
				int createClientNum;
				GetWindowText(dm.GethDummyClientNumEdit(), clientNum, 100);
				createClientNum = _wtoi(clientNum);

				for (int i = 0; i < createClientNum; i++)
				{
					//윈속 초기화
					WSADATA wsa;
					if (WSAStartup(MAKEWORD(2, 2), &wsa) != 0) break;
					//socket 생성
					SOCKET clientSock = socket(AF_INET, SOCK_STREAM, 0);
					if (clientSock == INVALID_SOCKET)
						MessageBox(hWnd, L"CreateSock, socket error", L"clientSock == INVALID_SOCKET", MB_OK);
					int retval;
					SOCKADDR_IN serveraddr;
					ZeroMemory(&serveraddr, sizeof(serveraddr));
					serveraddr.sin_family = AF_INET;
					serveraddr.sin_addr.s_addr = inet_addr(charIP);
					serveraddr.sin_port = htons(intPORT);
					retval = connect(clientSock, (SOCKADDR *)&serveraddr, sizeof(serveraddr));
					DisplayText(L"create %d dummy client \r\n ", i+1);
				}

			}
			break;
			case DummyClientNum50Button:
			{
				WCHAR clientNum[100]=L"";
				int i;
				GetWindowText(dm.GethDummyClientNumEdit(), clientNum, 100);
				i = _wtoi(clientNum) + 50;
				_itow(i, clientNum, 10);
				SetWindowText(dm.GethDummyClientNumEdit(), clientNum);
			}
			break;
			case DummyClientNum100Button:
			{
				WCHAR clientNum[100] = L"";
				int i;
				GetWindowText(dm.GethDummyClientNumEdit(), clientNum, 100);
				i = _wtoi(clientNum) + 100;
				_itow(i, clientNum, 10);
				SetWindowText(dm.GethDummyClientNumEdit(), clientNum);
			}
			break;
			case DummyClientNum500Button:
			{
				WCHAR clientNum[100] = L"";
				int i;
				GetWindowText(dm.GethDummyClientNumEdit(), clientNum, 100);
				i = _wtoi(clientNum) + 500;
				_itow(i, clientNum, 10);
				SetWindowText(dm.GethDummyClientNumEdit(), clientNum);
			}
			break;
			case DummyClientNum1000Button:
			{
				WCHAR clientNum[100] = L"";
				int i;
				GetWindowText(dm.GethDummyClientNumEdit(), clientNum, 100);
				i = _wtoi(clientNum) + 1000;
				_itow(i, clientNum, 10);
				SetWindowText(dm.GethDummyClientNumEdit(), clientNum);
			}
			break;
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
            HDC hdc = BeginPaint(hWnd, &ps);
            // TODO: 여기에 hdc를 사용하는 그리기 코드를 추가합니다.
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


void DisplayText(LPWSTR fmt, ...)
{
	va_list arg;
	va_start(arg, fmt);

	WCHAR cbuf[BUFSIZE + 256];
	vswprintf(cbuf, BUFSIZE + 256, fmt, arg);

	int nLength = GetWindowTextLength(dm.GethDummyWriteEdit());
	SendMessage(dm.GethDummyWriteEdit(), EM_SETSEL, nLength, nLength);
	SendMessage(dm.GethDummyWriteEdit(), EM_REPLACESEL, FALSE, (LPARAM)cbuf);

	va_end(arg);
}