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

	// �ػ󵵿� �°� ������ ũ�� ����
	RECT rt = { 0, 0, m_ptResolution.x, m_ptResolution.y };
	AdjustWindowRect(&rt, WS_OVERLAPPEDWINDOW, true);
	SetWindowPos(hWnd, nullptr, 100, 100, rt.right - rt.left, rt.bottom - rt.top, 0);
	hdc = GetDC(hWnd);

	// ������۸� ��Ʈ��, dc�� �Ҵ��ϱ�
	m_pMemTex = CResMgr::GetInstance()->CreateTexture(L"BackBuffer", (UINT)m_ptResolution.x, (UINT)m_ptResolution.y);
	hBit = CreateCompatibleBitmap(hdc, m_ptResolution.x, m_ptResolution.y);
	memDC = CreateCompatibleDC(hdc);

	HBITMAP hOldBit = (HBITMAP)SelectObject(memDC, hBit);
	DeleteObject(hOldBit);

	// ���� ���Ǵ� �귯�ÿ� �� �迭�� ����
	CreateBrushPen();
	m_graphics = new Graphics(m_pMemTex->GetDC());

	// Manager �ʱ�ȭ
	CPathMgr::GetInstance()->Init();
	CTimeMgr::GetInstance()->Init();
	CKeyMgr::GetInstance()->Init();
	CSceneMgr::GetInstance()->Init();


	return S_OK;
}

void CCore::CreateBrushPen()
{
	// Hollow Brush
	m_arrBrush[(UINT)BRUSH_TYPE::HOLLOW] = (HBRUSH)GetStockObject(HOLLOW_BRUSH); // �̹� ���ǵǾ� �ִ� �귯�� -> �ҷο� �귯��(���� �ʿ����)

	// RGB Pen
	m_arrPen[(UINT)PEN_TYPE::RED] = CreatePen(PS_SOLID, 1, RGB(255, 0, 0));
	m_arrPen[(UINT)PEN_TYPE::GREEN] = CreatePen(PS_SOLID, 1, RGB(0, 255, 0));
	m_arrPen[(UINT)PEN_TYPE::BLUE] = CreatePen(PS_SOLID, 1, RGB(0, 0, 255));
}


