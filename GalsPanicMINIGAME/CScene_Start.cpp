#include "pch.h"
#include "CScene_Start.h"

#include "CObject.h"
#include "CPlayer.h"
#include "CArea.h"
#include "CText.h"
#include "CTexture.h"
#include "CMonster.h"
#include "CHeart.h"
#include "CNumber.h"
#include "CPanel.h"

#include "CCore.h"
#include "CPathMgr.h"
#include "CDecisionMgr.h"
#include "CCollisionMgr.h"
#include "CKeyMgr.h"

void CScene_Start::Update()
{
	CScene::Update();

	if (KEY_TAP(KEY::ENTER))
	{
		ChangeScene(SCENE_TYPE::ENDING);
	}
}

void CScene_Start::Enter()
{
	// 영역 크기
	CPanel* pPanel = new CPanel(L"texture\\area.png");
	pPanel->SetPos(Vec2(1150.f, 20.f));
	CreateObj(pPanel, GROUP_TYPE::DEFAULT);

	CNumber* pNumber = new CNumber(0, Vec2(1155.f, 80.0f), 1.0f);
	CreateObj(pNumber, GROUP_TYPE::DEFAULT);

	CPanel* pPercent = new CPanel(L"texture\\percent.png");
	pPercent->SetPos(Vec2(1190.f, 70.f));
	CreateObj(pPercent, GROUP_TYPE::DEFAULT);

	// 영역 추가
	CArea* pArea = new CArea(pNumber);
	AddObject(pArea, GROUP_TYPE::DEFAULT);

	// 하트 추가
	CHeart* pHeart = new CHeart(3);
	pHeart->SetPos(Vec2(50.f, 50.f));
	AddObject(pHeart, GROUP_TYPE::DEFAULT);

	// Player 추가
	CPlayer* pPlayer = new CPlayer(pHeart);
	pPlayer->SetPos(Vec2(40.f, 728.f));
	pPlayer->SetScale(Vec2(40.f, 40.f));
	pPlayer->SetType(GROUP_TYPE::PLAYER);
	AddObject(pPlayer, GROUP_TYPE::PLAYER);

	// 몬스터
	vector<CMonster*> monsters;
	{
		CMonster* pMonster = new CMonster;
		pMonster->SetPos(Vec2(200.f, 300.f));
		pMonster->SetScale(Vec2(40.f, 40.f));
		pMonster->SetType(GROUP_TYPE::MONSTER);
		AddObject(pMonster, GROUP_TYPE::MONSTER);
		monsters.push_back(pMonster);
	}
	{
		CMonster* pMonster = new CMonster;
		pMonster->SetPos(Vec2(400.f, 300.f));
		pMonster->SetScale(Vec2(40.f, 40.f));
		pMonster->SetType(GROUP_TYPE::MONSTER);
		AddObject(pMonster, GROUP_TYPE::MONSTER);
		monsters.push_back(pMonster);
	}
	{
		CMonster* pMonster = new CMonster;
		pMonster->SetPos(Vec2(600.f, 300.f));
		pMonster->SetScale(Vec2(40.f, 40.f));
		pMonster->SetType(GROUP_TYPE::MONSTER);
		AddObject(pMonster, GROUP_TYPE::MONSTER);
		monsters.push_back(pMonster);
	}
	{
		CMonster* pMonster = new CMonster;
		pMonster->SetPos(Vec2(800.f, 500.f));
		pMonster->SetScale(Vec2(40.f, 40.f));
		pMonster->SetType(GROUP_TYPE::MONSTER);
		AddObject(pMonster, GROUP_TYPE::MONSTER);
		monsters.push_back(pMonster);
	}
	{
		CMonster* pMonster = new CMonster;
		pMonster->SetPos(Vec2(1000.f, 500.f));
		pMonster->SetScale(Vec2(40.f, 40.f));
		pMonster->SetType(GROUP_TYPE::MONSTER);
		AddObject(pMonster, GROUP_TYPE::MONSTER);
		monsters.push_back(pMonster);
	}

	//// 텍스트 추가
	//CText* pText1 = new CText;
	//pText1->SetPos(Vec2(100.f, 100.f));
	//pText1->SetTarget(pPlayer);
	//pText1->SetType(PRINT_TYPE::POS);
	//AddObject(pText1, GROUP_TYPE::DEFAULT);

	//CText* pText2 = new CText;
	//pText2->SetPos(Vec2(100.f, 120.f));
	//pText2->SetTarget(pPlayer);
	//pText2->SetType(PRINT_TYPE::POS_POINT);
	//AddObject(pText2, GROUP_TYPE::DEFAULT);

	//CText* pText3 = new CText;
	//pText3->SetPos(Vec2(100.f, 140.f));
	//pText3->SetTarget(pPlayer);
	//pText3->SetType(PRINT_TYPE::DIRECTION);
	//AddObject(pText3, GROUP_TYPE::DEFAULT);

	//CText* pText4 = new CText;
	//pText4->SetPos(Vec2(100.f, 160.f));
	//pText4->SetTarget(pPlayer);
	//pText4->SetType(PRINT_TYPE::STATE);
	//AddObject(pText4, GROUP_TYPE::DEFAULT);

	//CText* pText5 = new CText;
	//pText5->SetPos(Vec2(100.f, 180.f));
	//pText5->SetTarget(pPlayer);
	//pText5->SetType(PRINT_TYPE::AREA);
	//AddObject(pText5, GROUP_TYPE::DEFAULT);

	CDecisionMgr::GetInstance()->Init(pPlayer, pArea, monsters);

	CCollisionMgr::GetInstance()->CheckGroup(GROUP_TYPE::PLAYER, GROUP_TYPE::MONSTER);
	CCollisionMgr::GetInstance()->CheckGroup(GROUP_TYPE::MONSTER, GROUP_TYPE::MONSTER);
}

void CScene_Start::Exit()
{
	DeleteAll();
	CCollisionMgr::GetInstance()->Reset();
}

CScene_Start::CScene_Start()
{
}

CScene_Start::~CScene_Start()
{
}
