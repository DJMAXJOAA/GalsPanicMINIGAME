#pragma once
#include "CObject.h"
class CNumber :
    public CObject
{
    CLONE(CNumber)
private:
    int                 m_iNumber;      // ���� ����
    float               m_fScale;       // ���� �̹��� ����
    vector<Image*>      m_vecNumbers;   // 0~9 �̹��� �迭

private:
    void InitImages();

public:
    void SetNumber(int _number) { m_iNumber = _number; }

public:
    CNumber(int _number, Vec2 _vPos, float _scale);
    virtual ~CNumber();

public:
    virtual void Update() override;
    virtual void Render(HDC hdc) override;
};
