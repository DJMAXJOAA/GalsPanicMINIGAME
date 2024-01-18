#include "pch.h"
#include "CScene_Title.h"

#include "CCore.h"
#include "CPanel.h"

#include "CKeyMgr.h"
#include "CDecisionMgr.h"

void CScene_Title::Update()
{
	CScene::Update();

	if (KEY_TAP(KEY::SPACE))
	{
		ChangeScene(SCENE_TYPE::START);
	}
}

void CScene_Title::Enter()
{
	Vec2 vResolution = CCore::GetInstance()->GetResolution();

	// ÆÐ³Î
	{
		CPanel* background = new CPanel(L"texture\\StartBackground.png");
		CreateObj(background, GROUP_TYPE::DEFAULT);
	}
	{
		CPanel* button = new CPanel(L"texture\\Title.png");
		button->SetPos(Vec2(280.f, 150.f));
		CreateObj(button, GROUP_TYPE::DEFAULT);
	}
	{
		CPanel* button = new CPanel(L"texture\\Start.png");
		button->SetPos(Vec2(350.f, 550.f));
		CreateObj(button, GROUP_TYPE::DEFAULT);
	}
}

void CScene_Title::Exit()
{
}

CScene_Title::CScene_Title()
{
}

CScene_Title::~CScene_Title()
{
}
