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

public:
	list<POINT>& GetPoint() { return lstPoint; }

public:
	void AddToNewPoint(POINT _point) { newPoint.push_back(_point); };
	void ResetNewPoint() { newPoint.clear(); }
	void RenewlstPoint();

public:
	virtual void Update();
	virtual void Render(HDC hdc);
	
public:
	CArea();
	~CArea();
};

