#include "pch.h"
#include "CKeyMgr.h"

#include "CPlayer.h"

#include "CCore.h"
#include "CDecisionMgr.h"


int arrVK[(int)KEY::LAST]
{
	VK_LEFT,
	VK_RIGHT,
	VK_UP,
	VK_DOWN,
	'Q',
	'W',
	'E',
	'R',
	'T',
	'Y',
	'U',
	'I',
	'O',
	'P',
	'A',
	'S',
	'D',
	'F',
	'G',
	'Z',
	'X',
	'C',
	'V',
	'B',
	VK_MENU,
	VK_LSHIFT,
	VK_SPACE,
	VK_CONTROL,
	VK_RETURN,
	VK_ESCAPE,
};

void CKeyMgr::Init()
{
	for (int i = 0; i < (int)KEY::LAST; ++i)
	{
		vecKey.push_back(tKeyInfo{ KEY_STATE::NONE, false, true });
	}
}

void CKeyMgr::Update()
{
	// 윈도우 활성시에만 키입력 상태
	HWND hMainWnd = CCore::GetInstance()->GetMainhWnd();
	HWND hWnd = GetFocus();

	/*if (hWnd == hMainWnd)*/
	if (hWnd != nullptr)
	{
		for (int i = 0; i < (int)KEY::LAST; i++)
		{
			// 키가 눌려있음
			if (GetAsyncKeyState(arrVK[i]) & 0x8000)
			{
				if (CDecisionMgr::GetInstance()->GetPlayer()->GetState() == MOVE)
				{
					SetKeyAvailability((KEY)i, CDecisionMgr::GetInstance()->PlayerMovingPossible((KEY)i));
				}

				// 이전에도 눌리고 있었음
				if (vecKey[i].bPrevPush)

				{
					vecKey[i].eState = KEY_STATE::HOLD;
				}
				// 이번에 새로 눌림
				else
				{
					vecKey[i].eState = KEY_STATE::TAP;
				}
				vecKey[i].bPrevPush = true;
			}

			// 키가 안눌러져있음
			else
			{
				// 이전엔 눌려져 있었음(지금 뗐음)
				if (vecKey[i].bPrevPush)
				{
					vecKey[i].eState = KEY_STATE::AWAY;
				}
				// 이전에도 떼져있었음
				else
				{
					vecKey[i].eState = KEY_STATE::NONE;
				}
				vecKey[i].bPrevPush = false;
			}
		}
	}

	// 윈도우 포커싱 해제 상태
	else
	{
		for (int i = 0; i < (int)KEY::LAST; ++i)
		{
			vecKey[i].bPrevPush = false;
			// 눌렀거나 누르고 있는 상태면 자동으로 떼지게 하기
			if (KEY_STATE::TAP == vecKey[i].eState
				|| KEY_STATE::HOLD == vecKey[i].eState)
			{
				vecKey[i].eState = KEY_STATE::AWAY;
			}
			// 떼지고 있는 상태라면, NONE으로 가게 하기
			if (KEY_STATE::AWAY == vecKey[i].eState)
			{
				vecKey[i].bKeyAvailability = true;
				vecKey[i].eState = KEY_STATE::NONE;
			}
		}
	}
}

CKeyMgr::CKeyMgr()
{
}

CKeyMgr::~CKeyMgr()
{
}