#pragma once

class CConfigParser;


// CMeter

class CMeter
{	
	
// Constructor and Destructor
public:
	CMeter();
	virtual ~CMeter();

// public attributes
public:

// private attributes
private:

// protected attributes
protected:	
	
	// General Options
	CString m_MeterName;	// meter name
	CString m_MeterStyle;
	CString m_MeansureName;
	int m_X;		// location.x
	int m_Y;		// location.y
	int m_W;		// width
	int m_H;		// height 
	CString m_Hidden;	// property of hidden
	int m_UpdateDivider;	// update frequency of the meter

	CString m_OnUpdateAction;	// Action to execute when update the meter
	CString m_SolidColor;
	CString m_SolidColor2;
	int m_GradientAngle;
	CString m_BevelType;
	CString m_AntiAlias;
	CString m_DynamicVariables;
	CString m_TransformationMatrix;

	// General Image Options

	CString m_ImageCrop;
	CString m_Greyscale;//default 0£»
	CString m_ImageTint;// default 255,255,255,255
	int m_ImageAlpha;//default 255
	CString m_ImageFlip;// Default: None
	float m_ImageRotate;//default 0.0
	CString m_Tile;		// default 0;
	CString m_ColorMatrix;
	

	// Tooltip Options
	CString m_ToolTipText;
	CString m_ToolTipTitle;
	CString m_ToolTipIcon;
	CString m_ToolTipType;
	int m_ToolTipWidth;
	CString m_ToolTipHidden;	
	
	CMeter* m_RelativeMeter;
	CMeter* m_MeterStyleList;		// under construction

	// mouse actions
	unordered_map<wstring, wstring> m_MouseActions;

// public methods
public:
	// Set X
	void SetX(int x){ m_X = x; }
	// Get X
	int GetX(){ return m_X; }

	// Set Y
	void SetY(int y){ m_Y = y; }
	// Get Y
	int GetY(){ return m_Y; }

	// Set W
	void SetW(int w){ m_W = w; }
	// Get W
	int GetW(){ return m_W; }

	// Set H
	void SetH(int h){ m_H = h; }
	// Get H
	int GetH(){ return m_H; }

	// Set UpdateDivider
	void SetUpdateDivider(int updateDividert){	m_UpdateDivider = updateDividert;	}
	// Get UpdateDivider
	int GetUpdateDivider(){	return m_UpdateDivider;	}
	
	// Set meter's name
	void SetMeterName(CString meterName){ m_MeterName = meterName; }
	// Get the name of the meter
	CString GetMeterName(){ return m_MeterName; }

	// Set visible
	void SetHidden(CString hidden){ m_Hidden = hidden; }
	// Get visible
	CString IsHidden(){ return m_Hidden; }
	
	// Set MeterStyle
	void SetMeterStyle(CMeter* meterStyle){ m_MeterStyleList = meterStyle; }
	// Get MeterStyle
	CMeter* GetMeterStyle(){ return m_MeterStyleList; }

	// Get Meter type, virtual function. CMeter can not be instantiated
	virtual int GetMeterType()=0;

	// ParseData from the ini file with target section
	virtual void ParseData(CConfigParser* pConfigParser);

// private methods
private:

// protected methods
protected:

};


