#pragma once
class AnimatorData
{
public:
	wstring			m_strAnimatorName;	// 애니메이터 이름
	vector<int>		m_vecAnimation;		// 가져올 애니메이션 ID 명단

public:
	AnimatorData(wstring name, vector<int> v)
	{
		m_strAnimatorName = name;
		m_vecAnimation = v;
	}
	~AnimatorData() {}
};

