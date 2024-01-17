#pragma once

#define SINGLE(type) public: static type* GetInstance() {static type mgr; return &mgr;}

#define KEY_CHECK(key, state) CKeyMgr::GetInstance()->GetKeyState(key) == state
#define KEY_HOLD(key) KEY_CHECK(key, KEY_STATE::HOLD)
#define KEY_TAP(key) KEY_CHECK(key, KEY_STATE::TAP)	
#define KEY_AWAY(key) KEY_CHECK(key, KEY_STATE::AWAY)	
#define KEY_NONE(key) KEY_CHECK(key, KEY_STATE::NONE)
#define MOUSE_POS CKeyMgr::GetInstance()->GetMousePos()

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
	TITLE,
	START,
	ENDING,

	END,
};

enum class PEN_TYPE
{
	RED,
	GREEN,
	BLUE,
	END,
};

enum class BRUSH_TYPE
{
	HOLLOW,
	END,
};

enum class EVENT_TYPE
{
	CREATE_OBJECT,
	DELETE_OBJECT,
	SCENE_CHANGE,

	END,
};