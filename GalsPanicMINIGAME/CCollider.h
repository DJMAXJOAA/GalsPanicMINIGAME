#pragma once
class CObject;

class CCollider
{
private:
	// 콜라이더의 생성자가 불릴때마다 g_iNextID를 증가시키고, m_iID에 값을 넣어준다.
	static UINT g_iNextID;	// 정적 멤버라서 클래스 멤버에 포함 ㄴ, 데이터 영역에 저장되서 사라지지 않음

	CObject* m_pOwner;		// 콜라이더가 붙어있는 오브젝트의 정보를 알아야 한다(그래야 따라다니니깐)
	Vec2	 m_vOffsetPos;	// 기준 좌표(부착된 오브젝트의 좌표)부터의 상대적인 거리
	Vec2	 m_vFinalPos;	// FinalUpdate()를 통해 계산된 최종 콜라이더 위치(오프셋+좌표값) -> 매 프레임 계산해서 갱신
	Vec2	 m_vScale;		// 충돌체의 크기

	UINT	 m_iID;			// 멤버의 고유 ID값 (겹치면 안됨)
	UINT	 m_iCol;

public:
	CCollider();
	CCollider(const CCollider& _origin); // 깊은 복사를 통해 생성되는 복사 생성자
	~CCollider();

	CCollider& operator = (CCollider& _origin) = delete;

	friend class CObject;

public:
	void SetOffsetPos(Vec2 _vPos) { m_vOffsetPos = _vPos; }
	void SetScale(Vec2 _vScale) { m_vScale = _vScale; }
	void SetFinalPos(Vec2 _vPos) { m_vFinalPos = _vPos; }

public:
	Vec2 GetOffsetPos() { return m_vOffsetPos; }
	Vec2 GetScale() { return m_vScale; }
	Vec2 GetFinalPos() { return m_vFinalPos; }

	UINT GetID() { return m_iID; }

	CObject* GetObj() { return m_pOwner; }

public:
	void FinalUpdate();
	void Render(HDC hdc);	// 테스트 할땐 켜놨다가, 배포때 끄기

public:
	void OnCollision(CCollider* _pOther);		// 충돌 중일때 호출
	void OnCollisionEnter(CCollider* _pOther);	// 충돌 진입했을때 호출
	void OnCollisionExit(CCollider* _pOther);	// 충돌 진입했을때 호출
};