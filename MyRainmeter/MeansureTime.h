#pragma once

#include "Meansure.h"

class CMeansureTime : public CMeansure
{
public:
	CMeansureTime(void);
	~CMeansureTime(void);

public:
	wstring GetMeansureType();

public:
	wstring m_Format;
	wstring m_TimeStamp;
	wstring m_TimeZone;
	int m_DayLightSavingTime;
};

