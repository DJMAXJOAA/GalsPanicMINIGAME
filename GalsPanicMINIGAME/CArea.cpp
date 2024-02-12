#include "pch.h"
#include "CArea.h"
#include "CCore.h"
#include "CPlayer.h"
#include "CTexture.h"
#include "CNumber.h"

#include "CDecisionMgr.h"
#include "CPathMgr.h"
#include "CResMgr.h"

CArea::CArea(CNumber* number)
	: lstPoint{}
	, newPoint{}
	, vecBorder{}
	, ptMyArea(nullptr)
	, bDrawing(false)
	, pAreaExtent(number)
{
	// 텍스쳐 로딩
	pTex[0] = CResMgr::GetInstance()->LoadTexture(L"NewJeans", L"texture\\NewJeans.bmp");
	pTex[1] = CResMgr::GetInstance()->LoadTexture(L"Background", L"texture\\Background2.bmp");
	pTex[2] = CResMgr::GetInstance()->LoadTexture(L"ball1", L"texture\\BALL1.bmp");
	pTex[3] = CResMgr::GetInstance()->LoadTexture(L"ball2", L"texture\\BALL2.bmp");

	POINT vResolution = CCore::GetInstance()->GetResolution();
	LONG iInterval = 40;
	LONG iInitialValue = 200;

	// 내 영역
	lstPoint.push_back(POINT{ iInterval + 0 * iInitialValue, vResolution.y - iInterval - 0 * iInitialValue });
	lstPoint.push_back(POINT{ iInterval + 0 * iInitialValue, vResolution.y - iInterval - 1 * iInitialValue });
	lstPoint.push_back(POINT{ iInterval + 1 * iInitialValue, vResolution.y - iInterval - 1 * iInitialValue });
	lstPoint.push_back(POINT{ iInterval + 1 * iInitialValue, vResolution.y - iInterval - 0 * iInitialValue });

	list<POINT>::iterator firstItr = lstPoint.begin();
	list<POINT>::iterator lastItr = lstPoint.end();

	ptMyArea = new POINT[lstPoint.size() + 1];
	int i = 0;
	for (auto& itr = firstItr; itr != lastItr; ++itr)
	{
		ptMyArea[i].x = itr->x;
		ptMyArea[i].y = itr->y;
		i++;
	}
	CalculuateMyArea(); // 넓이 계산

	// 기본 영역
	vecBorder.resize(4);
	vecBorder[0].x = iInterval;
	vecBorder[0].y = vResolution.y - iInterval;
	vecBorder[1].x = iInterval;
	vecBorder[1].y = iInterval;
	vecBorder[2].x = vResolution.x - iInterval;
	vecBorder[2].y = iInterval;
	vecBorder[3].x = vResolution.x - iInterval;
	vecBorder[3].y = vResolution.y - iInterval;
}

CArea::~CArea()
{
	lstPoint.clear();
	newPoint.clear();
	vecBorder.clear();
	if (ptMyArea != nullptr)
	{
		delete[] ptMyArea;
	}
}

void CArea::CalculuateMyArea()
{
	float sum1 = 0;
	float sum2 = 0;
	for (auto itr = lstPoint.begin(); itr != prev(lstPoint.end(),1); ++itr)
	{
		sum1 += (float)itr->x * (float)next(itr, 1)->y;
		sum2 += (float)itr->y * (float)next(itr, 1)->x;
	}
	auto itrFront = lstPoint.begin();
	auto itrBack = prev(lstPoint.end(), 1);
	sum1 += (float)itrBack->x * (float)itrFront->y;
	sum2 += (float)itrBack->y * (float)itrFront->x;

	float myArea = (sum1 - sum2)/2;
	fExtent = myArea / 828000.0 * 100.0;
}

void CArea::Update()
{
	if (fExtent > 80.f)
	{
		ChangeScene(SCENE_TYPE::ENDING);
	}
	for (list<POINT>::iterator itr = lstPoint.begin(); itr != prev(lstPoint.end(), 1); ++itr)
	{
		if (itr->x == next(itr, 1)->x && itr->y == next(itr, 1)->y)
		{
			lstPoint.erase(itr);
			break;
		}
	}
	if (pAreaExtent)
	{
		pAreaExtent->SetNumber((int)fExtent);
	}
	CalculuateMyArea();
}

