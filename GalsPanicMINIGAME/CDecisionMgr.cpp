#include "pch.h"
#include "CDecisionMgr.h"

#include "CPlayer.h"
#include "CArea.h"

#include "CKeyMgr.h"
#include "CCore.h"

bool CDecisionMgr::PlayerMovingPossible(KEY key)
{
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
	
	auto itrFront = pArea->GetlstPoint().begin();
	auto itrBack = pArea->GetlstPoint().end();
	// �ӽ� ���� ���ͷ����͵��� �迭 (���۰� ���� ����)
	vecSave.push_back(itrPlayerPos);
	if (itrPlayerPos == itrBack)
	{
		vecSave.push_back(itrFront);
	}
	else
	{
		vecSave.push_back(next(itrPlayerPos, 1));
	}

	
}

bool CDecisionMgr::DrawCollide()
{
	auto itrFront = pArea->GetlstPoint().begin();
	auto itrBack = prev(pArea->GetlstPoint().end());
	POINT playerPos = { pPlayer->GetPos().x, pPlayer->GetPos().y };

	int max_xpos, min_xpos; // ��
	int max_ypos, min_ypos;

	int odd_number;
	if (itrFront->x == next(itrFront, 1)->x)
		odd_number = 0;
	else
		odd_number = 1;
	for (auto& itr = itrFront; itr != itrBack; ++itr)
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

bool CDecisionMgr::DrawStartPossible(KEY key)
{
	Vec2 vResolution = CCore::GetInstance()->GetResolution();

	auto itrFront = pArea->GetlstPoint().begin();
	auto itrBack = prev(pArea->GetlstPoint().end());
	POINT playerPos = { pPlayer->GetPos().x, pPlayer->GetPos().y };
	int playerDirection = pPlayer->GetDirection();

	int max_xpos, min_xpos; // ��
	int max_ypos, min_ypos;

	int odd_number;
	if (itrPlayerPos == itrBack)
	{
		if (itrPlayerPos->x == itrFront->x)
		{
			odd_number = 0; // ����
		}
		else
		{
			odd_number = 1; //����
		}
	}
	else
	{
		if (itrPlayerPos->x == next(itrPlayerPos, 1)->x)
		{
			odd_number = 0;
		}
		else
		{
			odd_number = 1;
		}
	}

	int cnt = 0;
	for (auto itr = itrFront; itr != itrBack; ++itr)
	{
		switch(odd_number)
		{
		case 0: // x�� ������ (y������ ��)
		{
			if (next(itr, 1)->y > itr->y)	 { max_ypos = next(itr, 1)->y; min_ypos = itr->y; }
			else							 { min_ypos = next(itr, 1)->y; max_ypos = itr->y; }	

			switch (playerDirection)
			{
			case LEFT:
				if (itr->x < playerPos.x && min_ypos <= playerPos.y && playerPos.y < max_ypos)
					cnt++;
				break;
			case RIGHT:
				if (itr->x > playerPos.x && min_ypos <= playerPos.y && playerPos.y < max_ypos)
					cnt++;
				break;
			default:
				return false;
			}
		}
			break;
		case 1: // y�� ������ (x������ ��)
		{
			if (next(itr, 1)->x > itr->x)	 { max_xpos = next(itr, 1)->x; min_xpos = itr->x; }
			else							 { min_xpos = next(itr, 1)->x; max_xpos = itr->x; }	

			switch (playerDirection)
			{
			case UP:
				if (itr->y < playerPos.y && max_xpos <= playerPos.x && playerPos.x < max_xpos)
					cnt++;
				break;
			case DOWN:
				if (itr->y > playerPos.y && min_xpos <= playerPos.x && playerPos.x < max_xpos)
					cnt++;
				break;
			default:
				return false;
			}
		}
			break;
		default:
			break;
		}
	}

	
	switch (odd_number)
	{
	case 0: // x�� ������ (y������ ��)
	{
		if (itrFront->y > itrBack->y)	{ max_ypos = itrFront->y; min_ypos = itrBack->y; }
		else							{ min_ypos = itrFront->y; max_ypos = itrBack->y; }

		switch (playerDirection)
		{
		case LEFT:
			if (itrBack->x < playerPos.x && min_ypos <= playerPos.y && playerPos.y < max_ypos)
				cnt++;
			break;
		case RIGHT:
			if (itrBack->x > playerPos.x && min_ypos <= playerPos.y && playerPos.y < max_ypos)
				cnt++;
			break;
		default:
			return false;
		}
	}
	break;
	case 1: // y�� ������ (x������ ��)
	{
		if (itrFront->x > itrBack->x)	{ max_xpos = itrFront->x; min_xpos = itrBack->x; }
		else							{ min_xpos = itrFront->x; max_xpos = itrBack->x; }

		switch (playerDirection)
		{
		case UP:
			if (itrBack->y < playerPos.y && max_xpos <= playerPos.x && playerPos.x < max_xpos)
				cnt++;
			break;
		case DOWN:
			if (itrBack->y > playerPos.y && min_xpos <= playerPos.x && playerPos.x < max_xpos)
				cnt++;
			break;
		default:
			return false;
		}
	}
	break;
	default:
		break;
	}
	
	printf("%d", cnt);

	if (cnt % 2 == 0)
		return true; // ¦���� �׸��� ���� 
	else
		return false; // Ȧ���� ���η� ���°Ŵϱ� ���׸�
}

void CDecisionMgr::DrawEnd()
{
	POINT playerPos = { CDecisionMgr::GetInstance()->GetPlayer()->GetPos().x, CDecisionMgr::GetInstance()->GetPlayer()->GetPos().y };

	pArea->AddToNewPoint(playerPos);

	auto itrFront = pArea->GetlstPoint().begin();
	auto itrBack = pArea->GetlstPoint().end();

	// �ӽ� ���� ���ͷ����͵��� �迭 (���۰� ���� ����)
	vecSave.push_back(itrPlayerPos);
	if (itrPlayerPos == prev(itrBack,1))
	{
		vecSave.push_back(itrFront);
	}
	else
	{
		vecSave.push_back(next(itrPlayerPos, 1));
	}

	list<POINT>& refPoint = pArea->GetlstPoint();

	// ���� �����ϱ�
	vector<list<POINT>::iterator> vecTemp;
	for (auto itr = itrFront; itr != itrBack; ++itr)
	{
		for (int i = 0; i < vecSave.size(); i++)
		{
			if (vecSave[i] == itr)
			{
				vecTemp.push_back(itr);
				break;
			}
		}
	}

	// ó���� ����ġ�ϸ� ���θ��� �迭 �Ųٷ�(����Ʈ ���϶� �ݴ�� ���ͷ����� ����)
	bool check = false;
	if (vecSave[0] != vecTemp[0])
	{
		check = true;
		printf("�Ųٷ� ����");
	}

	auto tempFront = pArea->GetnewPoint().begin();
	auto tempBack = prev(pArea->GetnewPoint().end());

	int min = 1, max = 3; // ���ϴ� ���� 2���ϰ�� -> �� �Ѱ� / �� 3�� -> �� �ΰ� / �� 4�� -> �� ���� �̻�
	if (vecTemp.size() == 2) // �ߺ� �ΰ�(���ٿ��� �׸�)
	{
		if (vecTemp[0]->x == vecTemp[1]->x && tempFront->y - tempBack->y > 0) // y�࿡�� ��
		{
			printf("�Ųٷ� ����");
			check = true;
		}
		else if(vecTemp[0]->y == vecTemp[1]->y && tempFront->x - tempBack->x > 0) // x�࿡�� ��
		{
			printf("�Ųٷ� ����");
			check = true;
		}
		max = 1;
	}
	else if (vecTemp.size() == 3) // �ߺ� �ϳ�
	{
		max = 2;
	}
	
	// ó���� ����ġ�ϸ� ���θ��� �迭 �Ųٷ�
	if (check)
		pArea->GetnewPoint().reverse();
	vecSave = vecTemp;


	// ����Ʈ �̾���̱�
	auto itrNewFront = pArea->GetnewPoint().begin();
	auto itrNewBack = pArea->GetnewPoint().end();

    list<POINT> renewPoint;
	renewPoint.insert(renewPoint.end(), itrFront, vecSave[min]);
	renewPoint.insert(renewPoint.end(), itrNewFront, itrNewBack);
	renewPoint.insert(renewPoint.end(), vecSave[max], itrBack);

	// ����Ʈ �ߺ� ��ǥ ����
	for (auto itr = renewPoint.begin(); itr != prev(renewPoint.end(),1); ++itr)
	{
		if (itr->x == next(itr, 1)->x && itr->y == next(itr,1)->y)
		{
			printf("%d, %d ����\n", itr->x, itr->y);
			renewPoint.erase(itr);
			break;
		}
	}

	// �迭�� �ݿ�
	POINT* temp = new POINT[renewPoint.size()];
	POINT* save = pArea->GetptMyArea();
	std::copy(renewPoint.begin(), renewPoint.end(), save);

	// ���� ���� ����Ʈ�� ����
	pArea->GetlstPoint() = renewPoint;

	// �÷��̾� ���ͷ����� �ʱ�ȭ
	for (auto itr = itrFront; itr != itrBack; ++itr)
	{
		if (itr->x == playerPos.x && itr->y == playerPos.y)
		{
			itrPlayerPos = itr;
			break;
		}
	}

	// ������
	vecSave.clear();
	pPlayer->SetState(MOVE);
	pArea->ResetNewPoint();
	pArea->SetDraw(false);
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
