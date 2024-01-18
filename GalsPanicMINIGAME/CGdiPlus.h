#pragma once
#include "CResource.h"

class CGdiPlus :
    public CResource
{
private:
    Bitmap* m_pBitmap;

private:
    CGdiPlus();
    virtual ~CGdiPlus();

public:
    friend class CResMgr;

public:
    void Load(const wstring& _strFilePath);
    void Create(UINT _iWidth, UINT _iHeight);

public:
    UINT Width() { return m_pBitmap->GetWidth(); }
    UINT Height() { return m_pBitmap->GetHeight(); }

public:
    Bitmap* GetBitmap() { return m_pBitmap; }
};