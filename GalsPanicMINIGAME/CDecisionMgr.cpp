#include "pch.h"
#include "func.h"
#include "CDecisionMgr.h"

#include "CPlayer.h"
#include "CArea.h"
#include "CMonster.h"

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
			if (itrFront->y > itrPlayerPos->y) { max_ypos = itrFront->y; min_ypos = itrPlayerPos->y; }
			else { min_ypos = itrFront->y; max_ypos = itrPlayerPos->y; }
			if (prev(itrPlayerPos, 1)->x > itrPlayerPos->x) { max_xpos = prev(itrPlayerPos, 1)->x; min_xpos = itrPlayerPos->x; }
			else { min_xpos = prev(itrPlayerPos, 1)->x; max_xpos = itrPlayerPos->x; }

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
			if (itrFront->x > itrPlayerPos->x) { max_xpos = itrFront->x; min_xpos = itrPlayerPos->x; }
			else { min_xpos = itrFront->x; max_xpos = itrPlayerPos->x; }
			if (prev(itrPlayerPos, 1)->y > itrPlayerPos->y) { max_ypos = prev(itrPlayerPos, 1)->y; min_ypos = itrPlayerPos->y; }
			else { min_ypos = prev(itrPlayerPos, 1)->y; max_ypos = itrPlayerPos->y; }

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
			if (next(itrPlayerPos, 1)->y > itrPlayerPos->y) { max_ypos = next(itrPlayerPos, 1)->y; min_ypos = itrPlayerPos->y; }
			else { min_ypos = next(itrPlayerPos, 1)->y; max_ypos = itrPlayerPos->y; }
			if (itrBack->x > itrPlayerPos->x) { max_xpos = itrBack->x; min_xpos = itrPlayerPos->x; }
			else { min_xpos = itrBack->x; max_xpos = itrPlayerPos->x; }

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
			if (next(itrPlayerPos, 1)->x > itrPlayerPos->x) { max_xpos = next(itrPlayerPos, 1)->x; min_xpos = itrPlayerPos->x; }
			else { min_xpos = next(itrPlayerPos, 1)->x; max_xpos = itrPlayerPos->x; }
			if (itrBack->y > itrPlayerPos->y) { max_ypos = itrBack->y; min_ypos = itrPlayerPos->y; }
			else { min_ypos = itrBack->y; max_ypos = itrPlayerPos->y; }

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
			if (next(itrPlayerPos, 1)->y > itrPlayerPos->y) { max_ypos = next(itrPlayerPos, 1)->y; min_ypos = itrPlayerPos->y; }
			else { min_ypos = next(itrPlayerPos, 1)->y; max_ypos = itrPlayerPos->y; }
			if (prev(itrPlayerPos, 1)->x > itrPlayerPos->x) { max_xpos = prev(itrPlayerPos, 1)->x; min_xpos = itrPlayerPos->x; }
			else { min_xpos = prev(itrPlayerPos, 1)->x; max_xpos = itrPlayerPos->x; }

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
			if (next(itrPlayerPos, 1)->x > itrPlayerPos->x) { max_xpos = next(itrPlayerPos, 1)->x; min_xpos = itrPlayerPos->x; }
			else { min_xpos = next(itrPlayerPos, 1)->x; max_xpos = itrPlayerPos->x; }
			if (prev(itrPlayerPos, 1)->y > itrPlayerPos->y) { max_ypos = prev(itrPlayerPos, 1)->y; min_ypos = itrPlayerPos->y; }
			else { min_ypos = prev(itrPlayerPos, 1)->y; max_ypos = itrPlayerPos->y; }

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
	int playerDirection = pPlayer->GetDirection();
	switch (playerDirection)
	{
	case LEFT:
		lastKEY = KEY::A;
		break;
	case UP:
		lastKEY = KEY::W;
		break;
	case RIGHT:
		lastKEY = KEY::D;
		break;
	case DOWN:
		lastKEY = KEY::S;
		break;
	default:
		break;
	}

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

	for (auto& itr = itrFront; itr != itrBack; ++itr)
	{
		if (itrFront->x == next(itrFront, 1)->x)
			odd_number = 0;
		else
			odd_number = 1;

		switch (odd_number)
		{
		case 0: // x�� ������ (y������ ��)
		{
			if (next(itr, 1)->y > itr->y) { max_ypos = next(itr, 1)->y; min_ypos = itr->y; }
			else { min_ypos = next(itr, 1)->y; max_ypos = itr->y; }
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
			if (next(itr, 1)->x > itr->x) { max_xpos = next(itr, 1)->x; min_xpos = itr->x; }
			else { min_xpos = next(itr, 1)->x; max_xpos = itr->x; }
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
		if (itrPlayerPos->x == playerPos.x && itrPlayerPos->y == playerPos.y)
		{
			odd_number = 2;
		}
		else if (itrPlayerPos->x == itrFront->x)
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
		if (itrPlayerPos->x == playerPos.x && itrPlayerPos->y == playerPos.y)
		{
			odd_number = 2;
		}
		else if (itrPlayerPos->x == next(itrPlayerPos, 1)->x)
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
		switch (odd_number)
		{
		case 0: // x�� ������ (y������ ��)
		{
			if (next(itr, 1)->y > itr->y)	{ max_ypos = next(itr, 1)->y; min_ypos = itr->y; }
			else							{ min_ypos = next(itr, 1)->y; max_ypos = itr->y; }

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
			if (next(itr, 1)->x > itr->x)	{ max_xpos = next(itr, 1)->x; min_xpos = itr->x; }
			else							{ min_xpos = next(itr, 1)->x; max_xpos = itr->x; }

			switch (playerDirection)
			{
			case UP:
				if (itr->y < playerPos.y && min_xpos <= playerPos.x && playerPos.x < max_xpos)
					cnt++;
				break;
			case DOWN:
				if (itr->y > playerPos.y && min_xpos <= playerPos.x && playerPos.x < max_xpos)
				{
					cnt++;
				}
				break;
			default:
				return false;
			}
		}
		break;
		case 2: // x, y �Ѵ� ������
		{
			if (next(itr, 1)->x > itr->x)	{ max_xpos = next(itr, 1)->x; min_xpos = itr->x; }
			else							{ min_xpos = next(itr, 1)->x; max_xpos = itr->x; }
			if (next(itr, 1)->y > itr->y)	{ max_ypos = next(itr, 1)->y; min_ypos = itr->y; }
			else							{ min_ypos = next(itr, 1)->y; max_ypos = itr->y; }

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
			case UP:
				if (itr->y < playerPos.y && min_xpos <= playerPos.x && playerPos.x < max_xpos)
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
			if (itrBack->y < playerPos.y && min_xpos <= playerPos.x && playerPos.x < max_xpos)
				cnt++;
			break;
		case DOWN:
			if (itrBack->y > playerPos.y && min_xpos <= playerPos.x && playerPos.x < max_xpos)
			{
				cnt++;
			}
			break;
		default:
			return false;
		}
	}
	break;
	case 2: // x, y �Ѵ� ������
	{
		if (itrFront->x > itrBack->x)	{ max_xpos = itrFront->x; min_xpos = itrBack->x; }
		else							{ min_xpos = itrFront->x; max_xpos = itrBack->x; }
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
		case UP:
			if (itrBack->y < playerPos.y && min_xpos <= playerPos.x && playerPos.x < max_xpos)
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
	}

	printf("�ߺ� �� : %d\n", cnt);

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
	if (itrPlayerPos == prev(itrBack, 1))
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
				printf("vecSave[%d] = %d, %d\n", i, vecSave[i]->x, vecSave[i]->y);
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
		printf("�Ųٷ� ����\n");
	}

	auto tempFront = pArea->GetnewPoint().begin();
	auto tempBack = prev(pArea->GetnewPoint().end());

	int min = 1, max = 3; // ���ϴ� ���� 2���ϰ�� -> �� �Ѱ� / �� 3�� -> �� �ΰ� / �� 4�� -> �� ���� �̻�
	if (vecTemp.size() == 2) // �ߺ� �ΰ�(���ٿ��� �׸�)
	{
		if (vecTemp[0]->x == vecTemp[1]->x) // y�࿡�� ��
		{
			if ((vecSave[2]->y < vecSave[3]->y && tempFront->y > tempBack->y)
				|| (vecSave[2]->y > vecSave[3]->y && tempFront->y < tempBack->y))
			{
				printf("�Ųٷ� ����\n");
				check = true;
			}
		}
		else if (vecTemp[0]->y == vecTemp[1]->y)
		{
			if((vecSave[2]->x < vecSave[3]->x && tempFront->x > tempBack->x)
				|| (vecSave[2]->x > vecSave[3]->x && tempFront->x < tempBack->x)) // x�࿡�� ��
			{
				printf("�Ųٷ� ����\n");
				check = true;
			}
		}
		max = 1;
	}
	else if (vecTemp.size() == 3) // �ߺ� �ϳ�
	{
		max = 2;
	}
	printf("\n");

	for (int i = 0; i < vecTemp.size(); i++)
	{
		printf("vecTemp[%d] = %d, %d\n", i, vecTemp[i]->x, vecTemp[i]->y);
	}
	printf("\n");

	auto itrtFront = pArea->GetnewPoint().begin();
	auto itrtBack = pArea->GetnewPoint().end();
	for (auto itr = itrtFront; itr != itrtBack; ++itr)
	{
		printf("%d, %d\n", itr->x, itr->y);
	}
	printf("\n");

	// ó���� ����ġ�ϸ� ���θ��� �迭 �Ųٷ�
	if (check)
	{
		pArea->GetnewPoint().reverse();
		vecSave = vecTemp;
	}
	else
	{
		vecSave = vecTemp;
	}


	for (int i = 0; i < vecSave.size(); i++)
	{
		printf("vecSave[%d] = %d, %d\n", i, vecSave[i]->x, vecSave[i]->y);
	}
	printf("max = %d\n", max);


	// ����Ʈ �̾���̱�
	auto itrNewFront = pArea->GetnewPoint().begin();
	auto itrNewBack = pArea->GetnewPoint().end();

	list<POINT> renewPoint;
	renewPoint.insert(renewPoint.end(), itrFront, vecSave[min]);
	renewPoint.insert(renewPoint.end(), itrNewFront, itrNewBack);
	renewPoint.insert(renewPoint.end(), vecSave[max], itrBack);

	auto itrtnFront = renewPoint.begin();
	auto itrtnBack = renewPoint.end();
	for (auto itr = itrtnFront; itr != itrtnBack; ++itr)
	{
		printf("%d, %d\n", itr->x, itr->y);
	}
	printf("\n");


	// ����Ʈ �ߺ� ��ǥ ����
	while (1)
	{
		int overlaped = 0;
		list<POINT>::iterator itrOverlap;
		list<POINT>::iterator itrPrev;
		list<POINT>::iterator itrNext;
		for (auto itr = next(renewPoint.begin(),1); itr != prev(renewPoint.end(), 1); ++itr)
		{
			itrPrev = prev(itr, 1);
			itrNext = next(itr, 1);

			if ((itr->x == itrNext->x && itr->y == itrNext->y)
				|| itr->x == itrPrev->x && itr->y == itrPrev->y)
			{
				printf("%d, %d 1������\n", itr->x, itr->y);
				itrOverlap = itrNext;
				renewPoint.erase(itr);
				overlaped = 1;
				break;
			}
			else if (prev(itr, 1)->x == next(itr, 1)->x
				|| prev(itr, 1)->y == next(itr, 1)->y)
			{
				printf("%d, %d 1������\n", itr->x, itr->y);
				itrOverlap = itrNext;
				renewPoint.erase(itr);
				overlaped = 2;
				break;
			}
		}
		if (overlaped == 1)
		{
			printf("%d, %d 2������\n", itrOverlap->x, itrOverlap->y);
			renewPoint.erase(itrOverlap);
		}
		else if (overlaped == 2)
		{
			continue;
		}
		else // �ߺ���ǥ ������ Ż��
		{
			break;
		}
	}
	printf("\n");

	auto itrtnFront2 = renewPoint.begin();
	auto itrtnBack2 = renewPoint.end();
	for (auto itr = itrtnFront2; itr != itrtnBack2; ++itr)
	{
		printf("%d, %d\n", itr->x, itr->y);
	}
	printf("\n");

	// �迭�� �ݿ�
	POINT* save = pArea->GetptMyArea();
	std::copy(renewPoint.begin(), renewPoint.end(), save);

	// ���� ���� ����Ʈ�� ����
	pArea->GetlstPoint() = renewPoint;

	// �÷��̾� ���ͷ����� �ʱ�ȭ
	bool itrPlayerInit = false;
	for (auto itr = itrFront; itr != itrBack; ++itr)
	{
		if (itr->x == playerPos.x && itr->y == playerPos.y)
		{
			itrPlayerPos = itr;
			itrPlayerInit = true;
			break;
		}
	}

	if(itrPlayerInit == false)
	{ // �ݶ��̴�
		auto itrFront = pArea->GetlstPoint().begin();
		auto itrBack = prev(pArea->GetlstPoint().end());
		POINT playerPos = { pPlayer->GetPos().x, pPlayer->GetPos().y };

		int max_xpos, min_xpos; // ��
		int max_ypos, min_ypos;

		int odd_number;

		for (auto itr = itrFront; itr != itrBack; ++itr)
		{
			if (itrFront->x == next(itrFront, 1)->x)
				odd_number = 0;
			else
				odd_number = 1;

			switch (odd_number)
			{
			case 0: // x�� ������ (y������ ��)
			{
				if (next(itr, 1)->y > itr->y) { max_ypos = next(itr, 1)->y; min_ypos = itr->y; }
				else { min_ypos = next(itr, 1)->y; max_ypos = itr->y; }
				if (itr->x == playerPos.x && min_ypos <= playerPos.y && playerPos.y <= max_ypos)
				{
					itrPlayerPos = itr;
					itrPlayerInit = true;
					break;
				}
				odd_number = 1;
			}
			break;
			case 1: // y�� ������ (x������ ��)
			{
				if (next(itr, 1)->x > itr->x) { max_xpos = next(itr, 1)->x; min_xpos = itr->x; }
				else { min_xpos = next(itr, 1)->x; max_xpos = itr->x; }
				if (itr->y == playerPos.y && min_xpos <= playerPos.x && playerPos.x <= max_xpos)
				{
					itrPlayerPos = itr;
					itrPlayerInit = true;
					break;
				}
				odd_number = 0;
			}
			break;
			default:
				break;
			}
		}
	}
	if (itrPlayerInit == false)
	{
		itrPlayerPos = prev(pArea->GetlstPoint().end());
	}

	// ������
	vecSave.clear();
	pPlayer->SetState(MOVE);
	pArea->ResetNewPoint();
	pArea->SetDraw(false);
}

void CDecisionMgr::DrawCollideDead()
{
	if (pArea->GetnewPoint().size() < 2)
		return;

	auto itrFront = pArea->GetnewPoint().begin();
	auto itrBack = prev(pArea->GetnewPoint().end(), 2);
	POINT playerPos = { pPlayer->GetPos().x, pPlayer->GetPos().y };

	int max_xpos, min_xpos; // ��
	int max_ypos, min_ypos;
	int odd_number;

	// �浹 üũ
	bool dead = pPlayer->GetDead();
	for (auto& itr = itrFront; itr != itrBack; ++itr)
	{
		if (itrFront->x == next(itrFront, 1)->x)
			odd_number = 0;
		else
			odd_number = 1;

		switch (odd_number)
		{
		case 0: // x�� ������ (y������ ��)
		{
			if (next(itr, 1)->y > itr->y) { max_ypos = next(itr, 1)->y; min_ypos = itr->y; }
			else { min_ypos = next(itr, 1)->y; max_ypos = itr->y; }
			if (itr->x == playerPos.x && min_ypos <= playerPos.y && playerPos.y <= max_ypos)
			{
				itrPlayerPos = itr;
				printf("x : %d, y : %d ~ x : %d, y : %d���� ����\n", itr->x, itr->y, next(itr,1)->x, next(itr,1)->y);
				dead = true;
				break;
			}
			odd_number = 1;
		}
		break;
		case 1: // y�� ������ (x������ ��)
		{
			if (next(itr, 1)->x > itr->x) { max_xpos = next(itr, 1)->x; min_xpos = itr->x; }
			else { min_xpos = next(itr, 1)->x; max_xpos = itr->x; }
			if (itr->y == playerPos.y && min_xpos <= playerPos.x && playerPos.x <= max_xpos)
			{
				itrPlayerPos = itr;
				printf("x : %d, y : %d ~ x : %d, y : %d���� ����\n", itr->x, itr->y, next(itr, 1)->x, next(itr, 1)->y);
				dead = true;
				break;
			}
			odd_number = 0;
		}
		break;
		default:
			break;
		}
	}

	if(dead == true && pPlayer->GetState() == DRAW)
	{
		auto itrReverse = prev(pArea->GetnewPoint().end(), 1);
		itrPlayerPos = itrReverse;
		pPlayer->SetState(DEAD);
		pPlayer->GetDamaged();

		for (int i = 0; i < (int)KEY::LAST; i++)
		{
			CKeyMgr::GetInstance()->SetKeyAvailability((KEY)i, false);
		}
		return;
	}
}

int CDecisionMgr::MonsterCollide(CMonster* pMonster)
{
	auto itrFront = pArea->GetlstPoint().begin();
	auto itrBack = prev(pArea->GetlstPoint().end());
	Vec2 vPos = pMonster->GetPos();
	Vec2 vScale = pMonster->GetScale();
	POINT monsterPos = { vPos.x, vPos.y };
	Vec2 direction = pMonster->GetDirection();
	int speed = pMonster->GetSpeed();

	int max_xpos, min_xpos; // ��
	int max_ypos, min_ypos;

	int odd_number;

	if (direction.x <= 0 || direction.y >= 0)
	{
		for (auto& itr = itrFront; itr != itrBack; ++itr)
		{
			if (itrFront->x == next(itrFront, 1)->x)
				odd_number = 0;
			else
				odd_number = 1;

			switch (odd_number)
			{
			case 0: // x�� ������ (y������ ��)
			{
				if (next(itr, 1)->y > itr->y) { max_ypos = next(itr, 1)->y; min_ypos = itr->y; }
				else { min_ypos = next(itr, 1)->y; max_ypos = itr->y; }

				if (direction.x >= 0)
				{
					if (min_ypos <= monsterPos.y && monsterPos.y <= max_ypos && itr->x < monsterPos.x + vScale.x / 2)
					{
						return 0;
					}
				}
				else
				{
					if (min_ypos <= monsterPos.y && monsterPos.y <= max_ypos && itr->x > monsterPos.x - vScale.x / 2)
					{
						return 0;
					}
				}
				odd_number = 1;
			}
			break;
			case 1: // y�� ������ (x������ ��)
			{
				if (next(itr, 1)->x > itr->x) { max_xpos = next(itr, 1)->x; min_xpos = itr->x; }
				else { min_xpos = next(itr, 1)->x; max_xpos = itr->x; }

				if (direction.y >= 0)
				{
					if (itr->y < monsterPos.y + vScale.y / 2 && min_xpos <= monsterPos.x && monsterPos.x <= max_xpos)
					{
						return 1;
					}
				}
				else
				{
					if (itr->y > monsterPos.y - vScale.y / 2 && min_xpos <= monsterPos.x && monsterPos.x <= max_xpos)
					{
						return 1;
					}
				}
				odd_number = 0;
			}
			break;
			default:
				break;
			}
		}
	}

	return -1;
}

bool CDecisionMgr::MonsterWallCheck(CMonster* pMonster, int left_right)
{
	auto itrFront = pArea->GetlstPoint().begin();
	auto itrBack = prev(pArea->GetlstPoint().end());
	Vec2 vPos = pMonster->GetPos();
	Vec2 vScale = pMonster->GetScale();
	POINT monsterPos = { vPos.x, vPos.y };
	Vec2 direction = pMonster->GetDirection();
	int speed = pMonster->GetSpeed();

	int max_xpos, min_xpos; // ��
	int max_ypos, min_ypos;

	int odd_number = 0;
	int cnt = 0;
	for (auto itr = itrFront; itr != itrBack; ++itr)
	{
		if (itr->x == next(itr, 1)->x)
			odd_number = 0;
		else
			odd_number = 1;

		switch (odd_number)
		{
		case 0: // x�� ������ (y������ ��)
		{
			if (left_right == 1) continue;
			if (next(itr, 1)->y > itr->y) { max_ypos = next(itr, 1)->y; min_ypos = itr->y; }
			else { min_ypos = next(itr, 1)->y; max_ypos = itr->y; }

			if (direction.x >= 0)
			{
				if (itr->x > monsterPos.x && min_ypos <= monsterPos.y && monsterPos.y < max_ypos)
					cnt++;
			}
			else
			{
				if (itr->x < monsterPos.x && min_ypos <= monsterPos.y && monsterPos.y < max_ypos)
					cnt++;
			}
		}
		break;
		case 1: // y�� ������ (x������ ��)
		{
			if (left_right == 0) continue;
			if (next(itr, 1)->x > itr->x) { max_xpos = next(itr, 1)->x; min_xpos = itr->x; }
			else { min_xpos = next(itr, 1)->x; max_xpos = itr->x; }

			if (direction.y >= 0)
			{
				if (itr->y > monsterPos.y && min_xpos <= monsterPos.x && monsterPos.x < max_xpos)
					cnt++;
			}
			else
			{
				if (itr->y < monsterPos.y && min_xpos <= monsterPos.x && monsterPos.x < max_xpos)
					cnt++;
			}
		}
		break;
		}
	}

	odd_number = odd_number % 2 == 0 ? 1 : 0;
	switch (odd_number)
	{
	case 0: // x�� ������ (y������ ��)
	{
		if (left_right == 1) break;
		if (itrFront->y > itrBack->y) { max_ypos = itrFront->y; min_ypos = itrBack->y; }
		else { min_ypos = itrFront->y; max_ypos = itrBack->y; }

		if (direction.x >= 0)
		{
			if (itrBack->x > monsterPos.x && min_ypos <= monsterPos.y && monsterPos.y < max_ypos)
				cnt++;
		}
		else
		{
			if (itrBack->x < monsterPos.x && min_ypos <= monsterPos.y && monsterPos.y < max_ypos)
				cnt++;
		}
	}
	break;
	case 1: // y�� ������ (x������ ��)
	{
		if (left_right == 0) break;
		if (itrFront->x > itrBack->x) { max_xpos = itrFront->x; min_xpos = itrBack->x; }
		else { min_xpos = itrFront->x; max_xpos = itrBack->x; }

		if (direction.y >= 0)
		{
			if (itrBack->y > monsterPos.y && min_xpos <= monsterPos.x && monsterPos.x < max_xpos)
				cnt++;
		}
		else
		{
			if (itrBack->y < monsterPos.y && min_xpos <= monsterPos.x && monsterPos.x < max_xpos)
				cnt++;
		}
	}
	break;
	}
	if (cnt == 0) return false;
	if (cnt % 2 == 0)
		return true;
	else
		return false;
}

void CDecisionMgr::Init()
{
	vecSave.clear();
	vecMonsters.clear();
}

void CDecisionMgr::Init(CPlayer* player, CArea* area, vector<CMonster*> monsters)
{
	pPlayer = player;
	pArea = area;
	vecMonsters = monsters;
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
		DrawCollideDead();
		DrawUpdate();
		break;
	case DEAD:
		DeadUpdate();
		break;
	default:
		break;
	}

	MonsterUpdate();
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
	int playerDirection = pPlayer->GetDirection();

	if (CKeyMgr::GetInstance()->GetKeyState(KEY::A) == KEY_STATE::TAP
		&& CKeyMgr::GetInstance()->GetKeyAvailability(KEY::A))
	{
		if (playerDirection != LEFT)
		{
			pArea->AddToNewPoint(PlayerPos);
			printf("�� �߰�\n");
		}
		
		CKeyMgr::GetInstance()->SetKeyAvailability(KEY::D, false);
		CKeyMgr::GetInstance()->SetKeyAvailability(KEY::A, true);
		CKeyMgr::GetInstance()->SetKeyAvailability(KEY::W, false);
		CKeyMgr::GetInstance()->SetKeyAvailability(KEY::S, false);
		check = LEFT;
		return;
	}
	else if (CKeyMgr::GetInstance()->GetKeyState(KEY::A) == KEY_STATE::AWAY
		&& CKeyMgr::GetInstance()->GetKeyAvailability(KEY::A))
	{
		CKeyMgr::GetInstance()->SetKeyAvailability(KEY::D, false);
		CKeyMgr::GetInstance()->SetKeyAvailability(KEY::A, true);
		CKeyMgr::GetInstance()->SetKeyAvailability(KEY::W, true);
		CKeyMgr::GetInstance()->SetKeyAvailability(KEY::S, true);
		check = NONE;
		return;
	}

	if (CKeyMgr::GetInstance()->GetKeyState(KEY::W) == KEY_STATE::TAP
		&& CKeyMgr::GetInstance()->GetKeyAvailability(KEY::W))
	{
		if (playerDirection != UP)
		{
			pArea->AddToNewPoint(PlayerPos);
			printf("�� �߰�\n");
		}
		
		CKeyMgr::GetInstance()->SetKeyAvailability(KEY::S, false);
		CKeyMgr::GetInstance()->SetKeyAvailability(KEY::A, false);
		CKeyMgr::GetInstance()->SetKeyAvailability(KEY::W, true);
		CKeyMgr::GetInstance()->SetKeyAvailability(KEY::D, false);
		check = UP;
		return;
	}
	else if (CKeyMgr::GetInstance()->GetKeyState(KEY::W) == KEY_STATE::AWAY
		&& CKeyMgr::GetInstance()->GetKeyAvailability(KEY::W))
	{
		CKeyMgr::GetInstance()->SetKeyAvailability(KEY::S, false);
		CKeyMgr::GetInstance()->SetKeyAvailability(KEY::A, true);
		CKeyMgr::GetInstance()->SetKeyAvailability(KEY::W, true);
		CKeyMgr::GetInstance()->SetKeyAvailability(KEY::D, true);
		check = NONE;
		return;
	}


	if (CKeyMgr::GetInstance()->GetKeyState(KEY::D) == KEY_STATE::TAP
		&& CKeyMgr::GetInstance()->GetKeyAvailability(KEY::D))
	{
		if (playerDirection != RIGHT)
		{
			pArea->AddToNewPoint(PlayerPos);
			printf("�� �߰�\n");
		}

		CKeyMgr::GetInstance()->SetKeyAvailability(KEY::A, false);
		CKeyMgr::GetInstance()->SetKeyAvailability(KEY::W, false);
		CKeyMgr::GetInstance()->SetKeyAvailability(KEY::D, true);
		CKeyMgr::GetInstance()->SetKeyAvailability(KEY::S, false);
		check = RIGHT;
		return;
	}
	else if (CKeyMgr::GetInstance()->GetKeyState(KEY::D) == KEY_STATE::AWAY
		&& CKeyMgr::GetInstance()->GetKeyAvailability(KEY::D))
	{
		CKeyMgr::GetInstance()->SetKeyAvailability(KEY::A, false);
		CKeyMgr::GetInstance()->SetKeyAvailability(KEY::W, true);
		CKeyMgr::GetInstance()->SetKeyAvailability(KEY::D, true);
		CKeyMgr::GetInstance()->SetKeyAvailability(KEY::S, true);
		check = NONE;
		return;
	}

	if (CKeyMgr::GetInstance()->GetKeyState(KEY::S) == KEY_STATE::TAP
		&& CKeyMgr::GetInstance()->GetKeyAvailability(KEY::S))
	{
		if (playerDirection != DOWN)
		{
			pArea->AddToNewPoint(PlayerPos);
			printf("�� �߰�\n");
		}

		CKeyMgr::GetInstance()->SetKeyAvailability(KEY::W, false);
		CKeyMgr::GetInstance()->SetKeyAvailability(KEY::A, false);
		CKeyMgr::GetInstance()->SetKeyAvailability(KEY::S, true);
		CKeyMgr::GetInstance()->SetKeyAvailability(KEY::D, false);
		check = DOWN;
		return;
	}
	else if (CKeyMgr::GetInstance()->GetKeyState(KEY::S) == KEY_STATE::AWAY
		&& CKeyMgr::GetInstance()->GetKeyAvailability(KEY::S))
	{
		CKeyMgr::GetInstance()->SetKeyAvailability(KEY::W, false);
		CKeyMgr::GetInstance()->SetKeyAvailability(KEY::A, true);
		CKeyMgr::GetInstance()->SetKeyAvailability(KEY::S, true);
		CKeyMgr::GetInstance()->SetKeyAvailability(KEY::D, true);
		check = NONE;
		return;
	}

	if (DrawCollide() == true) // ������ ����
		DrawEnd();
}

