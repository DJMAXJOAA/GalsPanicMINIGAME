#include "pch.h"
#include "CGdiPlus.h"

CGdiPlus::CGdiPlus()
    : m_pBitmap(nullptr)
{

}

CGdiPlus::~CGdiPlus()
{
    if (m_pBitmap)
    {
        delete m_pBitmap;
        m_pBitmap = nullptr;
    }
}

void CGdiPlus::Load(const wstring& _strFilePath)
{
    if (m_pBitmap)
    {
        delete m_pBitmap;
        m_pBitmap = nullptr;
    }

    m_pBitmap = new Bitmap(_strFilePath.c_str());

    if (m_pBitmap->GetLastStatus() != Ok)
    {
        delete m_pBitmap;
        m_pBitmap = nullptr;
    }
}

void CGdiPlus::Create(UINT _iWidth, UINT _iHeight)
{
    if (m_pBitmap)
    {
        delete m_pBitmap;
        m_pBitmap = nullptr;
    }

    m_pBitmap = new Bitmap(_iWidth, _iHeight, PixelFormat32bppARGB);

    if (m_pBitmap->GetLastStatus() != Ok)
    {
        delete m_pBitmap;
        m_pBitmap = nullptr;
    }
}
