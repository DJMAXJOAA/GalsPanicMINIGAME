#include "pch.h"
#include "CObject.h"

#include "CCollider.h"

CObject::CObject()
	: m_vPos{}
	, m_vScale{}
	, m_eType(GROUP_TYPE::DEFAULT)
	, m_pCollider(nullptr)
	, m_bAlive(true)
{
}

CObject::CObject(const CObject& _origin)
	: m_vPos(_origin.m_vPos)
	, m_vScale(_origin.m_vScale)
	, m_eType(_origin.m_eType)
	, m_pCollider(nullptr) // 새로 콜라이더 생성
	, m_bAlive(true)
{
	if (_origin.m_pCollider)
	{
		m_pCollider = new CCollider(*_origin.m_pCollider);
		m_pCollider->m_pOwner = this;
	}
}

CObject::~CObject()
{
	if (m_pCollider != nullptr)
	{
		delete m_pCollider;
		m_pCollider = nullptr;
	}
}


float CObject::Random(float min, float max)
{
    std::random_device rand;
    std::mt19937_64 random(rand());
    std::uniform_real_distribution<float> dist1(min, max);

    float temp = 0;
    while (!temp)
    {
        temp = dist1(random);
    }

    return temp;
}

void CObject::FinalUpdate()
{
    if (m_pCollider != nullptr)
        m_pCollider->FinalUpdate();
}

void CObject::Render(HDC hdc)
{
	Rectangle(hdc, (int)(m_vPos.x - m_vScale.x / 2.f), (int)(m_vPos.y - m_vScale.y / 2.f),
		(int)(m_vPos.x + m_vScale.x / 2.f), (int)(m_vPos.y + m_vScale.y / 2.f));
}

void CObject::ComponetRender(HDC hdc)
{
	if (m_pCollider != nullptr)
	{
		m_pCollider->Render(hdc);
	}
}

void CObject::CreateCollider()
{
    m_pCollider = new CCollider;
    m_pCollider->m_pOwner = this;
}