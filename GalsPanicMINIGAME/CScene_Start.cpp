#include "pch.h"
#include "CScene_Start.h"

#include "CObject.h"
#include "CPlayer.h"
#include "CArea.h"
#include "CText.h"

#include "CCore.h"
#include "CDecisionMgr.h"

void CScene_Start::Enter()
{
	// 영역 추가
	CArea* pArea = new CArea;
	AddObject(pArea, GROUP_TYPE::DEFAULT);

	// Player 추가
	CPlayer* pPlayer = new CPlayer;
	pPlayer->SetPos(Vec2(40.f, 728.f));
	pPlayer->SetScale(Vec2(40.f, 40.f));
	AddObject(pPlayer, GROUP_TYPE::PLAYER);

	// 텍스트 추가
	CText* pText1 = new CText;
	pText1->SetPos(Vec2(100.f, 100.f));
	pText1->SetTarget(pPlayer);
	pText1->SetType(PRINT_TYPE::POS);
	AddObject(pText1, GROUP_TYPE::DEFAULT);

	CText* pText2 = new CText;
	pText2->SetPos(Vec2(100.f, 120.f));
	pText2->SetTarget(pPlayer);
	pText2->SetType(PRINT_TYPE::DIRECTION);
	AddObject(pText2, GROUP_TYPE::DEFAULT);

	CText* pText3 = new CText;
	pText3->SetPos(Vec2(100.f, 140.f));
	pText3->SetTarget(pPlayer);
	pText3->SetType(PRINT_TYPE::STATE);
	AddObject(pText3, GROUP_TYPE::DEFAULT);

	CDecisionMgr::GetInstance()->Init(pPlayer, pArea);
}

void CScene_Start::Exit()
{
}

CScene_Start::CScene_Start()
{
}

CScene_Start::~CScene_Start()
{
}
