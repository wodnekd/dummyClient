#include "stdafx.h"
#include "dummyClientWindow.h"
//#include <windows.h>

dummyClientWindow::dummyClientWindow()
{
}


dummyClientWindow::~dummyClientWindow()
{
}

void dummyClientWindow::CreateDummyClientWindow(HWND hWnd, HINSTANCE hInst)
{
	hServerIpStatic = CreateWindowW(L"static", L"       I P       : ",
		WS_CHILD | WS_VISIBLE | WS_BORDER,
		20, 50, 80, 22, hWnd, (HMENU)ServerIpStatic, hInst, NULL);
	SendMessage(hServerIpStatic, EM_LIMITTEXT, (WPARAM)4, 0);
	hServerPortStatic = CreateWindowW(L"static", L"    PORT     : ",
		WS_CHILD | WS_VISIBLE | WS_BORDER,
		20, 80, 80, 22, hWnd, (HMENU)ServerPortStatic, hInst, NULL);

	hDummyClientNum = CreateWindowW(L"static", L"client Num : ",
		WS_CHILD | WS_VISIBLE | WS_BORDER,
		20, 110, 80, 22, hWnd, (HMENU)DummyClientNum, hInst, NULL);

	hServerIpEdit = CreateWindowW(L"edit", NULL,
		WS_CHILD | WS_VISIBLE | WS_BORDER,
		120, 50, 100, 22, hWnd, (HMENU)ServerIpEdit, hInst, NULL);

	hServerPortEdit = CreateWindowW(L"edit", NULL,
		WS_CHILD | WS_VISIBLE | WS_BORDER,
		120, 80, 100, 22, hWnd, (HMENU)ServerPortEdit, hInst, NULL);

	hDummyClientNumEdit = CreateWindowW(L"edit", NULL,
		WS_CHILD | WS_VISIBLE | WS_BORDER,
		120, 110, 100, 22, hWnd, (HMENU)DummyClientNumEdit, hInst, NULL);
	
	//CreateClientButton
	hCreateClientButton = CreateWindowW(L"button", L"create",
		WS_CHILD | WS_VISIBLE | WS_BORDER,
		230, 50, 150, 85, hWnd, (HMENU)CreateClientButton, hInst, NULL);

	//clientNumSend
	hDummyClientNum50Button = CreateWindowW(L"button", L"50",
		WS_CHILD | WS_VISIBLE | WS_BORDER,
		20, 150, 100, 100, hWnd, (HMENU)DummyClientNum50Button, hInst, NULL);

	hDummyClientNum100Button = CreateWindowW(L"button", L"100",
		WS_CHILD | WS_VISIBLE | WS_BORDER,
		120, 150, 100, 100, hWnd, (HMENU)DummyClientNum100Button, hInst, NULL);

	hDummyClientNum500Button = CreateWindowW(L"button", L"500",
		WS_CHILD | WS_VISIBLE | WS_BORDER,
		20, 250, 100, 100, hWnd, (HMENU)DummyClientNum500Button, hInst, NULL);
	
	hDummyClientNum1000Button = CreateWindowW(L"button", L"1000",
		WS_CHILD | WS_VISIBLE | WS_BORDER,
		120, 250, 100, 100, hWnd, (HMENU)DummyClientNum1000Button, hInst, NULL);

	//writeEdit
	hDummyWriteEdit = CreateWindowW(L"edit", NULL,
		WS_CHILD | WS_VISIBLE | WS_BORDER | ES_READONLY | ES_AUTOHSCROLL | ES_AUTOVSCROLL ,
		230, 150, 150, 200, hWnd, (HMENU)DummyWriteEdit, hInst, NULL);
}
