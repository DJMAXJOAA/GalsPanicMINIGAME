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
	vector<POINT> vecBorder;
	POINT* ptMyArea;
	bool bDrawing; // 그리는 중

private:
	CTexture* pTex[4]; // 비트맵 이미지

private:
	CNumber* pAreaExtent;
	float fExtent;

public:
	list<POINT>& GetlstPoint() { return lstPoint; }
	list<POINT>& GetnewPoint() { return newPoint; }
	POINT* GetMyArea() { return ptMyArea; }
	float GetExtent() { return fExtent; }
	void SetDraw(bool TF) { bDrawing = TF; }
	void SetPoint(POINT* _ptPoint) { ptMyArea = _ptPoint; }

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

