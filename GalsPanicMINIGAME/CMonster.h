#pragma once
#include "CObject.h"

class CTexture;

class CMonster :
    public CObject
{
private:
    int iSpeed;
    float fAngle;
    Vec2 fDirection;
    CTexture* pTex;
   
    CObject* pCollide;

public:
    int GetSpeed() { return iSpeed; }
    Vec2 GetDirection() { return fDirection; }

    void SetDirection(Vec2 _fDirection) { fDirection = _fDirection; }
    void SetCollide(CObject* _pCollide) { pCollide = _pCollide; }

public:
    virtual void Update();
    virtual void Render(HDC hdc);

public:
    virtual void OnCollisionEnter(CCollider* _pOther);

public:
    CMonster();
    ~CMonster();
};

