#include "StdAfx.h"
#include "MeansureTime.h"


CMeansureTime::CMeansureTime(void)
{
	m_MeansureType = _T("Time");
	m_Format = _T("%H:%M:%S");
	m_TimeZone = _T("local");
	m_DayLightSavingTime = 1;
}


CMeansureTime::~CMeansureTime(void)
{
}

wstring CMeansureTime::GetMeansureType()
{
	return m_MeansureType;
}
