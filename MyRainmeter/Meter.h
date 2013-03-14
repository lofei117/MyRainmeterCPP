#pragma once


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
	int m_X;		
	int m_Y;
	int m_W;
	int m_H;
	int m_Hidden;
	CString m_MeterName;
	
	CMeter* m_RelativeMeter;
	CMeter* m_MeterStyle;

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
	
	// Set meter's name
	void SetMeterName(CString meterName){ m_MeterName = meterName; }
	// Get the name of the meter
	CString GetMeterName(){ return m_MeterName; }

	// Set visible
	void SetHidden(bool hidden){ m_Hidden = hidden; }
	// Get visible
	bool IsHidden(){ return m_Hidden; }
	
	// Set MeterStyle
	void SetMeterStyle(CMeter* meterStyle){ m_MeterStyle = meterStyle; }
	// Get MeterStyle
	CMeter* GetMeterStyle(){ return m_MeterStyle; }

	// Get Meter type, virtual function. CMeter can not be instantiated
	virtual CString GetMeterType()=0;

// private methods
private:

// protected methods
protected:

};


