#include "pch.h"
#include "CEventMgr.h"
#include "func.h"

#include "CSceneMgr.h"

#include "CObject.h"
#include "CScene.h"
#include "CPlayer.h"

CEventMgr::CEventMgr()
{
}

CEventMgr::~CEventMgr()
{
}

void CEventMgr::Update()
{
	// �̹� �����ӿ� ���� ������ ������Ʈ�� �ϴ� �����ֱ�
	SafeDeleteVec(m_vecDead);

	// ���� ó���� �̺�Ʈ�� �߰���Ű��, Ŭ����
	for (size_t i = 0; i < m_vecEarlyEvent.size(); i++)
	{
		m_vecEvent.insert(m_vecEvent.begin(), m_vecEarlyEvent[i]);
	}
	m_vecEarlyEvent.clear();

	// �ļ��� �̺�Ʈ�� �̺�Ʈ�� �߰���Ű��, Ŭ����
	for (size_t i = 0; i < m_vecLateEvent.size(); i++)
	{
		m_vecEvent.push_back(m_vecLateEvent[i]);
	}
	m_vecLateEvent.clear();

	// �̺�Ʈ ó��
	for (size_t i = 0; i < m_vecEvent.size(); i++)
	{
		Excute(m_vecEvent[i]);
	}
	m_vecEvent.clear();
}

void CEventMgr::Excute(const tEvent& _eve)
{
	switch (_eve.eEvent)
	{
	case EVENT_TYPE::CREATE_OBJECT:
	{
		// lParam :: Object Adress
		// wParam :: Group Type
		CObject* pNewObj = (CObject*)_eve.lParam;
		GROUP_TYPE eType = (GROUP_TYPE)_eve.wParam;

		CSceneMgr::GetInstance()->GetCurScene()->AddObject(pNewObj, eType);
		break;
	}
	case EVENT_TYPE::DELETE_OBJECT:
	{
		// lParam :: Object Adress
		// Object�� Dead ���·� ���� (�޸𸮴� ����������, ��Ȱ��ȭ)
		// ���� ���� ������Ʈ���� ��Ƶΰ�, �� ���� �����ӿ� �ϰ� ����(������Ʈ�鿡�� �غ��� �ð��� ��)
		CObject* pDeadObj = (CObject*)_eve.lParam;
		pDeadObj->SetDead();			// ���� �����Ӷ� dead ����(��Ȱ��ȭ)
		m_vecDead.push_back(pDeadObj);	// �ٴ��� �����Ӷ� ����
		break;
	}
	case EVENT_TYPE::SCENE_CHANGE:
	{
		// lParam :: Next Scene Type
		CSceneMgr::GetInstance()->ChangeScene((SCENE_TYPE)_eve.lParam);
		break;
	}
	case EVENT_TYPE::END:
		break;
	default:
		break;
	}
}
