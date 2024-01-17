#pragma once

class CCollider;

class CObject
{
private:
	Vec2 vPos;
	Vec2 vScale;
	GROUP_TYPE type;

	// Componet
	CCollider* m_pCollider;	// nullptr�̶�� �ݶ��̴��� �ʿ� ���� ������Ʈ��(����̳� ui ��)

	bool		m_bAlive;		// Ȱ��ȭ, ��Ȱ��ȭ -> ��Ȱ��ȭ�Ǹ� ���� �����ӿ� ����

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
	// �̺�Ʈ �Ŵ����� ����
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

