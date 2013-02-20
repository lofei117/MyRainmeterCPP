#pragma once

#include "Meansure.h"

class CMeansureFDS : public CMeansure
{
public:
	CMeansureFDS(void);
	~CMeansureFDS(void);

public:
	wstring GetMeansureType();

public:
	wstring m_Drive;
	int m_Total;
	int m_Label;
	int m_Type;
	int m_IgnoreRemovable;
	int m_DiskQuota;

private:
	int m_MaxValue;

};

