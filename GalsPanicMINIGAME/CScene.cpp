#include "pch.h"
#include "CScene.h"
#include "func.h"

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

void CScene::FinalUpdate()
{
	for (UINT i = 0; i < (UINT)GROUP_TYPE::END; i++)
	{
		for (size_t j = 0; j < arrObj[i].size(); j++)
		{
			arrObj[i][j]->FinalUpdate();
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
			if (arrObj[i][j] != nullptr)
			{
				// arrObj[i]의 그룹의 벡터 j 물체 삭제
				delete arrObj[i][j];
			}
		}
	}
}

void CScene::DeleteGroup(GROUP_TYPE _eTarget)
{
	// 자주 사용하는 코드라서, func.h에 템플릿으로 구현
	SafeDeleteVec(arrObj[(UINT)_eTarget]);
}

void CScene::DeleteAll()
{
	// 모든 타입의 오브젝트 제거
	for (UINT i = 0; i < (UINT)GROUP_TYPE::END; i++)
	{
		DeleteGroup((GROUP_TYPE)i);
	}
}
