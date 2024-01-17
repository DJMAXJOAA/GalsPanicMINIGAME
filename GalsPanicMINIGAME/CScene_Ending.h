#pragma once
#include "CScene.h"
class CScene_Ending :
    public CScene
{
public:
public:
    virtual void Update() override;
    virtual void Enter() override;
    virtual void Exit() override;

public:
    CScene_Ending();
    ~CScene_Ending();
};

