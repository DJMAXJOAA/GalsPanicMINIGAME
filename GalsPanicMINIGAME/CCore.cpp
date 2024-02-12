#include "pch.h"
#include "CCore.h"

#include "CObject.h"

#include "CTexture.h"

#include "CTimeMgr.h"
#include "CKeyMgr.h"
#include "CSceneMgr.h"
#include "CDecisionMgr.h"
#include "CCollisionMgr.h"
#include "CPathMgr.h"
#include "CEventMgr.h"
#include "CResMgr.h"

ULONG_PTR g_gdiplusToken;

int CCore::Init(HWND _hWnd, POINT _ptResolution)
{
	hWnd = _hWnd;
	m_ptResolution = _ptResolution;

	GdiplusStartupInput gdiplusStartupInput;
	GdiplusStartup(&g_gdiplusToken, &gdiplusStartupInput, NULL);

	// 해상도에 맞게 윈도우 크기 조정
	RECT rt = { 0, 0, m_ptResolution.x, m_ptResolution.y };
	AdjustWindowRect(&rt, WS_OVERLAPPEDWINDOW, true);
	SetWindowPos(hWnd, nullptr, 100, 100, rt.right - rt.left, rt.bottom - rt.top, 0);
	hdc = GetDC(hWnd);

	// 더블버퍼링 비트맵, dc값 할당하기
	m_pMemTex = CResMgr::GetInstance()->CreateTexture(L"BackBuffer", (UINT)m_ptResolution.x, (UINT)m_ptResolution.y);
	hBit = CreateCompatibleBitmap(hdc, m_ptResolution.x, m_ptResolution.y);
	memDC = CreateCompatibleDC(hdc);

	HBITMAP hOldBit = (HBITMAP)SelectObject(memDC, hBit);
	DeleteObject(hOldBit);

	// 자주 사용되는 브러시와 펜 배열을 생성
	CreateBrushPen();
	m_graphics = new Graphics(m_pMemTex->GetDC());

	// Manager 초기화
	CPathMgr::GetInstance()->Init();
	CTimeMgr::GetInstance()->Init();
	CKeyMgr::GetInstance()->Init();
	CSceneMgr::GetInstance()->Init();


	return S_OK;
}

void CCore::CreateBrushPen()
{
	// Hollow Brush
	m_arrBrush[(UINT)BRUSH_TYPE::HOLLOW] = (HBRUSH)GetStockObject(HOLLOW_BRUSH); // 이미 정의되어 있는 브러쉬 -> 할로우 브러쉬(지울 필요없음)

	// RGB Pen
	m_arrPen[(UINT)PEN_TYPE::RED] = CreatePen(PS_SOLID, 1, RGB(255, 0, 0));
	m_arrPen[(UINT)PEN_TYPE::GREEN] = CreatePen(PS_SOLID, 1, RGB(0, 255, 0));
	m_arrPen[(UINT)PEN_TYPE::BLUE] = CreatePen(PS_SOLID, 1, RGB(0, 0, 255));
}


void CCore::Progress()
{
	// 매니저 업데이트
	CTimeMgr::GetInstance()->Update();
	CDecisionMgr::GetInstance()->Update();
	CKeyMgr::GetInstance()->Update();
	CSceneMgr::GetInstance()->Update();
	CCollisionMgr::GetInstance()->Update();

	// 화면 클리어
	Rectangle(memDC, -1, -1, m_ptResolution.x + 1, m_ptResolution.y + 1);

	// 화면 그리기
	CSceneMgr::GetInstance()->Render(memDC);

	// 더블버퍼링(화면 복붙)
	BitBlt(hdc, 0, 0, m_ptResolution.x, m_ptResolution.y, memDC, 0, 0, SRCCOPY);
	TransparentBlt(hdc, 0, 0, m_ptResolution.x, m_ptResolution.y, memDC, 0, 0, m_ptResolution.x, m_ptResolution.y, RGB(255, 0, 255));

	CEventMgr::GetInstance()->Update();
}

CCore::CCore()
	: hWnd(0)
	, m_ptResolution{}
	, hdc(0)
	, hBit(0)
	, memDC(0)
	, m_arrBrush{}
	, m_arrPen{}
	, m_pMemTex(nullptr)
	, m_graphics(nullptr)
{
}

CCore::~CCore()
{
	ReleaseDC(hWnd, hdc);
	DeleteDC(memDC);
	DeleteObject(hBit);

	for (int i = 0; i < (UINT)PEN_TYPE::END; i++)
	{
		DeleteObject(m_arrPen[i]);
	}

	delete m_graphics;
	GdiplusShutdown(g_gdiplusToken);
}