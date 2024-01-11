#pragma once

class CCollider;

class CObject
{
private:
	Vec2 vPos;
	Vec2 vScale;

	// Componet
	CCollider* m_pCollider;	// nullptr이라면 콜라이더가 필요 없는 오브젝트들(배경이나 ui 등)

public:
	void SetPos(Vec2 _vPos) { vPos = _vPos; }
	void SetScale(Vec2 _vScale) { vScale = _vScale; }

	Vec2 GetPos() { return vPos; }
	Vec2 GetScale() { return vScale; }

	CCollider* GetCollider() { return m_pCollider; }

	float Random(float min, float max);

public:
	virtual void Update() = 0;
	virtual void Render(HDC hdc);

public:
	void CreateCollider();
	virtual void OnCollision(CCollider* _pOther) {};
	virtual void OnCollisionEnter(CCollider* _pOther) {};
	virtual void OnCollisionExit(CCollider* _pOther) {};

public:
	CObject();
	~CObject();
};

