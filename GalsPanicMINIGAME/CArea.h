#pragma once
#include "CObject.h"

class CArea
	: public CObject
{
private:
	vector<Vec2> vecPoint;

public:
	vector<Vec2> GetVector() { return vecPoint; }

public:
	virtual void Update();
	virtual void Render(HDC hdc);
	
public:
	CArea();
	~CArea();
};

