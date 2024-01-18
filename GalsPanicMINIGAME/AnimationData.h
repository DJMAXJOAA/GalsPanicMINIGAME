#pragma once

struct AnimationInfo
{
	Vec2				vLeftTop;		// �ؽ��� ���� ��ġ(Left Top)
	Vec2				vSliceSize;		// ���ۺ��� ������ �ڸ�����(Right Bottom)
	Vec2				vStep;			// �ִϸ��̼� ���� �����Ӱ��� ����
	Vec2				vOffset;		// ������ ���� ����
	float				fDuration;		// �ִϸ��̼� ���ӽð�
	int					iFrame;			// �ִϸ��̼� ��������?
	int					iEventFrame;		// �̺�Ʈ ������ (0�̸� �ִϸ��̼� �̺�Ʈ ����)
};

class AnimationData
{
public:
	wstring				m_strAnimationName;	// ������ �ִϸ��̼� �̸�
	wstring				m_strTexturePath;	// ������ ���� ���� ���
	AnimationInfo		m_AniInfo;			// �ִϸ��̼� ����

public:
	AnimationData(wstring name, wstring path, AnimationInfo info)
	{
		m_strAnimationName = name;
		m_strTexturePath = path;
		info = info;
	}
	~AnimationData() {}
};