void CArea::Render(HDC hdc)
{
	{
		int iWidth = pTex[0]->Width();
		int iHeight = pTex[0]->Height();
		BitBlt(hdc, 0, 0, iWidth, iHeight, pTex[0]->GetDC(), 0, 0, SRCCOPY);

		int iWidth2 = pTex[1]->Width();
		int iHeight2 = pTex[1]->Height();
		HBRUSH hBrush = CreateSolidBrush(RGB(255, 0, 255));
		HBRUSH oldBrush = (HBRUSH)SelectObject(pTex[1]->GetDC(), hBrush);
		HPEN hPen = CreatePen(PS_DOT, 2, RGB(255, 0, 0));
		HPEN oldPen = (HPEN)SelectObject(pTex[1]->GetDC(), hPen);

		Polygon(pTex[1]->GetDC(), ptMyArea, lstPoint.size()); // 내 영역

		MoveToEx(pTex[1]->GetDC(), vecBorder[0].x, vecBorder[0].y, NULL);
		for (int i = 1; i < 4; i++)
		{
			LineTo(pTex[1]->GetDC(), vecBorder[i].x, vecBorder[i].y);
			MoveToEx(pTex[1]->GetDC(), vecBorder[i].x, vecBorder[i].y, NULL);
		}
		LineTo(pTex[1]->GetDC(), vecBorder[0].x, vecBorder[0].y);

		SelectObject(hdc, oldBrush);
		DeleteObject(hBrush);
		SelectObject(hdc, oldPen);
		DeleteObject(hPen);
		TransparentBlt(hdc, 0, 0, iWidth2, iHeight2, pTex[1]->GetDC(), 0, 0, iWidth2, iHeight2, RGB(255, 0, 255));
	}

	int radius = 7;
	wstring temp;
	for (int i = 0; i < lstPoint.size(); i++)
	{
		int iWidth = pTex[2]->Width();
		int iHeight = pTex[2]->Height();
		temp = L"" + std::to_wstring(i);
		TextOut(hdc, ptMyArea[i].x + radius, ptMyArea[i].y + radius, temp.c_str(), temp.length());
		temp = L"" + std::to_wstring(ptMyArea[i].x) + L", " + std::to_wstring(ptMyArea[i].y);
		TextOut(hdc, ptMyArea[i].x + radius, ptMyArea[i].y + 3*radius, temp.c_str(), temp.length());
		TransparentBlt(hdc, ptMyArea[i].x - radius, ptMyArea[i].y - radius, iWidth, iHeight, pTex[2]->GetDC(), 0, 0, iWidth, iHeight, RGB(255, 0, 255));
	}

	if (bDrawing == false)
		return;

	// 그림 그리는 중일때 실행
	{
		POINT playerPos = { CDecisionMgr::GetInstance()->GetPlayer()->GetPos().x, CDecisionMgr::GetInstance()->GetPlayer()->GetPos().y };
		auto itrFront = newPoint.begin();
		auto itrBack = newPoint.end();

		HPEN hPen = CreatePen(PS_DOT, 2, RGB(0, 0, 255));
		HPEN oldPen = (HPEN)SelectObject(hdc, hPen);

		MoveToEx(hdc, itrFront->x, itrFront->y, NULL);
		for (auto& itr = itrFront; itr != itrBack; ++itr)
		{
			LineTo(hdc, itr->x, itr->y);
			MoveToEx(hdc, itr->x, itr->y, NULL);
		}
		LineTo(hdc, playerPos.x, playerPos.y);

		SelectObject(hdc, oldPen);
		DeleteObject(hPen);

		for (list<POINT>::iterator itr = newPoint.begin(); itr != newPoint.end(); ++itr)
		{
			int iWidth = pTex[3]->Width();
			int iHeight = pTex[3]->Height();
			TransparentBlt(hdc, itr->x - radius, itr->y - radius, iWidth, iHeight, pTex[3]->GetDC(), 0, 0, iWidth, iHeight, RGB(255, 0, 255));
		}
	}
}


