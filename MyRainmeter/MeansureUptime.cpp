#include "StdAfx.h"
#include "MeansureUptime.h"


CMeansureUptime::CMeansureUptime(void)
{
	m_MeansureType = _T("Uptime");
	m_Format = _T("%4!i!d %3!i!:%2!02i!");
	m_AddDaysToHours = 1;
}


CMeansureUptime::~CMeansureUptime(void)
{
}

std::wstring CMeansureUptime::GetMeansureType()
{
	return m_MeansureType;
}
