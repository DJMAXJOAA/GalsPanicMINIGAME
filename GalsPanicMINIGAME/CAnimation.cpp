#include "pch.h"
#include "CAnimation.h"

#include "CTimeMgr.h"

#include "CAnimator.h"
#include "CTexture.h"
#include "CObject.h"

CAnimation::CAnimation()
	: m_pAnimator(nullptr)
	, m_pTex(nullptr)
	, m_iCurFrame(0)
	, m_fAccTime(0.f)
	, m_bFinish(false)
	, m_iID(0)
	, m_bFlip(false)
	, m_iEventFrame(0)
{
}

CAnimation::CAnimation(const CAnimation& _origin)
	: m_strName(_origin.m_strName)
	, m_strType(_origin.m_strType)
	, m_pAnimator(nullptr)
	, m_pTex(_origin.m_pTex)
	, m_vecFrame(_origin.m_vecFrame)
	, m_iCurFrame(_origin.m_iCurFrame)
	, m_fAccTime(_origin.m_fAccTime)
	, m_bFinish(_origin.m_bFinish)
	, m_bFlip(_origin.m_bFlip)
	, m_iID(_origin.m_iID)
	, m_iEventFrame(_origin.m_iEventFrame)
{

}

CAnimation::~CAnimation()
{
}

void CAnimation::Update()
{
	if (m_bFinish) // 끝난거면 재생 안하게 설정하기
		return;

	// 시간에 따라 애니메이션 변화되게 설정
	m_fAccTime += fDT;	// 누적시간, 흘러간 시간

	if (m_vecFrame[m_iCurFrame].fDuration < m_fAccTime)
	{
		++m_iCurFrame;
		
		// 사이즈랑 동일하면 다시 돌아가게
		if (m_vecFrame.size() <= m_iCurFrame)
		{
			m_iCurFrame = -1;
			m_bFinish = true;
			m_fAccTime = 0.f;
			return;
		}

		m_fAccTime = m_fAccTime - m_vecFrame[m_iCurFrame].fDuration;
	}
}

void CAnimation::Render(HDC hdc)
{
	if (m_bFinish) // 끝난거면 재생 안하게 설정하기
		return;

	CObject* pObj = m_pAnimator->GetObj();
	Vec2 vPos = pObj->GetPos();

	// 피벗 설정
	if (m_bFlip)
	{
		vPos.x -= m_vecFrame[m_iCurFrame].vOffset.x;
		vPos.y += m_vecFrame[m_iCurFrame].vOffset.y;
	}
	else
	{
		vPos += m_vecFrame[m_iCurFrame].vOffset;
	}

	int iRenderStartX = (int)m_vecFrame[m_iCurFrame].vLeftTop.x;
	int iRenderWidth = (int)m_vecFrame[m_iCurFrame].vSlice.x;
	int iRenderHeight = (int)m_vecFrame[m_iCurFrame].vSlice.y;

	HBITMAP hBitmap;
	HDC hdcTemp = CreateCompatibleDC(hdc);
	hBitmap = CreateCompatibleBitmap(hdc, iRenderWidth, iRenderHeight);
	SelectObject(hdcTemp, hBitmap);

	if (m_bFlip)
	{
		iRenderStartX += iRenderWidth - 1;
		iRenderWidth = -iRenderWidth;
		StretchBlt(hdcTemp, 0, 0, abs(iRenderWidth), iRenderHeight, m_pTex->GetDC(), iRenderStartX, (int)m_vecFrame[m_iCurFrame].vLeftTop.y, iRenderWidth, iRenderHeight, SRCCOPY);
	}
	else
	{
		BitBlt(hdcTemp, 0, 0, iRenderWidth, iRenderHeight, m_pTex->GetDC(), iRenderStartX, (int)m_vecFrame[m_iCurFrame].vLeftTop.y, SRCCOPY);
	}

	TransparentBlt(hdc, (int)(vPos.x - abs(iRenderWidth) / 2.f), (int)(vPos.y - iRenderHeight / 2.f), abs(iRenderWidth), iRenderHeight, hdcTemp, 0, 0, abs(iRenderWidth), iRenderHeight, RGB(255, 0, 255));

	DeleteObject(hBitmap);
	DeleteDC(hdcTemp);
}

void CAnimation::Create(CTexture* _pTex, Vec2 _vLeftTop, Vec2 _vSliceSize, Vec2 _vStep, float _fDuration, UINT _iFrameCount)
{
	m_pTex = _pTex;

	tAnimFrame frm = {};
	for (int i = 0; i < (int)_iFrameCount; ++i)
	{
		frm.fDuration = _fDuration;
		frm.vSlice = _vSliceSize;
		frm.vLeftTop = _vLeftTop + _vStep * i;

		m_vecFrame.push_back(frm);
	}
}
