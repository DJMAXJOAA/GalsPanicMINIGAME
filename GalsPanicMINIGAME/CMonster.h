#pragma once
#include "CObject.h"

class CTexture;

class CMonster :
    public CObject
{
    int iSpeed;
    float fAngle;
    Vec2 fDirection;
    CTexture* pTex;

public:
    virtual void Update();
    virtual void Render(HDC hdc);

public:
    CMonster();
    ~CMonster();

private:
    void Move();
};

