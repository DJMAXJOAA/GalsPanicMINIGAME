#pragma once
#include "CObject.h"

class CArea
	: public CObject
{
private:
	list<POINT> lstPoint;
	list<POINT> newPoint;
	POINT* ptBorder; // 외곽선 영역
	POINT* ptMyArea; // 내 영역
	bool bDrawing; // 그리는 중

public:
	list<POINT>& GetlstPoint() { return lstPoint; }
	list<POINT>& GetnewPoint() { return newPoint; }
	POINT* GetptMyArea() { return ptMyArea; }
	void SetDraw(bool TF) { bDrawing = TF; }

public:
	void AddToNewPoint(POINT _point) { newPoint.push_back(_point); };
	void ResetNewPoint() { newPoint.clear(); }

public:
	virtual void Update();
	virtual void Render(HDC hdc);
	
public:
	CArea();
	~CArea();
};

