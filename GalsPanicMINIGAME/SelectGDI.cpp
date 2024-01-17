#include "pch.h"
#include "SelectGDI.h"

#include "CCore.h"

SelectGDI::SelectGDI(HDC hdc, PEN_TYPE _ePenType)
	: m_hdc(hdc)
	, m_hDefaultBrush(nullptr)
	, m_hDefaultPen(nullptr)
{
	HPEN hPen = CCore::GetInstance()->GetPen(_ePenType);
	m_hDefaultPen = (HPEN)SelectObject(hdc, hPen);
}

SelectGDI::SelectGDI(HDC hdc, BRUSH_TYPE _eBrushType)
	: m_hdc(hdc)
	, m_hDefaultBrush(nullptr)
	, m_hDefaultPen(nullptr)
{
	HBRUSH hBrush = CCore::GetInstance()->GetBrush(_eBrushType);
	m_hDefaultBrush = (HBRUSH)SelectObject(hdc, hBrush);
}

SelectGDI::~SelectGDI()
{
	// 특정 클래스의 함수로 펜을 사용할 때, 그 객체가 사라지면 지역 객체였던 SelectGDI가 사라지게 됨
	// 그러면 자연스럽게 소멸자가 호출되어서 할당했던 펜과 브러시가 dc에 반환된당
	SelectObject(m_hdc, m_hDefaultBrush);
	SelectObject(m_hdc, m_hDefaultPen);
}
