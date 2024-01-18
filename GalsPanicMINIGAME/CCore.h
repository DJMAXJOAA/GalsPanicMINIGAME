#pragma once
class CTexture;
class CCore
{
	SINGLE(CCore);
private:
	HWND hWnd;
	POINT m_ptResolution;
	HDC hdc;

	HBITMAP hBit;
	HDC memDC;
	CTexture* m_pMemTex;		// 백 버퍼 텍스쳐 (더블버퍼링)

	// 자주 사용하는 GDI 오브젝트
	HBRUSH	m_arrBrush[(UINT)BRUSH_TYPE::END];
	HPEN	m_arrPen[(UINT)PEN_TYPE::END];

	Graphics* m_graphics;		// GDI+

public:
	int Init(HWND _hWnd, POINT _ptResolution);
	void Progress();

public:
	HWND GetMainhWnd() { return hWnd; }
	POINT GetResolution() { return m_ptResolution; }
	HDC GetMainDC() { return hdc; }
	HDC GetMemDC() { return memDC; }
	HBRUSH GetBrush(BRUSH_TYPE _eType) { return m_arrBrush[(UINT)_eType]; }
	HPEN GetPen(PEN_TYPE _eType) { return m_arrPen[(UINT)_eType]; }
	CTexture* GetMemTex() { return m_pMemTex; }
	Graphics* GetGraphics() { return m_graphics; }

private:
	void CreateBrushPen();

private:
	CCore();
	~CCore();
};

//
//#pragma once
//
//class CTexture;
//
//class CCore
//{
//	SINGLE(CCore);
//private:
//	HWND		m_hWnd;			// 메인 윈도우 핸들
//	POINT		m_ptResolution;	// 해상도 정보
//	HDC			m_hDC;			// 메인 윈도우에 Draw할 DC
//
//	CTexture*	m_pMemTex;		// 백 버퍼 텍스쳐 (더블버퍼링)
//
//	// 자주 사용하는 GDI 오브젝트
//	HBRUSH	m_arrBrush[(UINT)BRUSH_TYPE::END];
//	HPEN	m_arrPen[(UINT)PEN_TYPE::END];
//
//	Graphics*	m_graphics;		// GDI+
//
//private:
//	CCore();
//	~CCore();
//
//public:
//	int Init(HWND hWnd, POINT ptResolution);
//	void Progress();
//
//public:
//	HWND GetMainhWnd() { return m_hWnd; }
//	HDC GetMainDC() { return m_hDC; }
//	POINT GetResolution() { return m_ptResolution; }
//	HBRUSH GetBrush(BRUSH_TYPE _eType) { return m_arrBrush[(UINT)_eType]; }
//	HPEN GetPen(PEN_TYPE _eType) { return m_arrPen[(UINT)_eType]; }
//	CTexture* GetMemTex() { return m_pMemTex; }
//	Graphics* GetGraphics() { return m_graphics; }
//
//private:
//	void CreateBrushPen();
//};
//
