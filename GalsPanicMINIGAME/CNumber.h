#pragma once
#include "CObject.h"
class CNumber :
    public CObject
{
    CLONE(CNumber)
private:
    int                 m_iNumber;      // 현재 숫자
    float               m_fScale;       // 숫자 이미지 배율
    vector<Image*>      m_vecNumbers;   // 0~9 이미지 배열

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
