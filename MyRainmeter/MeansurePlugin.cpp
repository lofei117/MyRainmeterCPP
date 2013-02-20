#include "StdAfx.h"
#include "MeansurePlugin.h"


CMeansurePlugin::CMeansurePlugin(void)
{
	m_MeansureType = _T("Plugin");
}


CMeansurePlugin::~CMeansurePlugin(void)
{
}

std::wstring CMeansurePlugin::GetMeansureType()
{
	return m_MeansureType;
}
