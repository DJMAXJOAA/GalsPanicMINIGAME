#include "pch.h"
#include "CArea.h"
#include "CCore.h"

#include "CPlayer.h"
#include "CDecisionMgr.h"

CArea::CArea()
	: lstPoint{}
	, newPoint{}
	, ptBorder(nullptr)
	, ptMyArea(nullptr)
	, bDrawing(false)
{
	POINT vResolution = CCore::GetInstance()->GetResolution();
	LONG iInterval = 40;
	LONG iInitialValue = 200;

	// 내 영역
	lstPoint.push_back(POINT{ iInterval + 0 * iInitialValue, vResolution.y - iInterval - 0 * iInitialValue });
	lstPoint.push_back(POINT{ iInterval + 0 * iInitialValue, vResolution.y - iInterval - 2 * iInitialValue });
	lstPoint.push_back(POINT{ iInterval + 1 * iInitialValue, vResolution.y - iInterval - 2 * iInitialValue });
	lstPoint.push_back(POINT{ iInterval + 1 * iInitialValue, vResolution.y - iInterval - 1 * iInitialValue });
	lstPoint.push_back(POINT{ iInterval + 2 * iInitialValue, vResolution.y - iInterval - 1 * iInitialValue });
	lstPoint.push_back(POINT{ iInterval + 2 * iInitialValue, vResolution.y - iInterval - 0 * iInitialValue });

	list<POINT>::iterator firstItr = lstPoint.begin();
	list<POINT>::iterator lastItr = lstPoint.end();

	ptMyArea = new POINT[lstPoint.size()+1];
	int i = 0;
	for (auto& itr = firstItr; itr != lastItr; ++itr)
	{
		ptMyArea[i].x = itr->x;
		ptMyArea[i].y = itr->y;
		i++;
	}

	// 기본 영역
	ptBorder = new POINT[4];
	ptBorder[0].x = iInterval;
	ptBorder[0].y = vResolution.y - iInterval;
	ptBorder[1].x = iInterval;
	ptBorder[1].y = iInterval;
	ptBorder[2].x = vResolution.x - iInterval;
	ptBorder[2].y = iInterval;
	ptBorder[3].x = vResolution.x - iInterval;
	ptBorder[3].y = vResolution.y - iInterval;
}

CArea::~CArea()
{
	delete[] ptBorder;
	delete[] ptMyArea;
}

void CArea::Update()
{
	for (list<POINT>::iterator itr = lstPoint.begin(); itr != prev(lstPoint.end(), 1); ++itr)
	{
		if (itr->x == next(itr, 1)->x && itr->y == next(itr, 1)->y)
		{
			lstPoint.erase(itr);
			break;
		}
	}

}

void CArea::Render(HDC hdc)
{
	static int asdf;
	asdf++;

	Polygon(hdc, ptBorder, 4); // 기본 영역
	Polygon(hdc, ptMyArea, lstPoint.size()); // 내 영역


	int radius = 10;
	wstring temp;
	for (int i = 0; i < lstPoint.size(); i++)
	{
		temp = L"" + std::to_wstring(i);
		TextOut(hdc, ptMyArea[i].x + radius, ptMyArea[i].y + radius, temp.c_str(), temp.length());
		temp = L"" + std::to_wstring(ptMyArea[i].x) + L", " + std::to_wstring(ptMyArea[i].y);
		TextOut(hdc, ptMyArea[i].x + radius, ptMyArea[i].y + 3*radius, temp.c_str(), temp.length());
		Ellipse(hdc, ptMyArea[i].x - radius, ptMyArea[i].y - radius, ptMyArea[i].x + + radius, ptMyArea[i].y + radius);
	}

	
	if (bDrawing == false)
		return;
	POINT playerPos = { CDecisionMgr::GetInstance()->GetPlayer()->GetPos().x, CDecisionMgr::GetInstance()->GetPlayer()->GetPos().y };
	auto itrFront = newPoint.begin();
	auto itrBack = newPoint.end();
	MoveToEx(hdc, itrFront->x, itrFront->y, NULL);
	for(auto& itr = itrFront; itr != itrBack; ++itr)
	{
		LineTo(hdc, itr->x, itr->y);
		MoveToEx(hdc, itr->x, itr->y, NULL);
	}
	LineTo(hdc, playerPos.x, playerPos.y);

	for (list<POINT>::iterator itr = newPoint.begin(); itr != newPoint.end(); ++itr)
	{
		Ellipse(hdc, itr->x - radius, itr->y - radius, itr->x + +radius, itr->y + radius);
	}
}


