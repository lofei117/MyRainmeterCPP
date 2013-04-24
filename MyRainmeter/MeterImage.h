#pragma once

#include "Meter.h"
#include "RmControl.h"
#include "ConstInfo.h"


// CMeterBar

class CMeterImage : public CMeter, public CRmControl
{
	//	DECLARE_SERIAL(CMeterBar)

protected:
//	CMeterImage();

public:	
	CMeterImage(CXTPTaskPanelGroupItem* pItem, CMyRainmeterGraphView* pView);
	virtual ~CMeterImage();

	// Attributes
public:
	CString m_MeansureName;
	CString m_ImageName;
	CString m_Path;
	CString m_PreserveAspectRatio;
	CString m_ScaleMargins;

public:
	virtual void Serialize(CArchive& ar);
	virtual void Draw(CDC* pDC, CXTPTaskPanel* taskPanel );
	virtual int GetMeterType();
	virtual void InitProperties(CMFCPropertyGridCtrl* pPropGridCtrl);
	virtual void PropertyChanged (CMFCPropertyGridProperty* pProp);
	virtual CString ToString() const;
	virtual void UpdateProperties();
	virtual void ParseData(CConfigParser* pConfigParser);

protected:

private:

};


