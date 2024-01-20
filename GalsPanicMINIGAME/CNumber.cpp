#include "pch.h"
#include "CNumber.h"

#include "CPathMgr.h"

void CNumber::InitImages()
{
    wstring strFilePath = CPathMgr::GetInstance()->GetContentPath();
    wstring base = L"texture\\Number\\";

    // 0~9까지 숫자 이미지를 배열에 넣어줌
    for (int i = 0; i <= 9; ++i)
    {
        wstring temp = strFilePath + base + to_wstring(i) + L".png";
        m_vecNumbers[i] = new Image(temp.c_str());
    }
}

CNumber::CNumber(int _number, Vec2 _vPos, float _scale)
	: m_vecNumbers(10)
	, m_iNumber(_number)
	, m_fScale(_scale)
{
	SetPos(_vPos);
    InitImages();
}

CNumber::~CNumber()
{

}

void CNumber::Update()
{
}

void CNumber::Render(HDC hdc)
{
    Graphics graphics(hdc);

    Vec2 vPos = GetPos();
    string strNum = to_string(m_iNumber);
    int xOffset = 0;

    ImageAttributes imgAttr;
    ColorMatrix colorMatrix = {
        1.0f, 0.0f, 0.0f, 0.0f, 0.0f,
        0.0f, 1.0f, 0.0f, 0.0f, 0.0f,
        0.0f, 0.0f, 1.0f, 0.0f, 0.0f,
        0.0f, 0.0f, 0.0f, 1.0f, 0.0f,
        0.0f, 0.0f, 0.0f, 0.0f, 1.0f
    };
    imgAttr.SetColorMatrix(&colorMatrix);

    // 정수값을 숫자 이미지로 바꿔줌
    for (char c : strNum)
    {
        int digit = c - '0';
        if (digit >= 0 && digit <= 9)
        {
            Image* img = m_vecNumbers[digit];

            float scaledWidth = img->GetWidth() * m_fScale;
            float scaledHeight = img->GetHeight() * m_fScale;

            RectF destRect(vPos.x + xOffset, vPos.y, scaledWidth, scaledHeight);
            graphics.DrawImage(img, destRect, 0, 0, (REAL)img->GetWidth(), (REAL)img->GetHeight(), UnitPixel, &imgAttr);

            xOffset += (int)scaledWidth;  // 다음 숫자 이미지를 그릴 위치를 업데이트
        }
    }
}
