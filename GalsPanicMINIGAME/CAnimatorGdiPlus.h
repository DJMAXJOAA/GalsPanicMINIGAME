#pragma once

class CObject;
class CGdiPlus;
class CAnimationGdiPlus;

class CAnimatorGdiPlus
{
private:
	CObject*					m_pOwner;		// 애니메이션 소유 오브젝트
	bool						m_bRepeat;		// 반복재생 여부
	bool						m_eventTrigger;	// 이벤트 중복 전송 방지
	int							m_iID;			// 데이터 아이디

	map<wstring, CAnimationGdiPlus*>	m_mapAnim;
	CAnimationGdiPlus*					m_pCurAnim;

public:
	CAnimatorGdiPlus();
	CAnimatorGdiPlus(const CAnimatorGdiPlus& _origin);
	~CAnimatorGdiPlus();

	friend class CObject;

public:
	void AnimationEvent(CObject* _pObj);
	void AnimationEnd(CObject* _pObj);

public:
	int GetID() { return m_iID; }
	CAnimationGdiPlus* GetAnimation() { return m_pCurAnim; }
	CObject* GetObj() { return m_pOwner; }

public:
	void CreateAnimation(const wstring& _strName, CGdiPlus* _pTex, Vec2 _vLeftTop, Vec2 _vSliceSize, Vec2 _vStep, float _fDuration, UINT _iFrameCount, int _id, int _eventID);
	void CreateAnimation(int _key);
	CAnimationGdiPlus* FindAnimation(const wstring& _strName);
	CAnimationGdiPlus* FindAnimation(int _key);
	void Play(const wstring& _strName, bool _bRepeat);
	void Play(int _key, bool _bRepeat);

public:
	void Update();
	void FinalUpdate();
	void Render(HDC hdc);
};

