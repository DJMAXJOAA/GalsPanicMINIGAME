#pragma once
class CPathMgr
{
	SINGLE(CPathMgr);
private:
	wchar_t	szContentPath[255]; // 경로 글자수 제한 255자

public:
	void Init();
	const wchar_t* GetContentPath() { return szContentPath; }

private:
	CPathMgr();
	~CPathMgr();
};

