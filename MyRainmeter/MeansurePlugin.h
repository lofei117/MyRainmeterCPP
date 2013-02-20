#pragma once

#include "Meansure.h"

class CMeansurePlugin :	public CMeansure
{
public:
	CMeansurePlugin(void);
	~CMeansurePlugin(void);

public:
	virtual wstring GetMeansureType();

public:
	wstring m_Plugin;
};

