#include "pch.h"
#include "CScene_Ending.h"

#include "CCore.h"
#include "CPanel.h"
#include "CNumber.h"

#include "CKeyMgr.h"
#include "CDecisionMgr.h"

void CScene_Ending::Update()
{
	CScene::Update();

	if (KEY_TAP(KEY::SPACE))
	{
		ChangeScene(SCENE_TYPE::START);
	}
}

void CScene_Ending::Enter()
{
	int score = CDecisionMgr::GetInstance()->GetTimeScore();
	printf("\n score :: %d\n", score);
	CKeyMgr::GetInstance()->Init();
	CDecisionMgr::GetInstance()->Init();

	Vec2 vResolution = CCore::GetInstance()->GetResolution();

	// 패널
	{
		CPanel* pBackground = new CPanel(L"texture\\StartBackground.png");
		CreateObj(pBackground, GROUP_TYPE::DEFAULT);
	}
	{
		CPanel* pButton = new CPanel(L"texture\\Start.png");
		pButton->SetPos(Vec2(350.f, 550.f));
		CreateObj(pButton, GROUP_TYPE::DEFAULT);
	}
	// 점수 표기
	if (score == 0)
	{
		{
			CPanel* pDefeat = new CPanel(L"texture\\DEFEAT.png");
			pDefeat->SetPos(Vec2(350.f, 120.f));
			CreateObj(pDefeat, GROUP_TYPE::DEFAULT);
		}
	}
	else
	{
		{
			CPanel* pClear = new CPanel(L"texture\\CLEAR.png");
			pClear->SetPos(Vec2(380.f, 100.f));
			CreateObj(pClear, GROUP_TYPE::DEFAULT);
		}
		{
			CPanel* pScore = new CPanel(L"texture\\SCORE.png");
			pScore->SetPos(Vec2(540.f, 350.f));
			CreateObj(pScore, GROUP_TYPE::DEFAULT);
		}
		{
			CNumber* pNumber = new CNumber(score, Vec2(620.f, 450.f), 1.5f);
			CreateObj(pNumber, GROUP_TYPE::DEFAULT);
		}
	}
}

void CScene_Ending::Exit()
{

}

CScene_Ending::CScene_Ending()
{
}

CScene_Ending::~CScene_Ending()
{
}
