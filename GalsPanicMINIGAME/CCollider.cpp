#include "pch.h"
#include "CCollider.h"

#include "CCore.h"

#include "CObject.h"

UINT CCollider::g_iNextID = 0;

CCollider::CCollider()
	: m_pOwner(nullptr)
	, m_iID(g_iNextID++)
	, m_iCol(0)
{
}

CCollider::CCollider(const CCollider& _origin)
	:m_pOwner(nullptr)					// �ݶ��̴��� ����Ǿ�����, ���� �ִ� ������ ������Ű�� �ȵ�
	, m_vOffsetPos(_origin.m_vOffsetPos)
	, m_vFinalPos(_origin.m_vFinalPos)
	, m_vScale(_origin.m_vScale)			// ������ ����������� �״�� ����
	, m_iID(g_iNextID++)					// ID���� ���� �������� �߰���Ŵ
	, m_iCol(0)
{

}

CCollider::~CCollider()
{
}

void CCollider::FinalUpdate()
{
	// Object�� ��ġ�� ����
	Vec2 vObjectPos = m_pOwner->GetPos();
	m_vFinalPos = vObjectPos + m_vOffsetPos;

	assert(0 <= m_iCol);
}

void CCollider::Render(HDC hdc)
{

}

void CCollider::OnCollision(CCollider* _pOther)
{
	m_pOwner->OnCollision(_pOther);
}

void CCollider::OnCollisionEnter(CCollider* _pOther)
{
	++m_iCol;
	m_pOwner->OnCollisionEnter(_pOther);
}

void CCollider::OnCollisionExit(CCollider* _pOther)
{
	--m_iCol;
	m_pOwner->OnCollisionExit(_pOther);
}
