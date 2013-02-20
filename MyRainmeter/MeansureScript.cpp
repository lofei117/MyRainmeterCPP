#include "StdAfx.h"
#include "MeansureScript.h"


CMeansureScript::CMeansureScript(void)
{
	m_MeansureType = _T("Script");
}


CMeansureScript::~CMeansureScript(void)
{
}

std::wstring CMeansureScript::GetMeansureType()
{
	return m_MeansureType;
}
