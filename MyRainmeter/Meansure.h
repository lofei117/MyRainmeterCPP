#pragma once

#include "RmControl.h"

// CMeansure

class CMeansure : public CWnd
{
	DECLARE_DYNAMIC(CMeansure)

// Constructor and Destructor 
public:
	CMeansure();
	virtual ~CMeansure();

// public methods
public:
	virtual wstring GetMeansureType()=0;
	

// private methods
private:

// protected methods
protected:

// public attributes
public:
	// InvertMeansure Used/Available 
	int m_InvertMeansure;
	int m_Disabled;
	int m_UpdateDivider;
	double m_MaxValue;
	double m_MinValue;
	int m_AverageSize;
	int m_DynamicVariables;

	bool m_IfAbove;
	int m_AboveValue;
	wstring m_AboveAction;

	bool m_IfBelow;
	int m_BelowValue;
	wstring m_BelowAction;

	bool m_IfEqual;
	int m_EqualValue;
	wstring m_EqualAction;

	int m_IsRegExpSubstitute;
	wstring m_Substitute;

// private attributes
private:
	
// protected attributes
protected:
	// MeansureType
	wstring m_MeansureType;
	

protected:
	DECLARE_MESSAGE_MAP()
};


