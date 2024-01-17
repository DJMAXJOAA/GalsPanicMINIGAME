#include "pch.h"
#include "CMonster.h"

#include "CPathMgr.h"
#include "CCore.h"

#include "CTexture.h"
#include "CCollider.h"

CMonster::CMonster()
	: iSpeed(10)
	, fAngle(Random(0, 360))
	, fDirection(cosf(RADIAN(fAngle)), sinf(RADIAN(fAngle)))
	, pCollide(nullptr)
{
	pTex = new CTexture;
	wstring strFilePath = CPathMgr::GetInstance()->GetContentPath();
	strFilePath += L"texture\\MonsterTemp.bmp";
	pTex->Load(strFilePath);

	SetScale(Vec2(31.f, 29.f));

	CreateCollider();
	GetCollider()->SetScale(Vec2(31.f, 29.f));
	GetCollider()->SetOffsetPos(Vec2(-4.f, -5.f));
}

CMonster::~CMonster()
{
}

void CMonster::Update()
{
	Vec2 vResolution = CCore::GetInstance()->GetResolution();
	float fInterval = 40.f;

	Vec2 vPos = GetPos();

	if (vResolution.x - fInterval < vPos.x)
	{
		fDirection.x *= -1;
		vPos.x -= iSpeed;
	}
	if (fInterval > vPos.x)
	{
		fDirection.x *= -1;
		vPos.x += iSpeed;
	}
	if (vResolution.y - fInterval < vPos.y)
	{
		fDirection.y *= -1;
		vPos.y -= iSpeed;
	}
	if (fInterval > vPos.y)
	{
		fDirection.y *= -1;
		vPos.y += iSpeed;
	}

	vPos += fDirection * iSpeed;

	SetPos(vPos);
}

void CMonster::Render(HDC hdc)
{
	Vec2 Pos = GetPos();
	Vec2 Scale = GetScale();
	ComponetRender(hdc);

	int iWidth = pTex->Width();
	int iHeight = pTex->Height();
	TransparentBlt(hdc,
		(int)(Pos.x - Scale.x / 2.f),
		(int)(Pos.y - Scale.y / 2.f),
		iWidth,
		iHeight,
		pTex->GetDC(),
		0,
		0,
		iWidth,
		iHeight,
		RGB(255, 0, 255));
}

void CMonster::OnCollisionEnter(CCollider* _pOther)
{
	CObject* obj = _pOther->GetObj();
	if (pCollide != obj && obj->GetType() == GROUP_TYPE::MONSTER)
	{
		CMonster* mon = (CMonster*)obj;
		Vec2 tempDirecion = GetDirection();
		Vec2 otherDirection = mon->GetDirection();

		fDirection = otherDirection;
		otherDirection = tempDirecion;

		mon->SetDirection(otherDirection);
		SetCollide(obj);
		mon->SetCollide(this);
	}
}

