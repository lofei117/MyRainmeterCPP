#include "StdAfx.h"
#include "MeansureCpu.h"


CMeansureCpu::CMeansureCpu(void)
{
	m_MeansureType = _T("CPU");
	m_Processor = 0;
}


CMeansureCpu::~CMeansureCpu(void)
{
}

std::wstring CMeansureCpu::GetMeansureType()
{
	return m_MeansureType;
}
