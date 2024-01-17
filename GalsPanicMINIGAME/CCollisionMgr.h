#pragma once

class CCollider;

// map의 키값으로 들어갈, 콜라이더만으로 생성하는 고유의 키값(겹치지 않는)
// 공용체의 서로 값을 공유하는 속성을 통해 map에 저장할 수 있는 새로운 충돌 정보를 만들고 저장한다
union COLLIDER_ID
{
	struct
	{
		UINT iLeft_id;
		UINT iRight_id;
	};
	ULONGLONG ID;
};

class CCollisionMgr
{
	SINGLE(CCollisionMgr);
private:
	map<ULONGLONG, bool>	m_mapColInfo;	// 충돌체 간의 이전 프레임 충돌 정보 (공용체를 이용한 키값->고유의 값, bool값)
	UINT					m_arrCheck[(UINT)GROUP_TYPE::END];	// 그룹간 충돌 체크

private:
	CCollisionMgr();
	~CCollisionMgr();

public:
	void Init();
	void Update();
	void Reset() { memset(m_arrCheck, 0, sizeof(UINT) * (UINT)GROUP_TYPE::END); } // 비트들을 비교하는데 비트 초기화
	void CheckGroup(GROUP_TYPE _eLeft, GROUP_TYPE _eRight);

private:
	void CollisionGroupUpdate(GROUP_TYPE _eLeft, GROUP_TYPE _eRight);
	bool IsCollision(CCollider* _pLeftCol, CCollider* _pRightCol);
};

