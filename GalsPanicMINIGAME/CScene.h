#pragma once

class CObject;

class CScene
{
	vector<CObject*> arrObj[(UINT)GROUP_TYPE::END];
	wstring strName;

protected:
	void AddObject(CObject* pObj, GROUP_TYPE eType) { arrObj[(UINT)eType].push_back(pObj); }

public:
	void SetName(const wstring& _strName) { strName = _strName; }
	const wstring& GetName() { return strName; }

	virtual void Enter() = 0;
	virtual void Exit() = 0;

public:
	void Update();
	void Render(HDC hdc);

public:
	CScene();
	virtual ~CScene();
};

