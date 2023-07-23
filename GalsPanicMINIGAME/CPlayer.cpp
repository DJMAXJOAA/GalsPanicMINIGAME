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

	if (CKeyMgr::GetInstance()->GetKeyState(KEY::SPACE) == KEY_STATE::HOLD
	 && CKeyMgr::GetInstance()->GetKeyAvailability(KEY::SPACE))
	{
		if (CKeyMgr::GetInstance()->GetKeyState(KEY::A) == KEY_STATE::HOLD)
		{
			iDirection = LEFT;
			iState = DRAW;
			return;
		}
		else if (CKeyMgr::GetInstance()->GetKeyState(KEY::W) == KEY_STATE::HOLD)
		{
			iDirection = UP;
			iState = DRAW;
			return;
		}
		else if (CKeyMgr::GetInstance()->GetKeyState(KEY::D) == KEY_STATE::HOLD)
		{
			iDirection = RIGHT;
			iState = DRAW;
			return;
		}
		else if (CKeyMgr::GetInstance()->GetKeyState(KEY::S) == KEY_STATE::HOLD)
		{
			iDirection = DOWN;
			iState = DRAW;
			return;
		}
	}

	if (CKeyMgr::GetInstance()->GetKeyState(KEY::A) == KEY_STATE::HOLD
		&& CKeyMgr::GetInstance()->GetKeyAvailability(KEY::A))
	{
		if (fInterval < vPos.x)
			vPos.x -= iSpeed;
	}
	if (CKeyMgr::GetInstance()->GetKeyState(KEY::W) == KEY_STATE::HOLD
		&& CKeyMgr::GetInstance()->GetKeyAvailability(KEY::W))
	{
		if (fInterval < vPos.y)
			vPos.y -= iSpeed;
	}
	if (CKeyMgr::GetInstance()->GetKeyState(KEY::D) == KEY_STATE::HOLD
		&& CKeyMgr::GetInstance()->GetKeyAvailability(KEY::D))
	{
		if (vResolution.x - fInterval > vPos.x)
			vPos.x += iSpeed;
	}
	if (CKeyMgr::GetInstance()->GetKeyState(KEY::S) == KEY_STATE::HOLD
		&& CKeyMgr::GetInstance()->GetKeyAvailability(KEY::S))
	{
		if (vResolution.y - fInterval > vPos.y)
			vPos.y += iSpeed;
	}


	SetPos(vPos);
}

void CPlayer::Draw()
{
	Vec2 vResolution = CCore::GetInstance()->GetResolution();
	float fInterval = 40.f;

	Vec2 vPos = GetPos();

	if (CKeyMgr::GetInstance()->GetKeyState(KEY::A) == KEY_STATE::HOLD
		&& CKeyMgr::GetInstance()->GetKeyAvailability(KEY::A))
	{
		if (fInterval < vPos.x)
			vPos.x -= iSpeed;
		iDirection = LEFT;
	}
	if (CKeyMgr::GetInstance()->GetKeyState(KEY::W) == KEY_STATE::HOLD
		&& CKeyMgr::GetInstance()->GetKeyAvailability(KEY::W))
	{
		if (fInterval < vPos.y)
			vPos.y -= iSpeed;
		iDirection = UP;
	}
	if (CKeyMgr::GetInstance()->GetKeyState(KEY::D) == KEY_STATE::HOLD
		&& CKeyMgr::GetInstance()->GetKeyAvailability(KEY::D))
	{
		if (vResolution.x - fInterval > vPos.x)
			vPos.x += iSpeed;
		iDirection = RIGHT;
	}
	if (CKeyMgr::GetInstance()->GetKeyState(KEY::S) == KEY_STATE::HOLD
		&& CKeyMgr::GetInstance()->GetKeyAvailability(KEY::S))
	{
		if (vResolution.y - fInterval > vPos.y)
			vPos.y += iSpeed;
		iDirection = DOWN;
	}


	SetPos(vPos);
}

void CPlayer::Update()
{
	switch (iState)
	{
	case MOVE:
		Move();
		break;
	case DEAD:
		break;
	default:
		break;
	}
}

void CPlayer::Render(HDC hdc)
{
	Vec2 Pos = GetPos();
	Vec2 Scale = GetScale();
	Ellipse(hdc, (int)(Pos.x - Scale.x / 2.f), (int)(Pos.y - Scale.y / 2.f),
				 (int)(Pos.x + Scale.x / 2.f), (int)(Pos.y + Scale.y / 2.f));
}


