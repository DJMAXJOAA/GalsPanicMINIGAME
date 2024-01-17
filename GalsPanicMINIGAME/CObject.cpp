#include "pch.h"
#include "CObject.h"

#include "CCollider.h"

CObject::CObject()
	: vPos{}
	, vScale{}
    , m_pCollider(nullptr)
    , m_bAlive(true)
{
}

CObject::~CObject()
{
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
	Rectangle(hdc, (int)(vPos.x - vScale.x / 2.f), (int)(vPos.y - vScale.y / 2.f),
		(int)(vPos.x + vScale.x / 2.f), (int)(vPos.y + vScale.y / 2.f));
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

