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
	POINT* ptBorder; // 외곽선 영역
	POINT* ptMyArea; // 내 영역
	bool bDrawing; // 그리는 중

private:
	CTexture* pTex[4]; // 비트맵 이미지

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

