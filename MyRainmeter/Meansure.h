#pragma once

#include "RmControl.h"

// CMeansure

class CMeansure : public CRmControl
{
	DECLARE_DYNAMIC(CMeansure)

public:
	CMeansure();
	virtual ~CMeansure();

protected:
	DECLARE_MESSAGE_MAP()
};


