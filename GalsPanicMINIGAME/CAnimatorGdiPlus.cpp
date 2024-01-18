#include "pch.h"
#include "CAnimatorGdiPlus.h"

#include "CResMgr.h"
#include "CPathMgr.h"
#include "CEventMgr.h"

#include "CObject.h"
#include "CGdiPlus.h"
#include "CAnimationGdiPlus.h"

CAnimatorGdiPlus::CAnimatorGdiPlus()
	: m_pOwner(nullptr)
	, m_pCurAnim(nullptr)
	, m_bRepeat(false)
    , m_eventTrigger(false)
{
}

CAnimatorGdiPlus::CAnimatorGdiPlus(const CAnimatorGdiPlus& _origin)
    : m_pOwner(nullptr)
    , m_bRepeat(_origin.m_bRepeat)
    , m_iID(_origin.m_iID)
    , m_pCurAnim(nullptr)
{
    for (const auto& pair : _origin.m_mapAnim)
    {
        m_mapAnim[pair.first] = new CAnimationGdiPlus(*(pair.second));
        m_mapAnim[pair.first]->m_pAnimator = this;
    }

    if (_origin.m_pCurAnim) {
        auto iter = m_mapAnim.find(_origin.m_pCurAnim->GetName());
        if (iter != m_mapAnim.end()) {
            m_pCurAnim = iter->second;
        }
    }
}

CAnimatorGdiPlus::~CAnimatorGdiPlus()
{
	SafeDeleteMap(m_mapAnim);
}

void CAnimatorGdiPlus::CreateAnimation(const wstring& _strName, CGdiPlus* _pBitmap, Vec2 _vLeftTop, Vec2 _vSliceSize, Vec2 _vStep, float _fDuration, UINT _iFrameCount, int _id, int _eventFrame)
{
    CAnimationGdiPlus* pAnim = FindAnimation(_strName);
    assert(pAnim == nullptr);

    pAnim = new CAnimationGdiPlus;
    pAnim->SetName(_strName);
    pAnim->m_pAnimator = this;
    pAnim->m_iID = _id;
    pAnim->m_iEventFrame = _eventFrame;

    pAnim->Create(_pBitmap, _vLeftTop, _vSliceSize, _vStep, _fDuration, _iFrameCount);

    m_mapAnim.insert(make_pair(_strName, pAnim));
}

void CAnimatorGdiPlus::CreateAnimation(int _key)
{
    AnimationData* data = (AnimationData*)CDataMgr::GetInstance()->FindData(_key);
    CGdiPlus* pBitmap = CResMgr::GetInstance()->LoadGdiPlus(data->m_strAnimationName, data->m_strTexturePath);

    CAnimationGdiPlus* pAnim = FindAnimation(data->m_strAnimationName);
    assert(pAnim == nullptr); // 이미 같은 이름의 애니메이션이 존재하면 안되니까, 오류 검출 부분

    // 존재 안하면 애니메이션 새로 하나 만듬
    pAnim = new CAnimationGdiPlus;
    pAnim->m_iID = data->GetKey();
    pAnim->m_iEventFrame = data->m_AniInfo.iEventFrame;

    pAnim->SetName(data->m_strAnimationName);
    pAnim->m_pAnimator = this;

    pAnim->Create(pBitmap, data->m_AniInfo.vLeftTop, data->m_AniInfo.vSliceSize, data->m_AniInfo.vStep, data->m_AniInfo.fDuration, data->m_AniInfo.iFrame);

    m_mapAnim.insert(make_pair(data->m_strAnimationName, pAnim));
}

CAnimationGdiPlus* CAnimatorGdiPlus::FindAnimation(const wstring& _strName)
{
    map<wstring, CAnimationGdiPlus*>::iterator iter = m_mapAnim.find(_strName);
    if (iter == m_mapAnim.end())
        return nullptr;

    return iter->second;
}

CAnimationGdiPlus* CAnimatorGdiPlus::FindAnimation(int _key)
{
    AnimationData* data = (AnimationData*)CDataMgr::GetInstance()->FindData(_key);
    map<wstring, CAnimationGdiPlus*>::iterator iter = m_mapAnim.find(data->m_strAnimationName);
    if (iter == m_mapAnim.end())
        return nullptr;

    return iter->second;
}

void CAnimatorGdiPlus::Play(const wstring& _strName, bool _bRepeat)
{
    m_pCurAnim = FindAnimation(_strName);
    m_bRepeat = _bRepeat;
}

void CAnimatorGdiPlus::Play(int _key, bool _bRepeat)
{
    m_pCurAnim = FindAnimation(_key);
    m_bRepeat = _bRepeat;
}

void CAnimatorGdiPlus::Update()
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
            if (!m_bRepeat)
            {
                AnimationEnd(m_pOwner);
            }
            else
            {
                m_pCurAnim->SetFrame(0);
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

void CAnimatorGdiPlus::FinalUpdate()
{
}

void CAnimatorGdiPlus::Render(HDC hdc)
{
    if (m_pCurAnim != nullptr)
        m_pCurAnim->Render(hdc);
}
