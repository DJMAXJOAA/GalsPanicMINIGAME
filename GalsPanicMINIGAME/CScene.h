#pragma once

class CObject;

class CScene
{
	vector<CObject*> arrObj[(UINT)GROUP_TYPE::END];
	wstring strName;

public:
	void AddObject(CObject* pObj, GROUP_TYPE eType) { arrObj[(UINT)eType].push_back(pObj); }
	void DeleteGroup(GROUP_TYPE _eTarget);
	void DeleteAll();

public:
	vector<CObject*>& GetGroupObject(GROUP_TYPE _eType) { return arrObj[(UINT)_eType]; } // 레퍼런스로 주되, 변경은 불가능하게 const

public:
	void SetName(const wstring& _strName) { strName = _strName; }
	const wstring& GetName() { return strName; }

	virtual void Enter() = 0;
	virtual void Exit() = 0;

public:
	virtual void Update();
	virtual void FinalUpdate(); // 마무리 작업(모두 업데이트 끝나고, 확정 후 render)
	void Render(HDC hdc);

public:
	CScene();
	virtual ~CScene();
};

