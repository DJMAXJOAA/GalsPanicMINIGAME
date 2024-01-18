#pragma once
class CResource
{
private:
	wstring strKey;				// 리소스 키
	wstring strRelativePath;	// 리소스 경로

public:
	void SetKey(const wstring& _strKey) { strKey = _strKey; }
	void SetRelativePath(const wstring& _strPath) { strRelativePath = _strPath; }

	const wstring& GetKey() { return strKey; }
	const wstring& GetRelativePath() { return strRelativePath; }

public:
	CResource();
	virtual ~CResource();
};

