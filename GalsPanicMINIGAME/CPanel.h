#pragma once
#include "CObject.h"
class CPanel :
    public CObject
{
private:
	Image* m_image;

	CLONE(CPanel)

public:
	CPanel(wstring _filename);
	~CPanel();

public:
	virtual void Render(HDC hdc) override;
	virtual void Update() override;
};

