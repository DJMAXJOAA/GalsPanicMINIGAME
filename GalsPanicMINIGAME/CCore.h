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

	// 자주 사용하는 GDI 오브젝트
	HBRUSH	m_arrBrush[(UINT)BRUSH_TYPE::END];
	HPEN	m_arrPen[(UINT)PEN_TYPE::END];

public:
	int Init(HWND _hWnd, POINT _ptResolution);
	void Progress();

public:
	HWND GetMainhWnd() { return hWnd; }
	POINT GetResolution() { return ptResolution; }
	HDC getMainDC() { return hdc; }
	HDC getMemDC() { return memDC; }
	HBRUSH GetBrush(BRUSH_TYPE _eType) { return m_arrBrush[(UINT)_eType]; }
	HPEN GetPen(PEN_TYPE _eType) { return m_arrPen[(UINT)_eType]; }

private:
	CCore();
	~CCore();
};

