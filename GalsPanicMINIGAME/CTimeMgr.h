#pragma once
class CTimeMgr
{
	SINGLE(CTimeMgr);
private:
	LARGE_INTEGER liCurCount;
	LARGE_INTEGER liPrevCount;
	LARGE_INTEGER liFrequency;

	double dDT; // 한프레임 시간값
	double dAcc; // 누적 시간
	UINT iCallCount;
	UINT iFPS;

public:
	void Init();
	void Update();

public:
	double GetDT() { return dDT; }
	float GetfDT() { return (float)dDT; }

private:
	CTimeMgr();
	~CTimeMgr();
};

