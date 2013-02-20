#include "StdAfx.h"
#include "MeansureMemory.h"


CMeansureMemory::CMeansureMemory(void)
{
	m_Total = 0;
}


CMeansureMemory::~CMeansureMemory(void)
{
}

void CMeansureMemory::SetMeansureType( wstring Type )
{
	m_MeansureType = Type;
}

std::wstring CMeansureMemory::GetMeansureType()
{
	if (m_MeansureType.c_str() == NULL)
	{
		return NULL;
	}
	return m_MeansureType;
}
