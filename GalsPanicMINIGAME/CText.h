#pragma once
#include "CObject.h"

class CPlayer;

enum class PRINT_TYPE
{
    NONE,
    POS,
    DIRECTION,
    STATE,
    POS_POINT,
};

class CText :
    public CObject
{
private:
    PRINT_TYPE txtType;
    wstring strText;
    CPlayer* pTarget;
    
public:
    void SetText(const wstring& _strText) { strText = _strText; }
    void SetType(PRINT_TYPE _txtType) { txtType = _txtType; }
    void SetTarget(CPlayer* _pTarget) { pTarget = _pTarget; }

public:
    virtual void Update();
    virtual void Render(HDC hdc);

public:
    CText();
    ~CText();
};

