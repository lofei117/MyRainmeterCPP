#pragma once

#include "Meansure.h"

class CMeansureMemory :	public CMeansure
{
public:
	CMeansureMemory(void);
	~CMeansureMemory(void);

public:
	wstring GetMeansureType();
	void SetMeansureType(wstring Type);

public:
	int m_Total;

private:
	int m_MaxValue;
};

