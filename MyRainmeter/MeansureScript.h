#pragma once

#include "Meansure.h"

class CMeansureScript :	public CMeansure
{
public:
	CMeansureScript(void);
	~CMeansureScript(void);

public:
	wstring GetMeansureType();

public:
	wstring m_ScriptFile;
};

