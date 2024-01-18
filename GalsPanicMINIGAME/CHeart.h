#pragma once
#include "CObject.h"
class CHeart :
    public CObject
{
private:
	int		m_iHP;
	int		m_iMaxHP;
	int		m_iWidth;

	vector<Image*>	m_vecImages;

	CLONE(CHeart)

public:
	CHeart(int health);
	~CHeart();

public:
	void ReduceHP();

public:
	virtual void Render(HDC hdc) override;
	virtual void Update() override;
};

