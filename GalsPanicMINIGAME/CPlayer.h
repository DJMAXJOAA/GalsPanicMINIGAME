#pragma once
#include "CObject.h"

#include "CArea.h"

enum PLAYER_STATE
{
    MOVE, DRAW, DEAD,
};

enum PLAYER_DIRECTION
{
    LEFT, UP, RIGHT, DOWN,
};

class CPlayer :
    public CObject
{
private:
    int iState;
    int iDirection;
    int iSpeed;

public:
    int GetState() { return iState; }
    int GetDirection() { return iDirection; }
    int GetSpeed() { return iSpeed; }
    void SetState(int _iState) { iState = _iState; }

public:
    void Move();
    void Draw();

public:
    virtual void Update();
    virtual void Render(HDC hdc);

public:
    CPlayer();
    ~CPlayer();
};

