#include "pch.h"
#include "CDecisionMgr.h"

#include "CPlayer.h"
#include "CArea.h"

#include "CKeyMgr.h"

bool CDecisionMgr::PlayerMovingPossible(KEY key)
{
	if (!(key == KEY::A || key == KEY::W || key == KEY::D || key == KEY::S))
		return true;

	// 맨앞, 맨뒤
	auto itrFront = pArea->GetPoint().begin();
	auto itrBack = prev(pArea->GetPoint().end());

	Vec2 playerPos = pPlayer->GetPos();
	int playerSpeed = pPlayer->GetSpeed();

	int max_xpos, min_xpos; // 비교
	int max_ypos, min_ypos; 

	if (itrPlayerPos == itrBack) // 1. 플레이어의 현재 위치 = 좌표의 맨 마지막
	{
		if (itrFront->x == itrPlayerPos->x) // x좌표 동일 : 위아래 이동
		{
			if (itrFront->y > itrPlayerPos->y)				 { max_ypos = itrFront->y; min_ypos = itrPlayerPos->y; }
			else											 { min_ypos = itrFront->y; max_ypos = itrPlayerPos->y; }	
			if (prev(itrPlayerPos, 1)->x > itrPlayerPos->x)	 { max_xpos = prev(itrPlayerPos, 1)->x; min_xpos = itrPlayerPos->x; }
			else											 { min_xpos = prev(itrPlayerPos, 1)->x; max_xpos = itrPlayerPos->x; }

			switch (key)
			{
			case KEY::W:
				if (playerPos.y - playerSpeed >= min_ypos)
					return true;
				break;
			case KEY::S:
				if (playerPos.y + playerSpeed <= max_ypos)
					return true;
				break;
			case KEY::A:
				if (playerPos.x - playerSpeed >= min_xpos && playerPos.y == itrPlayerPos->y)
				{
					itrPlayerPos = prev(itrPlayerPos, 1);
					return true;
				}
				break;
			case KEY::D:
				if (playerPos.x + playerSpeed <= max_xpos && playerPos.y == itrPlayerPos->y)
				{
					itrPlayerPos = prev(itrPlayerPos, 1);
					return true;
				}
				break;
			}
		}
		if (itrFront->y == itrPlayerPos->y) // y좌표 동일 : 좌우로 이동
		{
			if (itrFront->x > itrPlayerPos->x)				{ max_xpos = itrFront->x; min_xpos = itrPlayerPos->x; }
			else											{ min_xpos = itrFront->x; max_xpos = itrPlayerPos->x; }
			if (prev(itrPlayerPos, 1)->y > itrPlayerPos->y) { max_ypos = prev(itrPlayerPos, 1)->y; min_ypos = itrPlayerPos->y; }
			else											{ min_ypos = prev(itrPlayerPos, 1)->y; max_ypos = itrPlayerPos->y; }

			switch (key)
			{
			case KEY::W:
				if (playerPos.y - playerSpeed >= min_ypos && playerPos.x == itrPlayerPos->x)
				{
					itrPlayerPos = prev(itrPlayerPos, 1);
					return true;
				}
				break;
			case KEY::S:
				if (playerPos.y + playerSpeed <= max_ypos && playerPos.x == itrPlayerPos->x)
				{
					itrPlayerPos = prev(itrPlayerPos, 1);
					return true;
				}
				break;
			case KEY::A:
				if (playerPos.x - playerSpeed >= min_xpos)
					return true;
				break;
			case KEY::D:
				if (playerPos.x + playerSpeed <= max_xpos)
					return true;
				break;
			}
		}
	}
	else if (itrPlayerPos == itrFront) // 2. 플레이어의 현재 위치 = 좌표의 맨 처음
	{
		if (next(itrPlayerPos, 1)->x == itrPlayerPos->x) // x좌표 동일 : 위아래 이동
		{
			if (next(itrPlayerPos, 1)->y > itrPlayerPos->y)	 { max_ypos = next(itrPlayerPos, 1)->y; min_ypos = itrPlayerPos->y; }
			else											 { min_ypos = next(itrPlayerPos, 1)->y; max_ypos = itrPlayerPos->y; }	
			if (itrBack->x > itrPlayerPos->x)				 { max_xpos = itrBack->x; min_xpos = itrPlayerPos->x; }
			else											 { min_xpos = itrBack->x; max_xpos = itrPlayerPos->x; }

			switch (key)
			{
			case KEY::W:
				if (playerPos.y - playerSpeed >= min_ypos)
					return true;
				break;
			case KEY::S:
				if (playerPos.y + playerSpeed <= max_ypos)
					return true;
				break;
			case KEY::A:
				if (playerPos.x - playerSpeed >= min_xpos && playerPos.y == itrPlayerPos->y)
				{
					itrPlayerPos = itrBack;
					return true;
				}
				break;
			case KEY::D:
				if (playerPos.x + playerSpeed <= max_xpos && playerPos.y == itrPlayerPos->y)
				{
					itrPlayerPos = itrBack;
					return true;
				}
				break;
			}
		}
		if (next(itrPlayerPos, 1)->y == itrPlayerPos->y) // y좌표 동일 : 좌우로 이동
		{
			if (next(itrPlayerPos, 1)->x > itrPlayerPos->x)	{ max_xpos = next(itrPlayerPos, 1)->x; min_xpos = itrPlayerPos->x; }
			else											{ min_xpos = next(itrPlayerPos, 1)->x; max_xpos = itrPlayerPos->x; }
			if (itrBack->y > itrPlayerPos->y)				{ max_ypos = itrBack->y; min_ypos = itrPlayerPos->y; }
			else											{ min_ypos = itrBack->y; max_ypos = itrPlayerPos->y; }

			switch (key)
			{
			case KEY::W:
				if (playerPos.y - playerSpeed >= min_ypos && playerPos.x == itrPlayerPos->x)
				{
					itrPlayerPos = prev(itrPlayerPos, 1);
					return true;
				}
				break;
			case KEY::S:
				if (playerPos.y + playerSpeed <= max_ypos && playerPos.x == itrPlayerPos->x)
				{
					itrPlayerPos = prev(itrPlayerPos, 1);
					return true;
				}
				break;
			case KEY::A:
				if (playerPos.x - playerSpeed >= min_xpos)
					return true;
				break;
			case KEY::D:
				if (playerPos.x + playerSpeed <= max_xpos)
					return true;
				break;
			}
		}
	}
	else // 3. 아무곳이나
	{
		if (next(itrPlayerPos, 1)->x == itrPlayerPos->x) // x좌표 동일 : 위아래 이동
		{
			if (next(itrPlayerPos, 1)->y > itrPlayerPos->y)	 { max_ypos = next(itrPlayerPos, 1)->y; min_ypos = itrPlayerPos->y; }
			else											 { min_ypos = next(itrPlayerPos, 1)->y; max_ypos = itrPlayerPos->y; }	
			if (prev(itrPlayerPos, 1)->x > itrPlayerPos->x)	 { max_xpos = prev(itrPlayerPos, 1)->x; min_xpos = itrPlayerPos->x; }
			else											 { min_xpos = prev(itrPlayerPos, 1)->x; max_xpos = itrPlayerPos->x; }

			switch (key)
			{
			case KEY::W:
				if (playerPos.y - playerSpeed >= min_ypos)
					return true;
				break;
			case KEY::S:
				if (playerPos.y + playerSpeed <= max_ypos)
					return true;
				break;
			case KEY::A:
				if (playerPos.x - playerSpeed >= min_xpos && playerPos.y == itrPlayerPos->y)
				{
					itrPlayerPos = prev(itrPlayerPos, 1);
					return true;
				}
				break;
			case KEY::D:
				if (playerPos.x + playerSpeed <= max_xpos && playerPos.y == itrPlayerPos->y)
				{
					itrPlayerPos = prev(itrPlayerPos, 1);
					return true;
				}
				break;
			}
		}
		if (next(itrPlayerPos, 1)->y == itrPlayerPos->y) // y좌표 동일 : 좌우로 이동
		{
			if (next(itrPlayerPos, 1)->x > itrPlayerPos->x)	{ max_xpos = next(itrPlayerPos, 1)->x; min_xpos = itrPlayerPos->x; }
			else											{ min_xpos = next(itrPlayerPos, 1)->x; max_xpos = itrPlayerPos->x; }
			if (prev(itrPlayerPos, 1)->y > itrPlayerPos->y) { max_ypos = prev(itrPlayerPos, 1)->y; min_ypos = itrPlayerPos->y; }
			else											{ min_ypos = prev(itrPlayerPos, 1)->y; max_ypos = itrPlayerPos->y; }

			switch (key)
			{
			case KEY::W:
				if (playerPos.y - playerSpeed >= min_ypos && playerPos.x == itrPlayerPos->x)
				{
					itrPlayerPos = prev(itrPlayerPos, 1);
					return true;
				}
				break;
			case KEY::S:
				if (playerPos.y + playerSpeed <= max_ypos && playerPos.x == itrPlayerPos->x)
				{
					itrPlayerPos = prev(itrPlayerPos, 1);
					return true;
				}
				break;
			case KEY::A:
				if (playerPos.x - playerSpeed >= min_xpos)
					return true;
				break;
			case KEY::D:
				if (playerPos.x + playerSpeed <= max_xpos)
					return true;
				break;
			}
		}
	}

	return false;
}

