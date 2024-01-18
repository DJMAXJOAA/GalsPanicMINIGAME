#pragma once

class CData;

class CDataMgr
{
	SINGLE(CDataMgr);
private:
	map<int, CData*>		m_mapDataList;	// 데이터 검색을 위한 해시맵

private:
	CDataMgr();
	~CDataMgr();

public:
	CData* CreateData(int _key);
	CData* FindData(int _key);
	vector<CData*> LoadDataRange(int _start, int _end);
	vector<CData*> LoadAllData(int _number);
};

