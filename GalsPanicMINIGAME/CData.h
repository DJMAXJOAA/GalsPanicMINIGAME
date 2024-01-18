#pragma once

class CData
{
private:
	bool	m_bValid;	// 데이터 존재 여부

public:
	CData();
	virtual ~CData();

public:
	bool GetValid() { return m_bValid; }
};
