#pragma once

#define SINGLE(type) public: static type* GetInstance() {static type mgr; return &mgr;}

#define fDT CTimeMgr::GetInstance()->GetfDT()
#define DT CTimeMgr::GetInstance()->GetDT()
#define PI 3.14159
#define RADIAN(value) value * PI / 180

enum class GROUP_TYPE
{
	DEFAULT,
	PLAYER,
	MISSILE,
	MONSTER,

	END = 32,
};

enum class SCENE_TYPE
{
	TOOL,
	START,
	STAGE_01,
	STAGE_02,

	END,
};