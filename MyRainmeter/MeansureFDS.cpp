#include "StdAfx.h"
#include "MeansureFDS.h"


CMeansureFDS::CMeansureFDS(void)
{
	m_MeansureType = _T("FreeDiskSpace");
	m_Drive = _T("C:");
	m_Total = 0;
	m_Label = 0;
	m_Type = 0;
	m_IgnoreRemovable = 1;
	m_DiskQuota = 1;
}


CMeansureFDS::~CMeansureFDS(void)
{
}

std::wstring CMeansureFDS::GetMeansureType()
{
	return m_MeansureType;
}
