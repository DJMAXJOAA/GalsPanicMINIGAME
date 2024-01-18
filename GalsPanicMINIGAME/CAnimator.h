#pragma once

class CObject;
class CTexture;
class CAnimation;

class CAnimator
{
private:
	CObject*					m_pOwner;		// 애니메이션 소유 오브젝트
	bool						m_bRepeat;		// 반복재생 여부
	bool						m_eventTrigger;	// 이벤트 중복 전송 방지
	int							m_iID;			// 데이터 아이디

	map<wstring, CAnimation*>	m_mapAnim;				// 모든 애니메이션 목록
	CAnimation*					m_pCurAnim;				// 현재 재생중인 애니메이션

public:
	CAnimator();
	CAnimator(const CAnimator& _origin);
	~CAnimator();

	friend class CObject;

public:
	void AnimationEvent(CObject* _pObj);
	void AnimationEnd(CObject* _pObj);

public:
	int GetID() { return m_iID; }
	CAnimation* GetAnimation() { return m_pCurAnim; }
	CObject* GetObj() { return m_pOwner; }

public:
	void CreateAnimation(const wstring& _strName, CTexture* _pTex, Vec2 _vLeftTop, Vec2 _vSliceSize, Vec2 _vStep, float _fDuration, UINT _iFrameCount, int _id, int _iEventFrame);
	void CreateAnimation(int _key);
	CAnimation* FindAnimation(const wstring& _strName);
	CAnimation* FindAnimation(int _key);
	CAnimation* FindAnimationType(const wstring& _strType);
	void Play(const wstring& s, bool _bRepeat);
	void Play(int _key, bool _bRepeat);
	void PlayType(const wstring& _strName, bool _bRepeat);

public:
	void Update();
	void FinalUpdate();
	void Render(HDC hdc);
};

