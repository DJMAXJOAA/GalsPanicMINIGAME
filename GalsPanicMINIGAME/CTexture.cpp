#include "pch.h"
#include "CTexture.h"

#include "CCore.h"

void CTexture::Load(const wstring& _strFilePath)
{
	// 경로 가져오기 (오브젝트 ID), _strFilePath는 파일의 상대경로(최종 경로를 가져옴)
	hBit = (HBITMAP)LoadImage(nullptr, _strFilePath.c_str(), IMAGE_BITMAP, 0, 0, LR_CREATEDIBSECTION | LR_LOADFROMFILE);

	// 비트맵과 연결할 DC
	hDC = CreateCompatibleDC(CCore::GetInstance()->getMainDC());

	// 비트맵과 DC 연결
	HBITMAP hPrevBit = (HBITMAP)SelectObject(hDC, hBit);
	DeleteObject(hPrevBit);

	// 비트맵 정보
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
