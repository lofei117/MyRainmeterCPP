#pragma once

#include "Meansure.h"

class CMeansureCalc : public CMeansure
{
public:
	CMeansureCalc(void);
	~CMeansureCalc(void);

public:
	wstring GetMeansureType();

public:
	wstring m_Formula;
	int m_UpdateRandom;
	int m_LowBound;
	int m_HighBound;
};

