#pragma once
class AnimatorData
{
public:
	wstring			m_strAnimatorName;	// �ִϸ����� �̸�
	vector<int>		m_vecAnimation;		// ������ �ִϸ��̼� ID ���

public:
	AnimatorData(wstring name, vector<int> v)
	{
		m_strAnimatorName = name;
		m_vecAnimation = v;
	}
	~AnimatorData() {}
};

