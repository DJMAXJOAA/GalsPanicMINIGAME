#include "pch.h"
#include "CArea.h"
#include "CCore.h"

CArea::CArea()
	: lstPoint{}
	, newPoint{}
	, ptBorder(nullptr)
	, ptMyArea(nullptr)
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

	int size = lstPoint.size();

	list<POINT>::iterator firstItr = lstPoint.begin();
	list<POINT>::iterator lastItr = lstPoint.end();

	ptMyArea = new POINT[size];
	int i = 0;
	for (auto itr = firstItr; itr != lastItr; ++itr)
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

void CArea::AddToNewPoint()
{
}

void CArea::ResetNewPoint()
{
}

void CArea::RenewlstPoint()
{
}

void CArea::Update()
{
}

void CArea::Render(HDC hdc)
{
	int size = lstPoint.size();

	Polygon(hdc, ptBorder, 4); // 기본 영역
	Polygon(hdc, ptMyArea, size); // 내 영역
}


