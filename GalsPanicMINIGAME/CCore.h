#pragma once
class CCore
{
	SINGLE(CCore);
private:
	HWND hWnd;
	POINT ptResolution;
	HDC hdc;

	HBITMAP hBit;
	HDC memDC;

public:
	int Init(HWND _hWnd, POINT _ptResolution);
	void Progress();

public:
	HWND GetMainhWnd() { return hWnd; }
	POINT GetResolution() { return ptResolution; }
	HDC getMainDC() { return hdc; }
	HDC getMemDC() { return memDC; }

private:
	CCore();
	~CCore();
};