void CCore::Progress()
{
	// �Ŵ��� ������Ʈ
	CTimeMgr::GetInstance()->Update();
	CDecisionMgr::GetInstance()->Update();
	CKeyMgr::GetInstance()->Update();
	CSceneMgr::GetInstance()->Update();
	CCollisionMgr::GetInstance()->Update();

	// ȭ�� Ŭ����
	Rectangle(memDC, -1, -1, m_ptResolution.x + 1, m_ptResolution.y + 1);

	// ȭ�� �׸���
	CSceneMgr::GetInstance()->Render(memDC);

	// ������۸�(ȭ�� ����)
	BitBlt(hdc, 0, 0, m_ptResolution.x, m_ptResolution.y, memDC, 0, 0, SRCCOPY);
	/*TransparentBlt(hdc, 0, 0, ptResolution.x, ptResolution.y, memDC, 0, 0, ptResolution.x, ptResolution.y, RGB(255, 0, 255));*/

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

//#include "pch.h"
//#include "CCore.h"
//
//#include "CTimeMgr.h"
//#include "CKeyMgr.h"
//#include "CSceneMgr.h"
//#include "CPathMgr.h"
//#include "CCollisionMgr.h"
//#include "CEventMgr.h"
//#include "CResMgr.h"
//
//#include "CTexture.h"
//#include "CObject.h"
//
//ULONG_PTR g_gdiplusToken;
//
//CCore::CCore()
//	: m_hWnd(0)
//	, m_ptResolution{}
//	, m_hDC(0)
//	, m_arrBrush{}
//	, m_arrPen{}
//	, m_pMemTex(nullptr)
//	, m_graphics(nullptr)
//{
//}
//
//CCore::~CCore()
//{
//	ReleaseDC(m_hWnd, m_hDC);
//	delete m_graphics;
//
//	// ���ֻ���ϴ� �� ����ߴ��� �����ֱ�
//	for (int i = 0; i < (UINT)PEN_TYPE::END; i++)
//	{
//		DeleteObject(m_arrPen[i]);
//	}
//
//	GdiplusShutdown(g_gdiplusToken);
//}
//
//void CCore::CreateBrushPen()
//{
//	// Hollow Brush
//	m_arrBrush[(UINT)BRUSH_TYPE::HOLLOW] = (HBRUSH)GetStockObject(HOLLOW_BRUSH); // �̹� ���ǵǾ� �ִ� �귯�� -> �ҷο� �귯��(���� �ʿ����)
//
//	// RGB Pen
//	m_arrPen[(UINT)PEN_TYPE::RED] = CreatePen(PS_SOLID, 1, RGB(255, 0, 0));
//	m_arrPen[(UINT)PEN_TYPE::GREEN] = CreatePen(PS_SOLID, 1, RGB(0, 255, 0));
//	m_arrPen[(UINT)PEN_TYPE::BLUE] = CreatePen(PS_SOLID, 1, RGB(0, 0, 255));
//}
//
//
//int CCore::Init(HWND hWnd, POINT ptResolution)
//{
//	GdiplusStartupInput gdiplusStartupInput;
//	GdiplusStartup(&g_gdiplusToken, &gdiplusStartupInput, NULL);
//
//	m_hWnd = hWnd;
//	m_ptResolution = ptResolution;
//
//	// �ػ󵵿� �°� ������ ũ�� ����
//	RECT rt = { 0, 0, m_ptResolution.x, m_ptResolution.y };
//	AdjustWindowRect(&rt, WS_OVERLAPPEDWINDOW, true);
//	SetWindowPos(m_hWnd, nullptr, 100, 100, rt.right - rt.left, rt.bottom - rt.top, 0);
//
//	m_hDC = GetDC(m_hWnd);
//
//	// ���� ���۸� �뵵�� �ؽ��� ����
//	m_pMemTex = CResMgr::GetInstance()->CreateTexture(L"BackBuffer", (UINT)m_ptResolution.x, (UINT)m_ptResolution.y);
//
//	// ���� ���Ǵ� �귯�ÿ� �� �迭�� ����
//	CreateBrushPen();
//
//	m_graphics = new Graphics(m_pMemTex->GetDC());
//
//	// Manager �ʱ�ȭ
//	CPathMgr::GetInstance()->Init();
//	CTimeMgr::GetInstance()->Init();
//	CKeyMgr::GetInstance()->Init();
//	CSceneMgr::GetInstance()->Init();
//
//	return S_OK;
//}
//
//void CCore::Progress()
//{
//	// �Ŵ��� ������Ʈ================================================
//	CTimeMgr::GetInstance()->Update();
//	CKeyMgr::GetInstance()->Update();
//
//	// �� ������Ʈ====================================================
//	CSceneMgr::GetInstance()->Update();
//	CCollisionMgr::GetInstance()->Update();
//
//	// ������ ����====================================================
//	Rectangle(m_pMemTex->GetDC(), -1, -1, m_ptResolution.x + 1, m_ptResolution.y + 1); // ȭ�� Ŭ����
//
//	CSceneMgr::GetInstance()->Render(m_pMemTex->GetDC()); // ȭ�� �׸���
//
//	// �ι�° ���ۿ��� ù��° ����(������ ǥ�õǴ� ȭ��)�� ����->�ٿ��ֱ�
//	BitBlt(m_hDC, 0, 0, m_ptResolution.x, m_ptResolution.y, m_pMemTex->GetDC(), 0, 0, SRCCOPY);
//
//	// �̺�Ʈ ���� ó��================================================
//	// (���������� ��� ��ġ�� ���������� �Ѿ�� ���� ����)=============
//	CEventMgr::GetInstance()->Update();
//}
