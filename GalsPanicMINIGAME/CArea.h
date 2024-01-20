#pragma once
#include "CObject.h"

class CTexture;
class CNumber;

class CArea
	: public CObject
{
private:
	list<POINT> lstPoint;
	list<POINT> newPoint;
	POINT* ptBorder; // �ܰ��� ����
	POINT* ptMyArea; // �� ����
	bool bDrawing; // �׸��� ��

private:
	CTexture* pTex[4]; // ��Ʈ�� �̹���

private:
	CNumber* pAreaExtent;
	float fExtent;

public:
	list<POINT>& GetlstPoint() { return lstPoint; }
	list<POINT>& GetnewPoint() { return newPoint; }
	POINT* GetptMyArea() { return ptMyArea; }
	float GetExtent() { return fExtent; }
	void SetDraw(bool TF) { bDrawing = TF; }

public:
	void AddToNewPoint(POINT _point) { newPoint.push_back(_point); };
	void CalculuateMyArea();
	void ResetNewPoint() { newPoint.clear(); }

public:
	virtual void Update();
	virtual void Render(HDC hdc);
	
public:
	CArea(CNumber* number);
	virtual ~CArea();

	CLONE(CArea);
};

