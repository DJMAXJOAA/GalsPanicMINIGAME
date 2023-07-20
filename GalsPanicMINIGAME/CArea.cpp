#include "pch.h"
#include "CArea.h"
#include "CCore.h"

CArea::CArea()
	: vecPoint{}
{
	Vec2 vResolution = CCore::GetInstance()->GetResolution();
	float fInterval = 40.f;

	vecPoint.push_back(Vec2(fInterval, fInterval));
	vecPoint.push_back(Vec2(vResolution.x - fInterval, fInterval));
	vecPoint.push_back(Vec2(vResolution.x - fInterval, vResolution.y - fInterval));
	vecPoint.push_back(Vec2(fInterval, vResolution.y - fInterval));
}

CArea::~CArea()
{
}

void CArea::Update()
{

}

void CArea::Render(HDC hdc)
{
	int size = vecPoint.size();
	POINT* temp = new POINT[size];
	for (int i = 0; i < size; i++)
	{
		temp[i].x = vecPoint[i].x;
		temp[i].y = vecPoint[i].y;
	}

	Polygon(hdc, temp, size);
	delete[] temp;
}


