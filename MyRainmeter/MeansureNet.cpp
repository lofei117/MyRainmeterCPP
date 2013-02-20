#include "StdAfx.h"
#include "MeansureNet.h"


CMeansureNet::CMeansureNet(void)
{
	m_Interface = 0;
	m_Cumulative = 0;
}


CMeansureNet::~CMeansureNet(void)
{
}

std::wstring CMeansureNet::GetMeansureType()
{
	if (m_MeansureType.c_str() == NULL)
	{
		return NULL;
	}
	return m_MeansureType;
}

void CMeansureNet::SetMeansureType( wstring type )
{
	m_MeansureType = type;
}
