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

public:
	bool PlayerMovingPossible(KEY key);
	bool PlayerDraw();

public:
	CPlayer* GetPlayer() { return pPlayer; }
	CArea* GetArea() { return pArea; }
	list<POINT>::iterator GetPlayerAreaPoint() { return itrPlayerPos; }

public:
	void Init(CPlayer* player, CArea* area);
	void Update();
	void MoveUpdate();
	void DrawUpdate();

private:
	CDecisionMgr();
	~CDecisionMgr();
};

