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
	if (IsDead()) return;

	wstring temp;

	switch (txtType)
	{
	case PRINT_TYPE::NONE:
		break;
	case PRINT_TYPE::POS:
	{
		temp = L"x좌표 : " + std::to_wstring(pTarget->GetPos().x) +
			L", y좌표 : " + std::to_wstring(pTarget->GetPos().y);
		SetText(temp);
		break;
	}
	case PRINT_TYPE::DIRECTION:
	{
		temp = L"방향 : " + std::to_wstring(pTarget->GetDirection());
		SetText(temp);
		break;
	}
	case PRINT_TYPE::STATE:
	{
		temp = L"플레이어 상태 : " + std::to_wstring(pTarget->GetState());
		SetText(temp);
		break;
	}
	case PRINT_TYPE::POS_POINT:
	{
		auto itr = CDecisionMgr::GetInstance()->GetPlayerAreaPoint();
		temp = L"기준 좌표 : " + std::to_wstring(itr->x) + L", " + std::to_wstring(itr->y);
		SetText(temp);
		break;
	}
	case PRINT_TYPE::AREA:
	{
		float fExtent = CDecisionMgr::GetInstance()->GetArea()->GetExtent();
		temp = L"점령 퍼센트 : " + std::to_wstring(CDecisionMgr::GetInstance()->GetArea()->GetExtent()) + L"% ";
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
