#pragma once
#include "CScene.h"
class CScene_Title :
    public CScene
{
public:
    // virtual�� ������ �ʾƵ� �̹� �����Լ�����, ������ ���� ��������� �����ش�
    virtual void Enter();
    virtual void Exit();

public:
    CScene_Title();
    ~CScene_Title();
};

