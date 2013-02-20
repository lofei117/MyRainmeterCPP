#pragma once

#include "Meter.h"

// CMeterBar

class CMeterBar : public CMeter
{
	DECLARE_DYNAMIC(CMeterBar)

public:
	CMeterBar();
	virtual ~CMeterBar();

protected:
	DECLARE_MESSAGE_MAP()
};


