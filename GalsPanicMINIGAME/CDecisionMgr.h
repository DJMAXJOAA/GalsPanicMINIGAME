#pragma once

enum class KEY;
class CPlayer;
class CArea;

class CDecisionMgr
{
	SINGLE(CDecisionMgr);

private:
	CPlayer* pPlayer;
	CArea* pArea;
	list<POINT>::iterator itrPlayerPos; // 플레이어가 현재 몇번 인덱스에 있는지
	vector<list<POINT>::iterator> vecSave; // 이터레이터 저장

public:
	bool PlayerMovingPossible(KEY key);

public:
	CPlayer* GetPlayer() { return pPlayer; }
	CArea* GetArea() { return pArea; }
	list<POINT>::iterator GetPlayerAreaPoint() { return itrPlayerPos; }

public:
	void Init(CPlayer* player, CArea* area);
	void DrawInit();
	bool DrawCollide();
	void DrawEnd();

public:
	void Update();
	void MoveUpdate();
	void DrawUpdate();

private:
	CDecisionMgr();
	~CDecisionMgr();
};

