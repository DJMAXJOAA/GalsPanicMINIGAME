#include "pch.h"
#include "CSceneMgr.h"

#include "CScene_Start.h"

void CSceneMgr::Init()
{
	arrScene[(UINT)SCENE_TYPE::START] = new CScene_Start;
	arrScene[(UINT)SCENE_TYPE::START]->SetName(L"¾ÀÀÇ ÀÌ¸§");

	pCurScene = arrScene[(UINT)SCENE_TYPE::START];
	pCurScene->Enter(); // ¾À ÁøÀÔ
}

void CSceneMgr::Update()
{
	// ÇöÀç ¾ÀÀ» ¾÷µ¥ÀÌÆ® ÇØ¾ßµÊ
	pCurScene->Update();

}

void CSceneMgr::Render(HDC hdc)
{
	// Àü´Þ
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
