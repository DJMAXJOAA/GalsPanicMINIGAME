#include "pch.h"
#include "CDecisionMgr.h"

#include "CPlayer.h"
#include "CArea.h"

#include "CKeyMgr.h"

bool CDecisionMgr::PlayerMovingPossible(KEY key)
{
	if (!(key == KEY::A || key == KEY::W || key == KEY::D || key == KEY::S))
		return true;

	// �Ǿ�, �ǵ�
	auto itrFront = pArea->GetlstPoint().begin();
	auto itrBack = prev(pArea->GetlstPoint().end());

	Vec2 playerPos = pPlayer->GetPos();
	int playerSpeed = pPlayer->GetSpeed();

	int max_xpos, min_xpos; // ��
	int max_ypos, min_ypos; 

	if (itrPlayerPos == itrBack) // 1. �÷��̾��� ���� ��ġ = ��ǥ�� �� ������
	{
		if (itrFront->x == itrPlayerPos->x) // x��ǥ ���� : ���Ʒ� �̵�
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
		if (itrFront->y == itrPlayerPos->y) // y��ǥ ���� : �¿�� �̵�
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
	else if (itrPlayerPos == itrFront) // 2. �÷��̾��� ���� ��ġ = ��ǥ�� �� ó��
	{
		if (next(itrPlayerPos, 1)->x == itrPlayerPos->x) // x��ǥ ���� : ���Ʒ� �̵�
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
		if (next(itrPlayerPos, 1)->y == itrPlayerPos->y) // y��ǥ ���� : �¿�� �̵�
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
	else // 3. �ƹ����̳�
	{
		if (next(itrPlayerPos, 1)->x == itrPlayerPos->x) // x��ǥ ���� : ���Ʒ� �̵�
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
		if (next(itrPlayerPos, 1)->y == itrPlayerPos->y) // y��ǥ ���� : �¿�� �̵�
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

void CDecisionMgr::DrawInit()
{
	POINT PlayerPos = { pPlayer->GetPos().x, pPlayer->GetPos().y };
	CKeyMgr::GetInstance()->SetKeyAvailability(KEY::SPACE, false);
	pArea->AddToNewPoint(PlayerPos);
	pArea->SetDraw(true);
	
	list<POINT>& lstPoint = pArea->GetlstPoint();
	// �ӽ� ���� ���ͷ����͵��� �迭 (���۰� ���� ����)
	vecSave.push_back(itrPlayerPos);
	if (itrPlayerPos == lstPoint.end())
	{
		vecSave.push_back(lstPoint.begin());
	}
	else
	{
		vecSave.push_back(next(itrPlayerPos, 1));
	}

	
}

bool CDecisionMgr::DrawCollide()
{
	list<POINT>& myArea = pArea->GetlstPoint();
	auto itrFront = myArea.begin();
	auto itrBack = prev(myArea.end());
	POINT playerPos = { pPlayer->GetPos().x, pPlayer->GetPos().y };

	int max_xpos, min_xpos; // ��
	int max_ypos, min_ypos;

	int odd_number;
	if (itrFront->x == next(itrFront, 1)->x)
		odd_number = 0;
	else
		odd_number = 1;
	for (auto itr = itrFront; itr != itrBack; ++itr)
	{
		switch (odd_number)
		{
		case 0: // x�� ������ (y������ ��)
		{
			if (next(itr, 1)->y > itr->y)	 { max_ypos = next(itr, 1)->y; min_ypos = itr->y; }
			else							 { min_ypos = next(itr, 1)->y; max_ypos = itr->y; }	
			if (itr->x == playerPos.x && min_ypos <= playerPos.y && playerPos.y <= max_ypos)
			{
				itrPlayerPos = itr;
				return true;
			}
			odd_number = 1;
		}
			break;
		case 1: // y�� ������ (x������ ��)
		{
			if (next(itr, 1)->x > itr->x)	 { max_xpos = next(itr, 1)->x; min_xpos = itr->x; }
			else							 { min_xpos = next(itr, 1)->x; max_xpos = itr->x; }	
			if (itr->y == playerPos.y && min_xpos <= playerPos.x && playerPos.x <= max_xpos)
			{
				itrPlayerPos = itr;
				return true;
			}
			odd_number = 0;
		}
			break;
		default:
			break;
		}
	}

	return false;
}

void CDecisionMgr::DrawEnd()
{
	POINT playerPos = { CDecisionMgr::GetInstance()->GetPlayer()->GetPos().x, CDecisionMgr::GetInstance()->GetPlayer()->GetPos().y };

	pArea->AddToNewPoint(playerPos);

	list<POINT>& lstPoint = pArea->GetlstPoint();
	list<POINT>& newPoint = pArea->GetnewPoint();
	// �ӽ� ���� ���ͷ����͵��� �迭 (���۰� ���� ����)
	vecSave.push_back(itrPlayerPos);
	if (itrPlayerPos == lstPoint.end())
	{
		vecSave.push_back(lstPoint.begin());
	}
	else
	{
		vecSave.push_back(next(itrPlayerPos, 1));
	}

	// ����Ʈ �̾���̱�
    list<POINT> renewPoint;
	renewPoint.insert(renewPoint.end(), lstPoint.begin(), vecSave.front());
	renewPoint.insert(renewPoint.end(), newPoint.begin(), newPoint.end());
	renewPoint.insert(renewPoint.end(), vecSave.back(), lstPoint.end());
	
	lstPoint.swap(renewPoint);

	// �迭�� �ݿ�
	POINT* temp = new POINT[lstPoint.size()];
	int i = 0;
	for (auto itr = lstPoint.begin(); itr != lstPoint.end(); ++itr)
	{
		temp[i].x = itr->x;
		temp[i].y = itr->y;
		i++;
	}
	POINT* save = pArea->GetptMyArea();
	delete[] save;
	save = temp;

	pPlayer->SetState(MOVE);
	pArea->SetDraw(false);
	pArea->ResetNewPoint();
	// �浹�ϸ�
}

void CDecisionMgr::Init(CPlayer* player, CArea* area)
{
	pPlayer = player;
	pArea = area;
	itrPlayerPos = pArea->GetlstPoint().begin();
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
	auto itrFront = pArea->GetlstPoint().begin();
	auto itrBack = prev(pArea->GetlstPoint().end());

	Vec2 playerPos = pPlayer->GetPos();

	// �� ���� ��ǥ�� ���� ������ �� ���� ��ǥ ���ͷ����� ����

	if (itrPlayerPos == itrBack) // 1. �÷��̾��� ���� ��ġ = ��ǥ�� �� �������̸�
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
	else if (itrPlayerPos == itrFront) // 2. �÷��̾��� ���� ��ġ = ��ǥ�� �� ó��
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
	else // 3. �� ���� ��Ȳ
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
	POINT PlayerPos = { pPlayer->GetPos().x, pPlayer->GetPos().y };

	if (CKeyMgr::GetInstance()->GetKeyState(KEY::A) == KEY_STATE::TAP
		&& CKeyMgr::GetInstance()->GetKeyAvailability(KEY::A))
	{
		pArea->AddToNewPoint(PlayerPos);
		CKeyMgr::GetInstance()->SetKeyAvailability(KEY::D, false);
		CKeyMgr::GetInstance()->SetKeyAvailability(KEY::A, true);
		CKeyMgr::GetInstance()->SetKeyAvailability(KEY::W, true);
		CKeyMgr::GetInstance()->SetKeyAvailability(KEY::S, true);
	}
	else if (CKeyMgr::GetInstance()->GetKeyState(KEY::W) == KEY_STATE::TAP
		&& CKeyMgr::GetInstance()->GetKeyAvailability(KEY::W))
	{
		pArea->AddToNewPoint(PlayerPos);
		CKeyMgr::GetInstance()->SetKeyAvailability(KEY::S, false);
		CKeyMgr::GetInstance()->SetKeyAvailability(KEY::A, true);
		CKeyMgr::GetInstance()->SetKeyAvailability(KEY::W, true);
		CKeyMgr::GetInstance()->SetKeyAvailability(KEY::D, true);
	}
	else if (CKeyMgr::GetInstance()->GetKeyState(KEY::D) == KEY_STATE::TAP
		&& CKeyMgr::GetInstance()->GetKeyAvailability(KEY::D))
	{
		pArea->AddToNewPoint(PlayerPos);
		CKeyMgr::GetInstance()->SetKeyAvailability(KEY::A, false);
		CKeyMgr::GetInstance()->SetKeyAvailability(KEY::W, true);
		CKeyMgr::GetInstance()->SetKeyAvailability(KEY::D, true);
		CKeyMgr::GetInstance()->SetKeyAvailability(KEY::S, true);
	}
	else if (CKeyMgr::GetInstance()->GetKeyState(KEY::S) == KEY_STATE::TAP
		&& CKeyMgr::GetInstance()->GetKeyAvailability(KEY::S))
	{
		pArea->AddToNewPoint(PlayerPos);
		CKeyMgr::GetInstance()->SetKeyAvailability(KEY::W, false);
		CKeyMgr::GetInstance()->SetKeyAvailability(KEY::A, true);
		CKeyMgr::GetInstance()->SetKeyAvailability(KEY::D, true);
		CKeyMgr::GetInstance()->SetKeyAvailability(KEY::S, true);
	}

	if (DrawCollide() == true) // ������ ����
		DrawEnd();
}

CDecisionMgr::CDecisionMgr()
	: pPlayer(nullptr)
	, pArea(nullptr)
{
}

CDecisionMgr::~CDecisionMgr()
{
}
