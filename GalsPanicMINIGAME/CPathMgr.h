#pragma once
class CPathMgr
{
	SINGLE(CPathMgr);
private:
	wchar_t	szContentPath[255]; // ��� ���ڼ� ���� 255��

public:
	void Init();
	const wchar_t* GetContentPath() { return szContentPath; }

private:
	CPathMgr();
	~CPathMgr();
};

