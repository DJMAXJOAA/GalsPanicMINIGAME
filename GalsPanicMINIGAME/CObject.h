#pragma once
class CCollider;

class CObject
{
private:
	Vec2		m_vPos;
	Vec2		m_vScale;
	GROUP_TYPE	m_eType;

	// Componet
	CCollider*	m_pCollider;	// nullptr�̶�� �ݶ��̴��� �ʿ� ���� ������Ʈ��(����̳� ui ��)

	bool		m_bAlive;		// Ȱ��ȭ, ��Ȱ��ȭ -> ��Ȱ��ȭ�Ǹ� ���� �����ӿ� ����

public:
	void SetPos(Vec2 _vPos) { m_vPos = _vPos; }
	void SetScale(Vec2 _vScale) { m_vScale = _vScale; }
	void SetType(GROUP_TYPE _type) { m_eType = _type; }

	Vec2 GetPos() { return m_vPos; }
	Vec2 GetScale() { return m_vScale; }
	GROUP_TYPE GetType() { return m_eType; }

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
	CObject(const CObject& _origin); // ���� ����
	virtual ~CObject();

	virtual CObject* Clone() = 0;	// ����

	friend class CEventMgr;
};

