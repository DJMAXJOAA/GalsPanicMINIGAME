#pragma once
#include "CObject.h"

class CArea
	: public CObject
{
private:
	list<POINT> lstPoint;
	list<POINT> newPoint;
	POINT* ptBorder; // �ܰ��� ����
	POINT* ptMyArea; // �� ����
	bool bDrawing; // �׸��� ��

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

