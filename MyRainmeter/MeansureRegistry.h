#pragma once

#include "Meansure.h"

class CMeansureRegistry : public CMeansure
{
public:
	CMeansureRegistry(void);
	~CMeansureRegistry(void);

public:
	wstring GetMeansureType();

public:
	wstring m_RegHKey;
	wstring m_RegKey;
	wstring m_RegValue;
};

