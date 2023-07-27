#include "pch.h"
#include "CCore.h"

#include "CObject.h"

#include "CTimeMgr.h"
#include "CKeyMgr.h"
#include "CSceneMgr.h"
#include "CDecisionMgr.h"
#include "CPathMgr.h"

int CCore::Init(HWND _hWnd, POINT _ptResolution)
{
	hWnd = _hWnd;
	ptResolution = _ptResolution;

	// 해상도에 맞게 윈도우 크기 조정
	RECT rt = { 0, 0, ptResolution.x, ptResolution.y };
	AdjustWindowRect(&rt, WS_OVERLAPPEDWINDOW, true);
	SetWindowPos(hWnd, nullptr, 100, 100, rt.right - rt.left, rt.bottom - rt.top, 0);
	hdc = GetDC(hWnd);

	// 더블버퍼링 비트맵, dc값 할당하기
	hBit = CreateCompatibleBitmap(hdc, ptResolution.x, ptResolution.y);
	memDC = CreateCompatibleDC(hdc);

	HBITMAP hOldBit = (HBITMAP)SelectObject(memDC, hBit);
	DeleteObject(hOldBit);

	// Manager 초기화
	CPathMgr::GetInstance()->Init();
	CTimeMgr::GetInstance()->Init();
	CKeyMgr::GetInstance()->Init();
	CSceneMgr::GetInstance()->Init();


	return S_OK;
}

void CCore::Progress()
{
	// 매니저 업데이트
	CTimeMgr::GetInstance()->Update();
	CDecisionMgr::GetInstance()->Update();
	CKeyMgr::GetInstance()->Update();
	CSceneMgr::GetInstance()->Update();


	// 화면 클리어
	Rectangle(memDC, -1, -1, ptResolution.x + 1, ptResolution.y + 1);

	// 화면 그리기
	CSceneMgr::GetInstance()->Render(memDC);

	// 더블버퍼링(화면 복붙)
	BitBlt(hdc, 0, 0, ptResolution.x, ptResolution.y, memDC, 0, 0, SRCCOPY);
	/*TransparentBlt(hdc, 0, 0, ptResolution.x, ptResolution.y, memDC, 0, 0, ptResolution.x, ptResolution.y, RGB(255, 0, 255));*/
}

CCore::CCore()
	: hWnd(0)
	, ptResolution{}
	, hdc(0)
	, hBit(0)
	, memDC(0)
{
}

CCore::~CCore()
{
	ReleaseDC(hWnd, hdc);
	DeleteDC(memDC);
	DeleteObject(hBit);
}
