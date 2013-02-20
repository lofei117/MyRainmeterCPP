#pragma once

#include "Meansure.h"

class CMeansureUptime :	public CMeansure
{
public:
	CMeansureUptime(void);
	~CMeansureUptime(void);

public:
	wstring GetMeansureType();

public:
	wstring m_Format;
	int m_AddDaysToHours;
};

