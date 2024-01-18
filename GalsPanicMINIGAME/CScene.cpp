#include "pch.h"
#include "CScene.h"
#include "func.h"

#include "CObject.h"

void CScene::Update()
{
	for (UINT i = 0; i < (UINT)GROUP_TYPE::END; i++)
	{
		for (size_t j = 0; j < m_arrObj[i].size(); j++)
		{
			// 죽어있지 않으면, 업데이트
			if (!m_arrObj[i][j]->IsDead())
			{
				m_arrObj[i][j]->Update();
			}
		}
	}
}

void CScene::FinalUpdate()
{
	for (UINT i = 0; i < (UINT)GROUP_TYPE::END; i++)
	{
		for (size_t j = 0; j < m_arrObj[i].size(); j++)
		{
			m_arrObj[i][j]->FinalUpdate();
		}
	}
}

void CScene::Render(HDC hdc)
{
	for (UINT i = 0; i < (UINT)GROUP_TYPE::END; i++)
	{
		vector<CObject*>::iterator iter = m_arrObj[i].begin();

		for (; iter != m_arrObj[i].end();)
		{
			// 죽어있지 않으면, 렌더링
			if (!(*iter)->IsDead())
			{
				(*iter)->Render(hdc);
				++iter;	// 삭제한 오브젝트인데 증가시키면 두번증가되니까 정상렌더링 된경우만 증가
			}
			else
			{
				iter = m_arrObj[i].erase(iter); // 마지막 과정에서 삭제시키면, 담프레임에 없어짐
			}
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
		for (size_t j = 0; j < m_arrObj[i].size(); j++)
		{
			if (m_arrObj[i][j] != nullptr)
			{
				// arrObj[i]의 그룹의 벡터 j 물체 삭제
				delete m_arrObj[i][j];
			}
		}
	}
}

void CScene::DeleteGroup(GROUP_TYPE _eTarget)
{
	// 자주 사용하는 코드라서, func.h에 템플릿으로 구현
	SafeDeleteVec(m_arrObj[(UINT)_eTarget]);
}

void CScene::DeleteAll()
{
	// 모든 타입의 오브젝트 제거
	for (UINT i = 0; i < (UINT)GROUP_TYPE::END; i++)
	{
		DeleteGroup((GROUP_TYPE)i);
	}
}
