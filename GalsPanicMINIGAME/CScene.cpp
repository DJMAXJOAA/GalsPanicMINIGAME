#include "pch.h"
#include "CScene.h"

#include "CObject.h"

void CScene::Update()
{
	for (UINT i = 0; i < (UINT)GROUP_TYPE::END; i++)
	{
		for (size_t j = 0; j < arrObj[i].size(); j++)
		{
			arrObj[i][j]->Update();
		}
	}
}

void CScene::Render(HDC hdc)
{
	for (UINT i = 0; i < (UINT)GROUP_TYPE::END; i++)
	{
		for (size_t j = 0; j < arrObj[i].size(); j++)
		{
			arrObj[i][j]->Render(hdc);
		}
	}
}

CScene::CScene()
{
}

CScene::~CScene()
{
	// 씬 모든 오브젝트 삭제
	for (UINT i = 0; i < (UINT)GROUP_TYPE::END; i++)
	{
		for (size_t j = 0; j < arrObj[i].size(); j++)
		{
			// arrObj[i]의 그룹의 벡터 j 물체 삭제
			delete arrObj[i][j];
		}
	}
}
