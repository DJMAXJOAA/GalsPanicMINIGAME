#include "pch.h"
#include "CText.h"

#include "CPlayer.h"

#include "CDecisionMgr.h"

CText::CText()
	: txtType(PRINT_TYPE::NONE)
	, pTarget(nullptr)
{
}

CText::~CText()
{
}


void CText::Update()
{
	wstring temp;

	switch (txtType)
	{
	case PRINT_TYPE::NONE:
		break;
	case PRINT_TYPE::POS:
	{
		temp = L"x��ǥ : " + std::to_wstring(pTarget->GetPos().x) +
			L", y��ǥ : " + std::to_wstring(pTarget->GetPos().y);
		SetText(temp);
		break;
	}
	case PRINT_TYPE::DIRECTION:
	{
		temp = L"���� : " + std::to_wstring(pTarget->GetDirection());
		SetText(temp);
		break;
	}
	case PRINT_TYPE::STATE:
	{
		temp = L"�÷��̾� ���� : " + std::to_wstring(pTarget->GetState());
		SetText(temp);
		break;
	}
	case PRINT_TYPE::POS_POINT:
	{
		auto itr = CDecisionMgr::GetInstance()->GetPlayerAreaPoint();
		temp = L"���� ��ǥ : " + std::to_wstring(itr->x) + L", " + std::to_wstring(itr->y);
		SetText(temp);
		break;
	}
	default:
		break;
	}
}

void CText::Render(HDC hdc)
{
	Vec2 pos = GetPos();
	TextOut(hdc, (int)pos.x, (int)pos.y, strText.c_str(), strText.length());
}
