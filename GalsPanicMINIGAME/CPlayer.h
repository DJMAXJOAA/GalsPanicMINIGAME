#pragma once
#include "CObject.h"

#include "CArea.h"

class CTexture;
class CHeart;

enum PLAYER_STATE
{
    MOVE, DRAW, DEAD,
};

enum PLAYER_DIRECTION
{
    LEFT, UP, RIGHT, DOWN, NONE
};

class CPlayer :
    public CObject
{
private:
    int iState;
    int iDirection;
    int iSpeed;
    CTexture* pTex;
    CHeart* pHeart;

    bool bDead;

public:
    int GetState() { return iState; }
    int GetDirection() { return iDirection; }
    int GetSpeed() { return iSpeed; }
    bool GetDead() const { return bDead; }

    void SetDead(bool _bDead) { bDead = _bDead; }
    void SetState(int _iState) { iState = _iState; }

public:
    void Move();

public:
    virtual void OnCollisionEnter(CCollider* _pOther);
    void GetDamaged();

public:
    virtual void Update();
    virtual void Render(HDC hdc);

public:
    CPlayer(CHeart* heart);
    virtual ~CPlayer();

    CLONE(CPlayer);
};

