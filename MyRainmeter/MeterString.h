#include "Meter.h"
#include "RmControl.h"
#include "ConstInfo.h"


// CMeterString

class CMeterString : public CMeter, public CRmControl
{
	//	DECLARE_SERIAL(CMeterString)

protected:
	//	CMeterString();
	CMFCPropertyGridCtrl* m_pPropWnd;
	LOGFONT m_CurFont;

public:	
	CMeterString(CXTPTaskPanelGroupItem* pItem, CMyRainmeterGraphView* pView);
	virtual ~CMeterString();

	// Attributes
public:
	CString m_Text;
	CString m_Prefix;
	CString m_Postfix;
	CString m_FontFace;
	int m_FontSize;
	CString m_FontColor;
	CString m_StringAligh;
	CString m_StringStyle;
	CString m_StringCase;
	CString m_StringEffect;
	CString m_FontEffectColor;
	CString m_ClipString;
	int m_ClipStringW;
	int m_ClipStringH;
	float m_Angle;
	int m_Percentual;
	int m_NumOfDecimals;
	int m_Scale;
	CString m_AutoScale;


public:
	virtual void Serialize(CArchive& ar);
	virtual void Draw(CDC* pDC, CXTPTaskPanel* taskPanel );
	virtual int GetMeterType();
	virtual void InitProperties(CMFCPropertyGridCtrl* pPropGridCtrl);
	virtual void PropertyChanged (CMFCPropertyGridProperty* pProp);
	virtual CString ToString() const;
	virtual void UpdateProperties();

protected:

private:

};


