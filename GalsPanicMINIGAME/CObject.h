#pragma once

class CCollider;

class CObject
{
private:
	Vec2 vPos;
	Vec2 vScale;
	GROUP_TYPE type;

	// Componet
	CCollider* m_pCollider;	// nullptr이라면 콜라이더가 필요 없는 오브젝트들(배경이나 ui 등)

	bool		m_bAlive;		// 활성화, 비활성화 -> 비활성화되면 다음 프레임에 삭제

public:
	void SetPos(Vec2 _vPos) { vPos = _vPos; }
	void SetScale(Vec2 _vScale) { vScale = _vScale; }
	void SetType(GROUP_TYPE _type) { type = _type; }

	Vec2 GetPos() { return vPos; }
	Vec2 GetScale() { return vScale; }
	GROUP_TYPE GetType() { return type; }

	CCollider* GetCollider() { return m_pCollider; }
	bool IsDead() { return !m_bAlive; }

	float Random(float min, float max);

private:
	// 이벤트 매니저만 접근
	void SetDead() { m_bAlive = false; }

public:
	virtual void Update() = 0;
	virtual void FinalUpdate();
	virtual void Render(HDC hdc);
	void ComponetRender(HDC hdc);

public:
	void CreateCollider();
	virtual void OnCollision(CCollider* _pOther) {};
	virtual void OnCollisionEnter(CCollider* _pOther) {};
	virtual void OnCollisionExit(CCollider* _pOther) {};

public:
	CObject();
	~CObject();

	friend class CEventMgr;
};

