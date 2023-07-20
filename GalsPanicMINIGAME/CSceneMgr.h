#pragma once

class CScene;

class CSceneMgr
{
	SINGLE(CSceneMgr);
private:
	CScene* arrScene[(UINT)SCENE_TYPE::END];
	CScene* pCurScene;

public:
	void Init();
	void Update();
	void Render(HDC hdc);

private:
	CSceneMgr();
	~CSceneMgr();
};

