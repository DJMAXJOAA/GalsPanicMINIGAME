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
	// 맵에 데이터 만들고 등록
	// 각 클래스의 생성자에서 키에 맞는 Init() 실행
	CData* AddData = nullptr;
	if (_key >= 600) AddData = new FieldData(_key);
	else if (_key >= 500) AddData = new MonsterData(_key);
	else if (_key >= 400) AddData = new SkillData(_key);
	else if (_key >= 300) AddData = new ItemData(_key);
	else if (_key >= 200) AddData = new AnimatorData(_key);
	else if (_key >= 100) AddData = new AnimationData(_key);
	else if (_key >= 0)	 AddData = new GameData(_key);
	else assert(0);		// 오류검출
	
	m_mapDataList.insert(make_pair(_key, AddData));
	return AddData;
}

CData* CDataMgr::FindData(int _key)
{
	map<int, CData*>::iterator iter = m_mapDataList.find(_key);

	// 결과값 없으면 새로 생성하고 데이터 반환, 있으면 그대로 반환
	if (iter == m_mapDataList.end()) return CreateData(_key)->FindData();
	else return iter->second->FindData();
}

vector<CData*> CDataMgr::LoadDataRange(int _start, int _end)
{
	// 특정 id에서 특정 id까지의 데이터들을 담아서 벡터로 반환
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
		// 오류 검출 코드, 100의 배수로 입력받아야 함
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

