#include "pch.h"
#include "CCollisionMgr.h"

#include "CSceneMgr.h"

#include "CScene.h"
#include "CObject.h"

#include "CCollider.h"

CCollisionMgr::CCollisionMgr()
	: m_arrCheck{}
{
}

CCollisionMgr::~CCollisionMgr()
{
}

void CCollisionMgr::Init()
{
	
}

void CCollisionMgr::Update()
{
	// 비트값이 ON 되어있는 부분만 체크하게 한다(전체 다돌리면 부담이 너무 심해짐)
	for (UINT iRow = 0; iRow < (UINT)GROUP_TYPE::END; iRow++)
	{
		// 시작부분이 iRow부터임, 왜냐면 중복체크 안할려고 -> 행이 항상 더 작음
		for (UINT iCol = iRow; iCol < (UINT)GROUP_TYPE::END; iCol++) 
		{
			if (m_arrCheck[iRow] & (1 << iCol)) // 비트 true인가 체크 -> 그룹끼리 비교하려고
			{
				CollisionGroupUpdate((GROUP_TYPE)iRow, (GROUP_TYPE)iCol);
			}
		}
	}
}

void CCollisionMgr::CheckGroup(GROUP_TYPE _eLeft, GROUP_TYPE _eRight)
{
	// 더 작은 값의 그룹을 행으로 사용
	// 더 큰 값을 열(비트) 로 사용한다
	UINT iRow = (UINT)_eLeft;
	UINT iCol = (UINT)_eRight; 

	if (iCol < iRow) // 뭐가 더 많은지 정해줘야된다, 항상 열(col)이 더 커야댐
	{
		iRow = (UINT)_eRight;
		iCol = (UINT)_eLeft;
	}

	if (m_arrCheck[iRow] & (1 << iCol))		// 이미 체크가 되어있으면, 체크를 해제한다
	{
		m_arrCheck[iRow] &= ~(1 << iCol); 
	}
	else
	{
		m_arrCheck[iRow] |= (1 << iCol);	// 내가 원하는 부분 체크 가능(iCol만큼 비트를 이동 -> 체크박스) 
	}
}

void CCollisionMgr::CollisionGroupUpdate(GROUP_TYPE _eLeft, GROUP_TYPE _eRight)
{
	// Update에서 비교하고, 특정 그룹끼리만 충돌을 비교한다
	CScene* pCurScene = CSceneMgr::GetInstance()->GetCurScene();
	
	// 레퍼런스 값 주의(얕은 복사, 깊은 복사)
	const vector<CObject*>& vecLeft = pCurScene->GetGroupObject(_eLeft);
	const vector<CObject*>& vecRight = pCurScene->GetGroupObject(_eRight);

	// 이전 프레임의 충돌 정보를 갖고 있는 map 컨테이너
	map<ULONGLONG, bool>::iterator iter;

	// 충돌 비교
	// 주의사항1 :: 자기 자신과 비교 하지 않기
	// 주의사항2 :: 콜라이더가 없는 오브젝트와 비교하지 않기
	for (size_t i = 0; i < vecLeft.size(); i++)
	{
		if (vecLeft[i]->GetCollider() == nullptr) // 콜라이더 없는 오브젝트와의 비교
			continue;

		for (size_t j = 0; j < vecRight.size(); j++)
		{
			// 콜라이더 없는 오브젝트 패스 + 자기 자신 패스
			if (vecRight[j]->GetCollider() == nullptr || vecLeft[i] == vecRight[j])
				continue;

			CCollider* pLeftCol = vecLeft[i]->GetCollider();
			CCollider* pRightCol = vecRight[j]->GetCollider();

			// 공용체의 공유 속성을 활용해서 고유의 새로운 키값 만들기
			// 두 충돌체 조합 아이디
			COLLIDER_ID ID{};
			ID.iLeft_id = pLeftCol->GetID();
			ID.iRight_id = pRightCol->GetID();
			iter = m_mapColInfo.find(ID.ID);

			// 검사 최초진행(맵에 정보가 없음, 다음에 검색할때 true false판단)
			if (m_mapColInfo.end() == iter)
			{
				m_mapColInfo.insert(make_pair(ID.ID, false));
				iter = m_mapColInfo.find(ID.ID); // 등록 후 다시 재검색
			}

			// 실제로 충돌 비교하는 부분 -> 따로 함수로 비교
			if (IsCollision(pLeftCol, pRightCol))
			{
				if (iter->second)
				{
					// 전 프레임에도 충돌중이였음(Stay)

					if (vecLeft[i]->IsDead() || vecRight[j]->IsDead())
					{
						// 근데 둘중 하나 이상이 없어질 예정임 -> 그러면 충돌 벗어난 처리
						pLeftCol->OnCollisionExit(pRightCol);
						pRightCol->OnCollisionExit(pLeftCol);
						iter->second = false;
					}

					pLeftCol->OnCollision(pRightCol);
					pRightCol->OnCollision(pLeftCol);
				}
				else
				{
					// 처음 충돌하는 상황(Enter)

					if (!vecLeft[i]->IsDead() && !vecRight[j]->IsDead())
					{
						// 둘다 살아있어야 조건 성립, 하나라도 죽으면 걍 충돌 없는 처리
						pLeftCol->OnCollisionEnter(pRightCol);
						pRightCol->OnCollisionEnter(pLeftCol);
						iter->second = true;
					}
				}
			}
			else
			{
				if (iter->second)
				{
					// 막 벗어난 상황(Exit)
					pLeftCol->OnCollisionExit(pRightCol);
					pRightCol->OnCollisionExit(pLeftCol);
					iter->second = false;
				}
			}
		}
	}
}

bool CCollisionMgr::IsCollision(CCollider* _pLeftCol, CCollider* _pRightCol)
{
	// 충돌을 실제로 검사
	Vec2 vLeftPos = _pLeftCol->GetFinalPos();
	Vec2 vLeftScale = _pLeftCol->GetScale();

	Vec2 vRightPos = _pRightCol->GetFinalPos();
	Vec2 vRightScale = _pRightCol->GetScale();

	if (abs(vRightPos.x - vLeftPos.x) < (vLeftScale.x + vRightScale.x) / 2.f
		&& abs(vRightPos.y - vLeftPos.y) < (vLeftScale.y + vRightScale.y) / 2.f)
	{
		return true;
	}

	return false;
}
