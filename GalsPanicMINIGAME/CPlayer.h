#pragma once
#include "CObject.h"

#include "CArea.h"

enum class PLAYER_STATE
{
    MOVE, DRAW, RETRY,
};

enum class PLAYER_DIRECTION
{
    LEFT, UP, RIGHT, DOWN,
};

class CPlayer :
    public CObject
{
private:
    int iState;
    int iDirection;
    CArea* pArea;

public:
    int GetState() { return iState; }
    int GetDirection() { return iDirection; }
    void SetArea(CArea* _pArea) { pArea = _pArea; }
    void SetState(PLAYER_STATE _iState) { iState = (int)_iState; }

public:
    void Move();
    void Collide();

public:
    virtual void Update();
    virtual void Render(HDC hdc);

public:
    CPlayer();
    ~CPlayer();
};

