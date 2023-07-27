#include "pch.h"
#include "CPlayer.h"

#include "CKeyMgr.h"
#include "CTimeMgr.h"
#include "CDecisionMgr.h"
#include "CCore.h"
#include "CPathMgr.h"

#include "CArea.h"
#include "CTexture.h"

CPlayer::CPlayer()
	: iState((int)PLAYER_STATE::MOVE)
	, iDirection((int)PLAYER_DIRECTION::LEFT)
	, iSpeed(10)
{
	{
		pTex = new CTexture;
		wstring strFilePath = CPathMgr::GetInstance()->GetContentPath();
		strFilePath += L"texture\\PlayerTemp.bmp";
		pTex->Load(strFilePath);
	}
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
				iDirection = LEFT;
				vPos.x -= iSpeed;
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
				iDirection = UP;
				vPos.y -= iSpeed;
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
				iDirection = RIGHT;
				vPos.x += iSpeed;
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
				iDirection = DOWN;
				vPos.y += iSpeed;
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

	if (CKeyMgr::GetInstance()->GetKeyState(KEY::A) == KEY_STATE::HOLD)
	{
			iDirection = LEFT;
		if (fInterval < vPos.x && CKeyMgr::GetInstance()->GetKeyAvailability(KEY::A))
		{
			vPos.x -= iSpeed;
		}
	}
	if (CKeyMgr::GetInstance()->GetKeyState(KEY::W) == KEY_STATE::HOLD)
	{
			iDirection = UP;
		if (fInterval < vPos.y && CKeyMgr::GetInstance()->GetKeyAvailability(KEY::W))
		{
			vPos.y -= iSpeed;
		}
	}
	if (CKeyMgr::GetInstance()->GetKeyState(KEY::D) == KEY_STATE::HOLD)
	{
			iDirection = RIGHT;
		if (vResolution.x - fInterval > vPos.x && CKeyMgr::GetInstance()->GetKeyAvailability(KEY::D))
		{
			vPos.x += iSpeed;
		}
	}
	if (CKeyMgr::GetInstance()->GetKeyState(KEY::S) == KEY_STATE::HOLD)
	{
			iDirection = DOWN;
		if (vResolution.y - fInterval > vPos.y && CKeyMgr::GetInstance()->GetKeyAvailability(KEY::S))
		{
			vPos.y += iSpeed;
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
	//Ellipse(hdc, (int)(Pos.x - Scale.x / 2.f), (int)(Pos.y - Scale.y / 2.f),
	//			 (int)(Pos.x + Scale.x / 2.f), (int)(Pos.y + Scale.y / 2.f));

	int iWidth = pTex->Width();
	int iHeight = pTex->Height();
	TransparentBlt(hdc, (int)(Pos.x - Scale.x / 2.f), (int)(Pos.y - Scale.y / 2.f), iWidth, iHeight, pTex->GetDC(), 0, 0, iWidth, iHeight, RGB(255, 0, 255));
}


