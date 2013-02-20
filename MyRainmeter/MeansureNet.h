#pragma once

#include "Meansure.h"

class CMeansureNet : public CMeansure
{
public:
	CMeansureNet(void);
	~CMeansureNet(void);

public:
	wstring GetMeansureType();
	void SetMeansureType(wstring type);
public:
	int m_Interface;
	int m_Cumulative;
};

