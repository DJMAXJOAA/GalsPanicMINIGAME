#pragma once

class CScene;

class CSceneMgr
{
	SINGLE(CSceneMgr);
private:
	CScene* arrScene[(UINT)SCENE_TYPE::END];
	CScene* pCurScene;

public:
	CScene* GetCurScene() { return pCurScene; }

public:
	void Init();
	void Update();
	void Render(HDC hdc);

private:
	// 전역 함수로 호출 -> 이벤트 매니저에 등록 -> 이벤트 처리 -> 그다음 씬 변경
	void ChangeScene(SCENE_TYPE _eNext);

private:
	CSceneMgr();
	~CSceneMgr();

	friend class CEventMgr;
};

