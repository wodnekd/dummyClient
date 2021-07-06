#pragma once

enum hDummyHMENU
{
	ServerIpStatic = 100,
	ServerPortStatic,
	DummyClientNum,
	ServerIpEdit,
	ServerPortEdit,
	DummyClientNumEdit,
	CreateClientButton,
	DummyClientNum50Button,
	DummyClientNum100Button,
	DummyClientNum500Button,
	DummyClientNum1000Button,
	DummyWriteEdit
};

class dummyClientWindow
{
	HWND hServerIpStatic;
	HWND hServerPortStatic;
	HWND hDummyClientNum;
	HWND hServerIpEdit;
	HWND hServerPortEdit;
	HWND hDummyClientNumEdit;

	HWND hCreateClientButton;

	HWND hDummyClientNum50Button;
	HWND hDummyClientNum100Button;
	HWND hDummyClientNum500Button;
	HWND hDummyClientNum1000Button;

	HWND hDummyWriteEdit;
public:
	dummyClientWindow();
	~dummyClientWindow();
	void CreateDummyClientWindow(HWND hWnd, HINSTANCE hInst);
};

