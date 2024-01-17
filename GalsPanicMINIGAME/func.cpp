#include "pch.h"
#include "func.h"

#include "CEventMgr.h"

void CreateObj(CObject* _pObj, GROUP_TYPE _eGroup)
{
	tEvent evn = {  };
	evn.eEvent = EVENT_TYPE::CREATE_OBJECT;
	evn.lParam = (DWORD_PTR)_pObj;
	evn.wParam = (DWORD_PTR)_eGroup;

	CEventMgr::GetInstance()->AddEvent(evn);
}

void DeleteObj(CObject* _pObj)
{
	tEvent evn = {  };
	evn.eEvent = EVENT_TYPE::DELETE_OBJECT;
	evn.lParam = (DWORD_PTR)_pObj;

	CEventMgr::GetInstance()->AddEvent(evn);
}

void ChangeScene(SCENE_TYPE _eNext)
{
	tEvent evn = {  };
	evn.eEvent = EVENT_TYPE::SCENE_CHANGE;
	evn.lParam = (DWORD_PTR)_eNext;

	CEventMgr::GetInstance()->AddEvent(evn);
}
