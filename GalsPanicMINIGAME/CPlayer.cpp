#include "pch.h"
#include "CPlayer.h"

#include "CKeyMgr.h"
#include "CTimeMgr.h"
#include "CDecisionMgr.h"
#include "CCore.h"

#include "CArea.h"

CPlayer::CPlayer()
	: iState((int)PLAYER_STATE::MOVE)
	, iDirection((int)PLAYER_DIRECTION::LEFT)
	, iSpeed(10)
{
}

CPlayer::~CPlayer()
{
}

void CPlayer::Move()
{
	Vec2 vResolution = CCore::GetInstance()->GetResolution();
	float fInterval = 40.f;

	Vec2 vPos = GetPos();

	if (CKeyMgr::GetInstance()->GetKeyState(KEY::SPACE) == KEY_STATE::TAP
		&& CKeyMgr::GetInstance()->GetKeyAvailability(KEY::SPACE) == false)
	{
		iState = MOVE;
		CKeyMgr::GetInstance()->SetKeyAvailability(KEY::D, true);
		CKeyMgr::GetInstance()->SetKeyAvailability(KEY::A, true);
		CKeyMgr::GetInstance()->SetKeyAvailability(KEY::W, true);
		CKeyMgr::GetInstance()->SetKeyAvailability(KEY::S, true);
		return;
	}

	if (CKeyMgr::GetInstance()->GetKeyState(KEY::SPACE) == KEY_STATE::TAP
	 && CKeyMgr::GetInstance()->GetKeyAvailability(KEY::SPACE) == true)
	{
		if (CKeyMgr::GetInstance()->GetKeyState(KEY::A) == KEY_STATE::HOLD)
		{
			if (fInterval < vPos.x)
			{
				vPos.x -= iSpeed;
				iDirection = LEFT;
				iState = DRAW;
				CDecisionMgr::GetInstance()->DrawInit();
				CKeyMgr::GetInstance()->SetKeyAvailability(KEY::D, false);
				CKeyMgr::GetInstance()->SetKeyAvailability(KEY::A, true);
				CKeyMgr::GetInstance()->SetKeyAvailability(KEY::W, true);
				CKeyMgr::GetInstance()->SetKeyAvailability(KEY::S, true);
			}
		}
		else if (CKeyMgr::GetInstance()->GetKeyState(KEY::W) == KEY_STATE::HOLD)
		{
			if (fInterval < vPos.y)
			{
				vPos.y -= iSpeed;
				iDirection = UP;
				iState = DRAW;
				CDecisionMgr::GetInstance()->DrawInit();
				CKeyMgr::GetInstance()->SetKeyAvailability(KEY::S, false);
				CKeyMgr::GetInstance()->SetKeyAvailability(KEY::A, true);
				CKeyMgr::GetInstance()->SetKeyAvailability(KEY::W, true);
				CKeyMgr::GetInstance()->SetKeyAvailability(KEY::D, true);
			}
		}
		else if (CKeyMgr::GetInstance()->GetKeyState(KEY::D) == KEY_STATE::HOLD)
		{
			if (vResolution.x - fInterval > vPos.x)
			{
				vPos.x += iSpeed;
				iDirection = RIGHT;
				iDirection = RIGHT;
				iState = DRAW;
				CDecisionMgr::GetInstance()->DrawInit();
				CKeyMgr::GetInstance()->SetKeyAvailability(KEY::A, false);
				CKeyMgr::GetInstance()->SetKeyAvailability(KEY::W, true);
				CKeyMgr::GetInstance()->SetKeyAvailability(KEY::D, true);
				CKeyMgr::GetInstance()->SetKeyAvailability(KEY::S, true);
			}
		}
		else if (CKeyMgr::GetInstance()->GetKeyState(KEY::S) == KEY_STATE::HOLD)
		{
			if (vResolution.y - fInterval > vPos.y)
			{
				vPos.y += iSpeed;
				iDirection = DOWN;
				iState = DRAW;
				CDecisionMgr::GetInstance()->DrawInit();
				CKeyMgr::GetInstance()->SetKeyAvailability(KEY::W, false);
				CKeyMgr::GetInstance()->SetKeyAvailability(KEY::A, true);
				CKeyMgr::GetInstance()->SetKeyAvailability(KEY::D, true);
				CKeyMgr::GetInstance()->SetKeyAvailability(KEY::S, true);
			}
		}
		SetPos(vPos);
		return;
	}

	if (CKeyMgr::GetInstance()->GetKeyState(KEY::A) == KEY_STATE::HOLD
		&& CKeyMgr::GetInstance()->GetKeyAvailability(KEY::A))
	{
		if (fInterval < vPos.x)
		{
			vPos.x -= iSpeed;
			iDirection = LEFT;
		}
	}
	if (CKeyMgr::GetInstance()->GetKeyState(KEY::W) == KEY_STATE::HOLD
		&& CKeyMgr::GetInstance()->GetKeyAvailability(KEY::W))
	{
		if (fInterval < vPos.y)
		{
			vPos.y -= iSpeed;
			iDirection = UP;
		}
	}
	if (CKeyMgr::GetInstance()->GetKeyState(KEY::D) == KEY_STATE::HOLD
		&& CKeyMgr::GetInstance()->GetKeyAvailability(KEY::D))
	{
		if (vResolution.x - fInterval > vPos.x)
		{
			vPos.x += iSpeed;
			iDirection = RIGHT;
		}
	}
	if (CKeyMgr::GetInstance()->GetKeyState(KEY::S) == KEY_STATE::HOLD
		&& CKeyMgr::GetInstance()->GetKeyAvailability(KEY::S))
	{
		if (vResolution.y - fInterval > vPos.y)
		{
			vPos.y += iSpeed;
			iDirection = DOWN;
		}
	}

	SetPos(vPos);
}

void CPlayer::Update()
{
	if (iState != DEAD)
		Move();
}

void CPlayer::Render(HDC hdc)
{
	Vec2 Pos = GetPos();
	Vec2 Scale = GetScale();
	Ellipse(hdc, (int)(Pos.x - Scale.x / 2.f), (int)(Pos.y - Scale.y / 2.f),
				 (int)(Pos.x + Scale.x / 2.f), (int)(Pos.y + Scale.y / 2.f));
}


