#include "pch.h"
#include "CPlayer.h"

#include "CKeyMgr.h"
#include "CTimeMgr.h"
#include "CArea.h"

CPlayer::CPlayer()
	: iState((int)PLAYER_STATE::MOVE)
	, iDirection((int)PLAYER_DIRECTION::LEFT)
	, pArea(nullptr)
{
}

CPlayer::~CPlayer()
{
}

void CPlayer::Move()
{
	Vec2 vPos = GetPos();

	if (CKeyMgr::GetInstance()->GetKeyState(KEY::A) == KEY_STATE::HOLD)
	{
		vPos.x -= 400.f * fDT;
	}
	if (CKeyMgr::GetInstance()->GetKeyState(KEY::W) == KEY_STATE::HOLD)
	{
		vPos.y -= 400.f * fDT;
	}
	if (CKeyMgr::GetInstance()->GetKeyState(KEY::D) == KEY_STATE::HOLD)
	{
		vPos.x += 400.f * fDT;
	}
	if (CKeyMgr::GetInstance()->GetKeyState(KEY::S) == KEY_STATE::HOLD)
	{
		vPos.y += 400.f * fDT;
	}

	SetPos(vPos);
}

void CPlayer::Collide()
{
	vector<Vec2> AreaPos = pArea->GetVector();
	for (int i = 0; i < AreaPos.size() - 1; i++)
	{
		if (AreaPos[i].x == AreaPos[i + 1].x)
		{

		}
		else if (AreaPos[i].y == AreaPos[i + 1].y)
		{

		}
	}
	
}

void CPlayer::Update()
{
	Collide();
	Move();
}

void CPlayer::Render(HDC hdc)
{
	Vec2 Pos = GetPos();
	Vec2 Scale = GetScale();
	Ellipse(hdc, (int)(Pos.x - Scale.x / 2.f), (int)(Pos.y - Scale.y / 2.f),
				 (int)(Pos.x + Scale.x / 2.f), (int)(Pos.y + Scale.y / 2.f));
}


