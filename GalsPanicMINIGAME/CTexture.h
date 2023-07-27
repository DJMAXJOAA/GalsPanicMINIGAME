#pragma once
#include "CResource.h"
class CTexture :
    public CResource
{
private:
    HDC     hDC;
    HBITMAP hBit;
    BITMAP  BitInfo;

public:
    void Load(const wstring& _strFilePath);

public:
    UINT Width() { return BitInfo.bmWidth; }
    UINT Height() { return BitInfo.bmHeight; }
    HDC GetDC() { return hDC; }

public:
    CTexture();
    ~CTexture();
};

