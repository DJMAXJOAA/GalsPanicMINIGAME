#include "pch.h"
#include "CMonster.h"

#include "CPathMgr.h"
#include "CCore.h"

#include "CTexture.h"
#include "CCollider.h"

CMonster::CMonster()
	: iSpeed(20)
	, fAngle(Random(0, 360))
	, fDirection(cosf(RADIAN(fAngle)), sinf(RADIAN(fAngle)))
{
	pTex = new CTexture;
	wstring strFilePath = CPathMgr::GetInstance()->GetContentPath();
	strFilePath += L"texture\\MonsterTemp.bmp";
	pTex->Load(strFilePath);

	CreateCollider();
	GetCollider()->SetScale(Vec2(15.f, 15.f));
}

CMonster::~CMonster()
{
}

void CMonster::Move()
{
	Vec2 vResolution = CCore::GetInstance()->GetResolution();
	float fInterval = 40.f;

	Vec2 vPos = GetPos();

	if (vResolution.x - fInterval * 2 < vPos.x) fDirection.x *= -1;
	if (fInterval > vPos.x) fDirection.x *= -1;
	if (vResolution.y - fInterval * 2 < vPos.y) fDirection.y *= -1;
	if (fInterval > vPos.y) fDirection.y *= -1;

	vPos += fDirection * iSpeed;

	SetPos(vPos);
}


void CMonster::Update()
{
	Move();
}

void CMonster::Render(HDC hdc)
{
	Vec2 Pos = GetPos();
	Vec2 Scale = GetScale();

	int iWidth = pTex->Width();
	int iHeight = pTex->Height();
	TransparentBlt(hdc, (int)(Pos.x - Scale.x / 2.f), (int)(Pos.y - Scale.y / 2.f), iWidth, iHeight, pTex->GetDC(), 0, 0, iWidth, iHeight, RGB(255, 0, 255));
}

