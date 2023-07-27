#include "pch.h"
#include "CMonster.h"

#include "CTexture.h"

CMonster::CMonster()
	: iSpeed(10)
	, fAngle(Random(0, 360))
	, fDirection(cosf(RADIAN(fAngle)), sinf(RADIAN(fAngle)))
{
}

CMonster::~CMonster()
{
}


void CMonster::Update()
{
}

void CMonster::Render(HDC hdc)
{
}

