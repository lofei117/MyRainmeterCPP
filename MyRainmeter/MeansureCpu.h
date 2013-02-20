#pragma once
#include "Meansure.h"

class CMeansureCpu : public CMeansure
{
public:
	CMeansureCpu(void);
	~CMeansureCpu(void);

public:
	wstring GetMeansureType();

public:
	int m_Processor;

};

