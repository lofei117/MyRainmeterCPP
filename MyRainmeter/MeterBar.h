#pragma once

#include "Meter.h"
#include "RmControl.h"

// CMeterBar

class CMeterBar : public CMeter, public CRmControl
{
//	DECLARE_SERIAL(CMeterBar)

public:
	
	CMeterBar();
	virtual ~CMeterBar();

public:
	virtual void Serialize(CArchive& ar);
	virtual void Draw(CDC* pDC);

protected:

private:

};


