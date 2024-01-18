#include "pch.h"
#include "CScene_Ending.h"

#include "CCore.h"
#include "CPanel.h"

#include "CKeyMgr.h"
#include "CDecisionMgr.h"

void CScene_Ending::Update()
{
	CScene::Update();

	if (KEY_TAP(KEY::ENTER))
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

	// ÆÐ³Î
	{
		CPanel* background = new CPanel(L"texture\\StartBackground.png");
		CreateObj(background, GROUP_TYPE::DEFAULT);
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
