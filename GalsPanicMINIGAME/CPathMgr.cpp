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
	int iLen = wcslen(szContentPath); // ����� ����

	// ���� ������ ( bin\\content\\)
	for (int i = iLen - 1; i >= 0; i--) // �ڿ������� �̸� �о�� -> ���� ������θ� ������
	{
		if ('\\' == szContentPath[i])
		{
			szContentPath[i] = '\0';
			break;
		}
	}
	wcscat_s(szContentPath, 255, L"\\bin\\content\\"); // ���ڿ� �̾���̱� -> �� ���ҽ��� ���� ���� ��� �ۼ�

}

