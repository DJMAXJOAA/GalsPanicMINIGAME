#pragma once

class CData
{
private:
	bool	m_bValid;	// ������ ���� ����

public:
	CData();
	virtual ~CData();

public:
	bool GetValid() { return m_bValid; }
};
