#pragma once
#include "CScene.h"
class CScene_Title :
    public CScene
{
public:
    // virtual�� ������ �ʾƵ� �̹� �����Լ�����, ������ ���� ��������� �����ش�
    virtual void Update() override;
    virtual void Enter() override;
    virtual void Exit() override;

public:
    CScene_Title();
    ~CScene_Title();
};

