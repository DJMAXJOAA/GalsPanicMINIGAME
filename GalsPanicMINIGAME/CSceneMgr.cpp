#include "pch.h"
#include "CSceneMgr.h"

#include "CScene_Start.h"
#include "CScene_Ending.h"
#include "CScene_Title.h"

void CSceneMgr::Init()
{
	arrScene[(UINT)SCENE_TYPE::TITLE] = new CScene_Title;
	arrScene[(UINT)SCENE_TYPE::TITLE]->SetName(L"Ÿ��Ʋ");

	arrScene[(UINT)SCENE_TYPE::START] = new CScene_Start;
	arrScene[(UINT)SCENE_TYPE::START]->SetName(L"���� ����");

	arrScene[(UINT)SCENE_TYPE::ENDING] = new CScene_Ending;
	arrScene[(UINT)SCENE_TYPE::ENDING]->SetName(L"���");

	pCurScene = arrScene[(UINT)SCENE_TYPE::START];
	pCurScene->Enter(); // �� ����
}

void CSceneMgr::Update()
{
	// ���� ���� ������Ʈ �ؾߵ�
	pCurScene->Update();
	pCurScene->FinalUpdate();
}

void CSceneMgr::Render(HDC hdc)
{
	// ����
	pCurScene->Render(hdc);
}

CSceneMgr::CSceneMgr()
	: arrScene{}
	, pCurScene(nullptr)
{
}

CSceneMgr::~CSceneMgr()
{
	for (UINT i = 0; i < (UINT)SCENE_TYPE::END; i++)
	{
		if (nullptr != arrScene[i])
		{
			delete arrScene[i];
		}
	}
}

void CSceneMgr::ChangeScene(SCENE_TYPE _eNext)
{
	pCurScene->Exit();
	pCurScene = arrScene[(UINT)_eNext];

	pCurScene->Enter();
}