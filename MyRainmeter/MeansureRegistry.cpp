#include "StdAfx.h"
#include "MeansureRegistry.h"


CMeansureRegistry::CMeansureRegistry(void)
{
	m_MeansureType = _T("Registry");
}


CMeansureRegistry::~CMeansureRegistry(void)
{
}

std::wstring CMeansureRegistry::GetMeansureType()
{
	return m_MeansureType;
}