bool CDecisionMgr::PlayerDrawInit()
{
	return false;
}

void CDecisionMgr::Init(CPlayer* player, CArea* area)
{
	pPlayer = player;
	pArea = area;
	itrPlayerPos = pArea->GetPoint().begin();
}

void CDecisionMgr::Update()
{
	int playerState = pPlayer->GetState();
	switch (playerState)
	{
	case MOVE:
		MoveUpdate();
		break;
	case DRAW:
		DrawUpdate();
		break;
	case DEAD:
		break;
	default:
		break;
	}

}

void CDecisionMgr::MoveUpdate()
{
	auto itrFront = pArea->GetPoint().begin();
	auto itrBack = prev(pArea->GetPoint().end());

	Vec2 playerPos = pPlayer->GetPos();

	// 내 다음 좌표와 값이 같으면 내 현재 좌표 이터레이터 갱신

	if (itrPlayerPos == itrBack) // 1. 플레이어의 현재 위치 = 좌표의 맨 마지막이면
	{
		if (itrFront->x == (int)playerPos.x && itrFront->y == (int)playerPos.y)
		{
			itrPlayerPos = itrFront;
			return;
		}
		if (prev(itrPlayerPos, 1)->x == (int)playerPos.x && prev(itrPlayerPos, 1)->y == (int)playerPos.y)
		{
			itrPlayerPos = prev(itrPlayerPos, 1);
			return;
		}
	}
	else if (itrPlayerPos == itrFront) // 2. 플레이어의 현재 위치 = 좌표의 맨 처음
	{
		if (next(itrPlayerPos, 1)->x == (int)playerPos.x && next(itrPlayerPos, 1)->y == (int)playerPos.y)
		{
			itrPlayerPos = next(itrPlayerPos, 1);
			return;
		}
		if (itrBack->x == (int)playerPos.x && itrBack->y == (int)playerPos.y)
		{
			itrPlayerPos = itrBack;
			return;
		}
	}
	else // 3. 그 외의 상황
	{
		if (next(itrPlayerPos, 1)->x == (int)playerPos.x && next(itrPlayerPos, 1)->y == (int)playerPos.y)
		{
			itrPlayerPos = next(itrPlayerPos, 1);
			return;
		}
		if (prev(itrPlayerPos, 1)->x == (int)playerPos.x && prev(itrPlayerPos, 1)->y == (int)playerPos.y)
		{
			itrPlayerPos = prev(itrPlayerPos, 1);
			return;
		}
	}
}

void CDecisionMgr::DrawUpdate()
{
	
}

CDecisionMgr::CDecisionMgr()
	: pPlayer(nullptr)
	, pArea(nullptr)
{
}

CDecisionMgr::~CDecisionMgr()
{
}
