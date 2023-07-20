#include "pch.h"
#include "CText.h"
#include "CPlayer.h"

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
		temp = L"x좌표 : " + std::to_wstring(pTarget->GetPos().x) +
			L", y좌표 : " + std::to_wstring(pTarget->GetPos().y);
		SetText(temp);
		break;
	case PRINT_TYPE::DIRECTION:
		temp = L"이동 방향 : " + std::to_wstring(pTarget->GetDirection());
		SetText(temp);
		break;
	case PRINT_TYPE::STATE:
		temp = L"플레이어 상태 : " + std::to_wstring(pTarget->GetState());
		SetText(temp);
		break;
	default:
		break;
	}
}

void CText::Render(HDC hdc)
{
	Vec2 pos = GetPos();
	TextOut(hdc, pos.x, pos.y, strText.c_str(), strText.length());
}
