#include "pch.h"
#include "CHeart.h"

#include "CCore.h"

#include "CResMgr.h"
#include "CPathMgr.h"
#include "CDecisionMgr.h"

CHeart::CHeart(int health)
	: m_iHP(health)
	, m_iMaxHP(health)
	, m_iWidth(0)
	, m_vecImages(health)
	
{
	wstring strFilePath = CPathMgr::GetInstance()->GetContentPath();
	strFilePath += L"texture\\heart.png";

	for (int i = 0; i < health; i++)
	{
		Image* temp = new Image(strFilePath.c_str());
		m_iWidth = temp->GetWidth();
		m_vecImages[i] = temp;
	}
}

CHeart::~CHeart()
{
	SafeDeleteVec(m_vecImages);
}

void CHeart::ReduceHP()
{
	m_iHP--;
	if (m_iHP == 0)
	{
		CDecisionMgr::GetInstance()->SetTimeScore(0);
		ChangeScene(SCENE_TYPE::ENDING);
	}
}

void CHeart::Render(HDC hdc)
{
	Graphics graphics(hdc);

	Vec2 vPos = GetPos();
	for (int i = 0; i < m_iHP; i++)
	{
		graphics.DrawImage(m_vecImages[i], GetPos().x + ((m_iWidth / 2) * i), GetPos().y);
	}
}

void CHeart::Update()
{
}
