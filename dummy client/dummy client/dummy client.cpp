// dummy client.cpp : ���� ���α׷��� ���� �������� �����մϴ�.
//

#include "stdafx.h"
#include "dummy client.h"

#define MAX_LOADSTRING 100
#define BUFSIZE	   512

// ���� ����:
HINSTANCE hInst;                                // ���� �ν��Ͻ��Դϴ�.
WCHAR szTitle[MAX_LOADSTRING];                  // ���� ǥ���� �ؽ�Ʈ�Դϴ�.
WCHAR szWindowClass[MAX_LOADSTRING];            // �⺻ â Ŭ���� �̸��Դϴ�.

void DisplayText(LPWSTR fmt, ...);
// �� �ڵ� ��⿡ ��� �ִ� �Լ��� ������ �����Դϴ�.
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

    // TODO: ���⿡ �ڵ带 �Է��մϴ�.

    // ���� ���ڿ��� �ʱ�ȭ�մϴ�.
    LoadStringW(hInstance, IDS_APP_TITLE, szTitle, MAX_LOADSTRING);
    LoadStringW(hInstance, IDC_DUMMYCLIENT, szWindowClass, MAX_LOADSTRING);
    MyRegisterClass(hInstance);

    // ���� ���α׷� �ʱ�ȭ�� �����մϴ�.
    if (!InitInstance (hInstance, nCmdShow))
    {
        return FALSE;
    }

    HACCEL hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_DUMMYCLIENT));

    MSG msg;

    // �⺻ �޽��� �����Դϴ�.
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
//  �Լ�: MyRegisterClass()
//
//  ����: â Ŭ������ ����մϴ�.
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
//   �Լ�: InitInstance(HINSTANCE, int)
//
//   ����: �ν��Ͻ� �ڵ��� �����ϰ� �� â�� ����ϴ�.
//
//   ����:
//
//        �� �Լ��� ���� �ν��Ͻ� �ڵ��� ���� ������ �����ϰ�
//        �� ���α׷� â�� ���� ���� ǥ���մϴ�.
//
BOOL InitInstance(HINSTANCE hInstance, int nCmdShow)
{
   hInst = hInstance; // �ν��Ͻ� �ڵ��� ���� ������ �����մϴ�.

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
//  �Լ�: WndProc(HWND, UINT, WPARAM, LPARAM)
//
//  ����:  �� â�� �޽����� ó���մϴ�.
//
//  WM_COMMAND  - ���� ���α׷� �޴��� ó���մϴ�.
//  WM_PAINT    - �� â�� �׸��ϴ�.
//  WM_DESTROY  - ���� �޽����� �Խ��ϰ� ��ȯ�մϴ�.
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
            // �޴� ������ ���� �м��մϴ�.
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
					//���� �ʱ�ȭ
					WSADATA wsa;
					if (WSAStartup(MAKEWORD(2, 2), &wsa) != 0) break;
					//socket ����
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
            // TODO: ���⿡ hdc�� ����ϴ� �׸��� �ڵ带 �߰��մϴ�.
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