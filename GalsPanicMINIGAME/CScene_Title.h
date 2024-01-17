#pragma once
#include "CScene.h"
class CScene_Title :
    public CScene
{
public:
    // virtual을 붙이지 않아도 이미 가상함수지만, 구분을 위해 명시적으로 적어준다
    virtual void Enter();
    virtual void Exit();

public:
    CScene_Title();
    ~CScene_Title();
};

