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
	// ���� �Լ��� ȣ�� -> �̺�Ʈ �Ŵ����� ��� -> �̺�Ʈ ó�� -> �״��� �� ����
	void ChangeScene(SCENE_TYPE _eNext);

private:
	CSceneMgr();
	~CSceneMgr();

	friend class CEventMgr;
};

