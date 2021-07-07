#pragma once

enum hDummyHMENU
{
	DummyClientStatic = 300,
	ServerIpStatic,
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
	HWND hDummyClientStatic;

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
	int dummyClientNum;
public:
	dummyClientWindow();
	~dummyClientWindow();
	void CreateDummyClientWindow(HWND hWnd, HINSTANCE hInst);
	HWND GethDummyClientNumEdit() { return hDummyClientNumEdit; }
	HWND GethServerIpEdit() { return hServerIpEdit; }
	HWND GethServerPortEdit() { return hServerPortEdit; }
	HWND GethDummyWriteEdit() { return hDummyWriteEdit; }
	void SetDummyClientNum(int num) { dummyClientNum = num; }
};

