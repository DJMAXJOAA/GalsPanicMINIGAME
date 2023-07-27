#pragma once

enum class KEY;
class CPlayer;
class CArea;

struct POINT_UNIQUE
{
	bool operator() (const POINT& a, const POINT& b) const
	{
		return (a.x == b.x && a.y == b.y);
	}
};

class CDecisionMgr
{
	SINGLE(CDecisionMgr);

private:
	CPlayer* pPlayer;
	CArea* pArea;
	list<POINT>::iterator itrPlayerPos; // �÷��̾ ���� ��� �ε����� �ִ���
	vector<list<POINT>::iterator> vecSave; // ���ͷ����� ����
	KEY lastKEY;

	int check = 1;

public:
	bool PlayerMovingPossible(KEY key);

public:
	CPlayer* GetPlayer() { return pPlayer; }
	CArea* GetArea() { return pArea; }
	list<POINT>::iterator GetPlayerAreaPoint() { return itrPlayerPos; }
	int GetCheck() { return check; }

public:
	void Init(CPlayer* player, CArea* area);
	void DrawInit();
	bool DrawCollide();
	bool DrawStartPossible(KEY key);
	void DrawEnd();
	void DrawCollideDead();

public:
	void Update();
	void MoveUpdate();
	void DrawUpdate();
	void DeadUpdate();

private:
	CDecisionMgr();
	~CDecisionMgr();
};

