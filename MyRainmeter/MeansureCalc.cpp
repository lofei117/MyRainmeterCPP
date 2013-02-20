#include "StdAfx.h"
#include "MeansureCalc.h"


CMeansureCalc::CMeansureCalc(void)
{
	m_MeansureType = _T("Calc");
}


CMeansureCalc::~CMeansureCalc(void)
{
}

std::wstring CMeansureCalc::GetMeansureType()
{
	return m_MeansureType;
}
