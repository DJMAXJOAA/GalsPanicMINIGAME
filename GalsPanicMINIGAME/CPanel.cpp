#include "pch.h"
#include "CPanel.h"

#include "CCore.h"

#include "CResMgr.h"
#include "CPathMgr.h"

CPanel::CPanel(wstring _filename)
	: m_image(nullptr)
{
	wstring strFilePath = CPathMgr::GetInstance()->GetContentPath();
	strFilePath += _filename;

	m_image = new Image(strFilePath.c_str());

	// 오류 검출
	assert(m_image);
}

CPanel::~CPanel()
{
	delete m_image;
}

void CPanel::Render(HDC hdc)
{
	Graphics graphics(hdc);

	graphics.DrawImage(m_image, GetPos().x, GetPos().y);
}

void CPanel::Update()
{
}