void CDecisionMgr::DeadUpdate()
{
	POINT playerPos = { pPlayer->GetPos().x, pPlayer->GetPos().y };
	int playerSpeed = pPlayer->GetSpeed();
	auto& newPoint = pArea->GetnewPoint();

	auto &itrReverse = itrPlayerPos;

	bool erase = false;
	if(newPoint.size() > 0)
	{
		if (playerPos.x == itrPlayerPos->x && playerPos.y == itrPlayerPos->y)
		{
			if (itrPlayerPos != newPoint.begin())
			{
				itrPlayerPos = prev(itrReverse, 1);
				newPoint.pop_back();
			}
			else
			{
				erase = true;
			}
		}
		else if (playerPos.x == itrReverse->x) // y������ �̵�
		{
			pPlayer->SetPos(Vec2((int)playerPos.x,
				playerPos.y + (int)((itrReverse->y - playerPos.y) / abs((itrReverse->y - playerPos.y))) * playerSpeed));
		}
		else // x������ �̵�
		{
			pPlayer->SetPos(Vec2(playerPos.x + (int)((itrReverse->x - playerPos.x) / abs((itrReverse->x - playerPos.x))) * playerSpeed
				, (int)playerPos.y));
		}
	}
	if (erase == true)
	{
		printf("asdf\n");

		auto itrFront = pArea->GetlstPoint().begin();
		auto itrBack = pArea->GetlstPoint().end();
		// �ٽ� ���� ����
		for (int i = 0; i < (int)KEY::LAST; i++)
		{
			CKeyMgr::GetInstance()->SetKeyAvailability((KEY)i, true);
		}

		bool itrPlayerInit = false;
		for (auto &itr = itrFront; itr != itrBack; ++itr)
		{
			if (itr->x == playerPos.x && itr->y == playerPos.y)
			{
				itrPlayerPos = itr;
				itrPlayerInit = true;
				break;
			}
		}

		if (itrPlayerInit == false)
		{ // �ݶ��̴�
			auto itrFront = pArea->GetlstPoint().begin();
			auto itrBack = prev(pArea->GetlstPoint().end());
			POINT playerPos = { pPlayer->GetPos().x, pPlayer->GetPos().y };

			int max_xpos, min_xpos; // ��
			int max_ypos, min_ypos;

			int odd_number;

			for (auto &itr = itrFront; itr != itrBack; ++itr)
			{
				if (itrFront->x == next(itrFront, 1)->x)
					odd_number = 0;
				else
					odd_number = 1;

				switch (odd_number)
				{
				case 0: // x�� ������ (y������ ��)
				{
					if (next(itr, 1)->y > itr->y) { max_ypos = next(itr, 1)->y; min_ypos = itr->y; }
					else { min_ypos = next(itr, 1)->y; max_ypos = itr->y; }
					if (itr->x == playerPos.x && min_ypos <= playerPos.y && playerPos.y <= max_ypos)
					{
						itrPlayerPos = itr;
						itrPlayerInit = true;
						break;
					}
					odd_number = 1;
				}
				break;
				case 1: // y�� ������ (x������ ��)
				{
					if (next(itr, 1)->x > itr->x) { max_xpos = next(itr, 1)->x; min_xpos = itr->x; }
					else { min_xpos = next(itr, 1)->x; max_xpos = itr->x; }
					if (itr->y == playerPos.y && min_xpos <= playerPos.x && playerPos.x <= max_xpos)
					{
						itrPlayerPos = itr;
						itrPlayerInit = true;
						break;
					}
					odd_number = 0;
				}
				break;
				default:
					break;
				}
			}
		}
		if (itrPlayerInit == false)
		{
			itrPlayerPos = prev(pArea->GetlstPoint().end());
		}

		vecSave.clear();
		pPlayer->SetState(MOVE);
		pArea->ResetNewPoint();
		pArea->SetDraw(false);
	}
}

void CDecisionMgr::MonsterUpdate()
{
	for (auto& monster : vecMonsters)
	{
		int direction = MonsterCollide(monster);
		Vec2 vDirection = monster->GetDirection();
		Vec2 vPos = monster->GetPos();
		Vec2 vScale = monster->GetScale();
		if (direction == 0)
		{
			if(MonsterWallCheck(monster, direction))
			{
				vDirection.x *= -1;
				monster->SetDirection(vDirection);
				if (vDirection.x >= 0) vPos.x += vScale.x;
				else vPos.x -= vScale.x;
				monster->SetPos(vPos);
			}
		}
		else if (direction == 1)
		{
			if (MonsterWallCheck(monster, direction))
			{
				vDirection.y *= -1;
				monster->SetDirection(vDirection);
				if (vDirection.y >= 0) vPos.y += vScale.y;
				else vPos.y -= vScale.y;
				monster->SetPos(vPos);
			}
		}
	}
}

CDecisionMgr::CDecisionMgr()
	: pPlayer(nullptr)
	, pArea(nullptr)
{
}

CDecisionMgr::~CDecisionMgr()
{
}