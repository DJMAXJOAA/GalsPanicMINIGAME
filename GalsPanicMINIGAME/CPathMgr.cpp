#include "pch.h"
#include "CPathMgr.h"

#include "CCore.h"

CPathMgr::CPathMgr()
	: szContentPath{}
{
}

CPathMgr::~CPathMgr()
{
}


void CPathMgr::Init()
{
	GetCurrentDirectory(255, szContentPath);
	int iLen = wcslen(szContentPath); // 경로의 길이

	// 상위 폴더로 ( bin\\content\\)
	for (int i = iLen - 1; i >= 0; i--) // 뒤에서부터 이름 읽어옴 -> 가장 상위경로만 가져옴
	{
		if ('\\' == szContentPath[i])
		{
			szContentPath[i] = '\0';
			break;
		}
	}
	wcscat_s(szContentPath, 255, L"\\bin\\content\\"); // 문자열 이어붙이기 -> 내 리소스들 넣을 폴더 경로 작성

}

