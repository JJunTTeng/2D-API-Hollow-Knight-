#pragma once

class CBase
{
private:
	static UINT g_NextID;

private:	
	wstring		m_Name;
	const UINT	m_ID;

public:
	// inline 키워드 or 헤더에 함수가 구현된 경우 ==> inline 함수
	// 코드가 간결, 사용 빈도가 높을 때
	// Get, Set 류 함수들
	void SetName(const wstring& _Name) { m_Name = _Name; }
	const wstring& GetName() { return m_Name; }
	UINT GetID() { return m_ID; }
	void operator =(const CBase& _Origin) { m_Name = _Origin.m_Name; }

public:
	CBase();
	CBase(const CBase& _Origin);
	virtual ~CBase();
};

