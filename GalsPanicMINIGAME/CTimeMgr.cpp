#include "pch.h"
#include "CTimeMgr.h"

#include "CCore.h"

CTimeMgr::CTimeMgr()
	: liCurCount{}
	, liFrequency{}
	, liPrevCount{}
	, dDT(0.)
	, dAcc(0.)
	, iCallCount(0)
	, iFPS(0)
{
}

CTimeMgr::~CTimeMgr()
{
}


void CTimeMgr::Init()
{
	// 현재 카운트 횟수
	QueryPerformanceCounter(&liCurCount);

	// 초당 카운트 횟수
	QueryPerformanceFrequency(&liFrequency);
}

void CTimeMgr::Update()
{
	QueryPerformanceCounter(&liCurCount);

	// 이전 프레임의 카운팅과, 현재 프레임의 카운팅 값의 차이를 구한다
	dDT = (double)(liCurCount.QuadPart - liPrevCount.QuadPart) /
		(double)liFrequency.QuadPart;

	// 이전카운트 값을 현재 카운트값으로 갱신(다음 계산 위해)
	liPrevCount = liCurCount;

	++iCallCount;
	dAcc += dDT; // DT 누적

	if (dAcc >= 1.) // 1초마다 한번 체크
	{
		iFPS = iCallCount;
		dAcc = 0.;
		iCallCount = 0;

		wchar_t szBuffer[255] = {};
		swprintf_s(szBuffer, L"FPS : %d, DT : %f", iFPS, dDT);
		SetWindowText(CCore::GetInstance()->GetMainhWnd(), szBuffer); // 타이틀 지정
	}
}

