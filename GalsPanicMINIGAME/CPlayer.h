#pragma once
#include "CObject.h"

#include "CArea.h"

class CTexture;

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


public:
    int GetState() { return iState; }
    int GetDirection() { return iDirection; }
    int GetSpeed() { return iSpeed; }
    void SetState(int _iState) { iState = _iState; }

public:
    void Move();

public:
    virtual void Update();
    virtual void Render(HDC hdc);

public:
    CPlayer();
    ~CPlayer();
};

