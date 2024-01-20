#include "pch.h"
#include "CCollider.h"

#include "CCore.h"

#include "CObject.h"
#include "SelectGDI.h"

UINT CCollider::g_iNextID = 0;

CCollider::CCollider()
	: m_pOwner(nullptr)
	, m_iID(g_iNextID++)
	, m_iCol(0)
{
}

CCollider::CCollider(const CCollider& _origin)
	: m_pOwner(nullptr)					// 콜라이더가 복사되었으면, 원래 있던 주인을 참조시키면 안됨
	, m_vOffsetPos(_origin.m_vOffsetPos)
	, m_vFinalPos(_origin.m_vFinalPos)
	, m_vScale(_origin.m_vScale)			// 나머지 멤버변수들은 그대로 복사
	, m_iID(g_iNextID++)					// ID값은 정적 변수에서 추가시킴
	, m_iCol(0)
{
}

CCollider::~CCollider()
{
	m_pOwner = nullptr;
}

void CCollider::FinalUpdate()
{
	if (m_pOwner == nullptr) return;

	// Object의 위치를 따라감
	Vec2 vObjectPos = m_pOwner->GetPos();
	m_vFinalPos = vObjectPos + m_vOffsetPos;

	assert(0 <= m_iCol);
}

void CCollider::Render(HDC hdc)
{
	//PEN_TYPE ePen = PEN_TYPE::GREEN;
	//if (m_iCol)
	//	ePen = PEN_TYPE::RED;

	//SelectGDI pen(hdc, ePen);
	//SelectGDI brush(hdc, BRUSH_TYPE::HOLLOW);

	//Rectangle(hdc
	//	, (int)(m_vFinalPos.x - m_vScale.x / 2.f)
	//	, (int)(m_vFinalPos.y - m_vScale.y / 2.f)
	//	, (int)(m_vFinalPos.x + m_vScale.x / 2.f)
	//	, (int)(m_vFinalPos.y + m_vScale.y / 2.f));
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
