#include "pch.h"
#include "CDataMgr.h"

#include "GameData.h"
#include "AnimationData.h"
#include "AnimatorData.h"
#include "ItemData.h"
#include "SkillData.h"
#include "MonsterData.h"
#include "FieldData.h"

CDataMgr::CDataMgr()
	: m_mapDataList{}
{
}

CDataMgr::~CDataMgr()
{
	SafeDeleteMap(m_mapDataList);
}

CData* CDataMgr::CreateData(int _key)
{
	// �ʿ� ������ ����� ���
	// �� Ŭ������ �����ڿ��� Ű�� �´� Init() ����
	CData* AddData = nullptr;
	if (_key >= 600) AddData = new FieldData(_key);
	else if (_key >= 500) AddData = new MonsterData(_key);
	else if (_key >= 400) AddData = new SkillData(_key);
	else if (_key >= 300) AddData = new ItemData(_key);
	else if (_key >= 200) AddData = new AnimatorData(_key);
	else if (_key >= 100) AddData = new AnimationData(_key);
	else if (_key >= 0)	 AddData = new GameData(_key);
	else assert(0);		// ��������
	
	m_mapDataList.insert(make_pair(_key, AddData));
	return AddData;
}

CData* CDataMgr::FindData(int _key)
{
	map<int, CData*>::iterator iter = m_mapDataList.find(_key);

	// ����� ������ ���� �����ϰ� ������ ��ȯ, ������ �״�� ��ȯ
	if (iter == m_mapDataList.end()) return CreateData(_key)->FindData();
	else return iter->second->FindData();
}

vector<CData*> CDataMgr::LoadDataRange(int _start, int _end)
{
	// Ư�� id���� Ư�� id������ �����͵��� ��Ƽ� ���ͷ� ��ȯ
	vector<CData*> dataList;

	for (int i = _start; i <= _end; ++i) {
		CData* data = FindData(i);
		if (!data->GetValid()) {
			dataList.push_back(data);
		}
	}

	return dataList;
}

vector<CData*> CDataMgr::LoadAllData(int _number)
{
	if (_number % 100 != 0)
	{
		// ���� ���� �ڵ�, 100�� ����� �Է¹޾ƾ� ��
		assert(0);
	}
	
	vector<CData*> dataList;
	
	int start = _number;
	int end = _number + 99;

	for (int i = start; i <= end; ++i) {
		CData* data = FindData(i);
		if (!data->GetValid()) {
			break;
		}
		dataList.push_back(data);
	}

	return dataList;
}
