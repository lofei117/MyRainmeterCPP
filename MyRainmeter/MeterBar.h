#pragma once

#include "Meter.h"
#include "RmControl.h"
#include "ConstInfo.h"

// CMeterBar

class CMeterBar : public CMeter, public CRmControl
{
//	DECLARE_SERIAL(CMeterBar)

protected:
	CMeterBar();

public:	
	CMeterBar(CXTPTaskPanelGroupItem* pItem);
	virtual ~CMeterBar();

public:
	virtual void Serialize(CArchive& ar);
	virtual void Draw(CDC* pDC, CXTPTaskPanel* taskPanel );
	virtual int GetMeterType();
	virtual void FillProperties(CMFCPropertyGridCtrl* pPropGridCtrl);

protected:

private:

};


