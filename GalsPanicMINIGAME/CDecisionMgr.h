#pragma once

enum class KEY;
class CPlayer;
class CArea;
class CMonster;

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
	vector<CMonster*> vecMonsters;
	list<POINT>::iterator itrPlayerPos; // 플레이어가 현재 몇번 인덱스에 있는지
	vector<list<POINT>::iterator> vecSave;
	list<POINT> renewPoint;
	KEY lastKEY;

private:
	int			m_iCheck = 0;
	float		m_fTimeCount;

public:
	bool PlayerMovingPossible(KEY key);

public:
	CPlayer* GetPlayer() { return pPlayer; }
	CArea* GetArea() { return pArea; }
	list<POINT>::iterator GetPlayerAreaPoint() { return itrPlayerPos; }
	int GetTimeScore() { return (int)m_fTimeCount; }
	int GetCheck() { return m_iCheck; }

	void SetTimeScore(int score) { m_fTimeCount = score; }

public:
	void Init();
	void Init(CPlayer* player, CArea* area, vector<CMonster*> monsters);
	void DrawInit();
	bool DrawCollide();
	bool DrawStartPossible(KEY key);
	void DrawEnd();
	void DrawCollideDead();
	bool MonsterWallCheck(CMonster* monster, int left_right);
	void MonsterDeadCheck();

public:
	void Update();
	void MoveUpdate();
	void DrawUpdate();
	void DeadUpdate();
	void MonsterUpdate();

private:
	void CheckTimeScore();

private:
	CDecisionMgr();
	~CDecisionMgr();
};

