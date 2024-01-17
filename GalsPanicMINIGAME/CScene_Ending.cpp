#include "pch.h"
#include "CScene_Ending.h"
#include "func.h"

#include "CPlayer.h"
#include "CText.h"

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
	CKeyMgr::GetInstance()->Init();
	CDecisionMgr::GetInstance()->Init();
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
