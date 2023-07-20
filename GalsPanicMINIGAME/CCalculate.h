#pragma once

class CObject;

class CCalculateMgr
{
	SINGLE(CCalculateMgr);
public:
	bool OnCollisionRead(Vec2 v1, Vec2 v2);

private:
	CCalculateMgr();
	~CCalculateMgr();
};

