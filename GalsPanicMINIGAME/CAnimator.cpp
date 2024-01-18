#include "pch.h"
#include "CAnimator.h"

#include "CDataMgr.h"
#include "CResMgr.h"
#include "CPathMgr.h"
#include "CEventMgr.h"

#include "CObject.h"
#include "CTexture.h"
#include "CAnimation.h"

#include "AnimationData.h"


CAnimator::CAnimator()
	: m_pOwner(nullptr)
	, m_pCurAnim(nullptr)
	, m_bRepeat(false)
	, m_eventTrigger(false)
{
}

CAnimator::CAnimator(const CAnimator& _origin)
	: m_pOwner(nullptr)
	, m_bRepeat(_origin.m_bRepeat)
	, m_iID(_origin.m_iID)
	, m_pCurAnim(nullptr)
	, m_eventTrigger(_origin.m_eventTrigger)
{
	for (const auto& pair : _origin.m_mapAnim)
	{
		m_mapAnim[pair.first] = new CAnimation(*(pair.second));
		m_mapAnim[pair.first]->m_pAnimator = this;
	}

	if (_origin.m_pCurAnim) {
		auto iter = m_mapAnim.find(_origin.m_pCurAnim->GetName());
		if (iter != m_mapAnim.end()) {
			m_pCurAnim = iter->second;
		}
	}
}

CAnimator::~CAnimator()
{
	SafeDeleteMap(m_mapAnim);
}

void CAnimator::CreateAnimation(const wstring& _strName, CTexture* _pTex, Vec2 _vLeftTop, Vec2 _vSliceSize, Vec2 _vStep, float _fDuration, UINT _iFrameCount, int _id, int _iEventFrame)
{
	CAnimation* pAnim = FindAnimation(_strName);
	assert(pAnim == nullptr); // 이미 같은 이름의 애니메이션이 존재하면 안되니까, 오류 검출 부분

	// 존재 안하면 애니메이션 새로 하나 만듬
	pAnim = new CAnimation;

	pAnim->SetName(_strName);
	pAnim->m_pAnimator = this;
	pAnim->m_iEventFrame = _iEventFrame;

	pAnim->Create(_pTex, _vLeftTop, _vSliceSize, _vStep, _fDuration, _iFrameCount);

	m_mapAnim.insert(make_pair(_strName, pAnim));
}

void CAnimator::CreateAnimation(int _key)
{
	AnimationData* data = (AnimationData*)CDataMgr::GetInstance()->FindData(_key);
	CTexture* pTex = CResMgr::GetInstance()->LoadTexture(data->m_strAnimationName, data->m_strTexturePath);

	CAnimation* pAnim = FindAnimation(data->m_strAnimationName);
	assert(pAnim == nullptr); // 이미 같은 이름의 애니메이션이 존재하면 안되니까, 오류 검출 부분

	// 존재 안하면 애니메이션 새로 하나 만듬
	pAnim = new CAnimation;
	pAnim->m_iID = data->GetKey();
	pAnim->m_iEventFrame = data->m_AniInfo.iEventFrame;

	pAnim->SetName(data->m_strAnimationName);
	pAnim->SetType(data->m_strAnimationType);
	pAnim->m_pAnimator = this;

	pAnim->Create(pTex, data->m_AniInfo.vLeftTop, data->m_AniInfo.vSliceSize, data->m_AniInfo.vStep, data->m_AniInfo.fDuration, data->m_AniInfo.iFrame);

	m_mapAnim.insert(make_pair(data->m_strAnimationName, pAnim));
}

CAnimation* CAnimator::FindAnimation(const wstring& _strName)
{
	map<wstring, CAnimation*>::iterator iter = m_mapAnim.find(_strName);
	if (iter == m_mapAnim.end())
		return nullptr;
	
	return iter->second;
}

CAnimation* CAnimator::FindAnimationType(const wstring& _strType)
{
	for (auto& pair : m_mapAnim)
	{
		if (pair.second->GetType() == _strType)
		{
			return pair.second;
		}
	}
	return nullptr;
}

CAnimation* CAnimator::FindAnimation(int _key)
{
	AnimationData* data = (AnimationData*)CDataMgr::GetInstance()->FindData(_key);
	map<wstring, CAnimation*>::iterator iter = m_mapAnim.find(data->m_strAnimationName);
	if (iter == m_mapAnim.end())
		return nullptr;

	return iter->second;
}

void CAnimator::Play(const wstring& _strName, bool _bRepeat)
{
	m_pCurAnim = FindAnimation(_strName);
	m_bRepeat = _bRepeat;
}

void CAnimator::Play(int _key, bool _bRepeat)
{
	m_pCurAnim = FindAnimation(_key);
	m_bRepeat = _bRepeat;
}

void CAnimator::PlayType(const wstring& _strName, bool _bRepeat)
{
	m_pCurAnim = FindAnimationType(_strName);
	m_bRepeat = _bRepeat;
}

void CAnimator::Update()
{
	if (m_pCurAnim != nullptr)
	{
		m_pCurAnim->Update();

		if (m_pCurAnim->GetEventFrame() != m_pCurAnim->GetCurrentFrame())
		{
			m_eventTrigger = false;
		}

		if (m_pCurAnim->isFinish())
		{
			m_pCurAnim->SetFrame(0);

			if (!m_bRepeat)
			{
				AnimationEnd(m_pOwner);
			}
		}
		else if (m_eventTrigger == false
		 && m_pCurAnim->GetEventFrame() != 0
		 && m_pCurAnim->GetEventFrame() == m_pCurAnim->GetCurrentFrame())
		{
			AnimationEvent(m_pOwner);
			m_eventTrigger = true;
		}
	}
}

void CAnimator::FinalUpdate()
{
}

void CAnimator::Render(HDC hdc)
{
	if (m_pCurAnim != nullptr)
		m_pCurAnim->Render(hdc);
}
