#include "pch.h"
#include "CTexture.h"

#include "CCore.h"

void CTexture::Load(const wstring& _strFilePath)
{
	// ��� �������� (������Ʈ ID), _strFilePath�� ������ �����(���� ��θ� ������)
	hBit = (HBITMAP)LoadImage(nullptr, _strFilePath.c_str(), IMAGE_BITMAP, 0, 0, LR_CREATEDIBSECTION | LR_LOADFROMFILE);

	// ��Ʈ�ʰ� ������ DC
	hDC = CreateCompatibleDC(CCore::GetInstance()->getMainDC());

	// ��Ʈ�ʰ� DC ����
	HBITMAP hPrevBit = (HBITMAP)SelectObject(hDC, hBit);
	DeleteObject(hPrevBit);

	// ��Ʈ�� ����
	GetObject(hBit, sizeof(BITMAP), &BitInfo);
}

CTexture::CTexture()
	: hBit(0)
	, hDC(0)
{
}

CTexture::~CTexture()
{
	DeleteDC(hDC);
	DeleteObject(hBit);
}
