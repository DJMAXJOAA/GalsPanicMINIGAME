#include "pch.h"
#include "CTexture.h"

#include "CCore.h"

CTexture::CTexture()
	: m_hBit(0)
	, m_hdc(0)
	, m_bitInfo{}
{
}

CTexture::~CTexture()
{
	DeleteDC(m_hdc);
	DeleteObject(m_hBit);
}

void CTexture::Load(const wstring& _strFilePath)
{
	// 최종 경로 -> 속성, 일반 페이지에서 출력 디렉토리를 $(SolutionDir)Output\bin, bin_debug로 변경해주어야 한다
	// 리소스 파일은 bin 폴더 안의 content 폴더 안에 저장된다 (배포 버전 안에 파일들이 함께 들어있게 하기 위해서)
	m_hBit = (HBITMAP)LoadImage(nullptr, _strFilePath.c_str(), IMAGE_BITMAP, 0, 0, LR_CREATEDIBSECTION | LR_LOADFROMFILE);
	assert(m_hBit); // 오류 검출

	// 비트맵과 연결할 DC
	m_hdc = CreateCompatibleDC(CCore::GetInstance()->GetMainDC());

	// 비트맵과 dc 연결
	HBITMAP hPrevBit = (HBITMAP)SelectObject(m_hdc, m_hBit);
	DeleteObject(hPrevBit);

	// 가로 세로 길이 들어있는 비트맵 정보
	BITMAP tInfo = {};
	GetObject(m_hBit, sizeof(BITMAP), &m_bitInfo);
}

void CTexture::Create(UINT _iWidth, UINT _iHeight)
{
	HDC mainDC = CCore::GetInstance()->GetMainDC();

	m_hBit = CreateCompatibleBitmap(mainDC, _iWidth, _iHeight);
	m_hdc = CreateCompatibleDC(mainDC); // hdc와 동일한 dc 가져오기

	HBITMAP hOldBit = (HBITMAP)SelectObject(m_hdc, m_hBit);
	DeleteObject(hOldBit);

	GetObject(m_hBit, sizeof(BITMAP), &m_bitInfo);
}

