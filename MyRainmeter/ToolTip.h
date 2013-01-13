#pragma once

#include "RmControl.h"
#include "ConstInfo.h"

// ToolTip

class CToolTip : public CRmControl
{
	DECLARE_DYNAMIC(CToolTip)

// Constructor and Destructor
public:
	CToolTip();
	virtual ~CToolTip();

// public attributes
public:

// private attributes
private:	
	CString m_ToolTipText;
	CString m_ToolTipTitle;
	ToolTipIcon m_ToolTipIcon;
	ToolTipType m_ToolTipType;
	unsigned m_ToolTipWidth;
	bool m_ToolTipHidden;

// protected attributes
protected:
	

// public methods
public:
	// Set tooltip text
	void SetToolTipText(CString toolTipText){ m_ToolTipText = toolTipText; }
	// Get tooltip text
	CString GetToolTipText(){ return m_ToolTipText; }

	// Set tooltip title
	void SetToolTipTitle(CString toolTipTitle){ m_ToolTipTitle = toolTipTitle; }
	// Get tooltip title
	CString GetToolTipTitle(){ return m_ToolTipTitle; }

	// Set tooltip icon
	void SetToolTipIcon(ToolTipIcon toolTipIcon) { m_ToolTipIcon = toolTipIcon; }
	// Get tooltip icon
	ToolTipIcon GetToolTipIcon(){ return m_ToolTipIcon; }

	// Set tooltip type
	void SetToolTipType(ToolTipType toolTipType) { m_ToolTipType = toolTipType; }
	// Get tooltip type
	ToolTipType GetToolTipType(){ return m_ToolTipType; }

	// Set tooltip width
	void SetToolTipWidth(unsigned toolTipWidth) { m_ToolTipWidth = toolTipWidth; }
	// Get tooltip width
	unsigned GetToolTipWidth(){ return m_ToolTipWidth; }

	// Set tooltip visible
	void SetToolTipHidden(bool hidden){ m_ToolTipHidden = hidden; }
	// Get tooltip visible
	bool IsToolTipHidden(){ return m_ToolTipHidden; }

// private methods
private:

// protected methods
protected:

protected:
	DECLARE_MESSAGE_MAP()
};


