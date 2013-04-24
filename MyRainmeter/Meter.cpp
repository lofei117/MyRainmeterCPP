// Meter.cpp : 实现文件
//

#include "stdafx.h"
#include "MyRainmeter.h"
#include "Meter.h"
#include "ConfigParser.h"


// CMeter


CMeter::CMeter()
{
	// General Options
	m_X = m_Y = 0;
	m_Hidden = L"0";
	m_UpdateDivider=1;
	m_SolidColor=L"0,0,0,0";
	m_GradientAngle=0;
	m_BevelType=L"0";
	m_AntiAlias=L"0";
	m_DynamicVariables=L"0";
	m_TransformationMatrix=L"1;0;0;1;0;0";

	// General Image Options
	m_ImageCrop=L"";	
	m_Greyscale=L"0";
	m_ImageTint=L"255,255,255,255";
	m_ImageAlpha=255;
	m_ImageFlip=L"None";
	m_ImageRotate=0.0;
	m_Tile=L"0";

	// Mouse Click Actions
	m_MouseActions.insert(std::make_pair(L"LeftMouseDownAction", L""));
	m_MouseActions.insert(std::make_pair(L"LeftMouseUpAction", L""));
	m_MouseActions.insert(std::make_pair(L"RightMouseDownAction", L""));
	m_MouseActions.insert(std::make_pair(L"RightMouseUpAction", L""));
	m_MouseActions.insert(std::make_pair(L"MiddleMouseDownAction", L""));
	m_MouseActions.insert(std::make_pair(L"MiddleMouseUpAction", L""));
	m_MouseActions.insert(std::make_pair(L"LeftMouseDoubleClickAction", L""));
	m_MouseActions.insert(std::make_pair(L"RightMouseDoubleClickAction", L""));
	m_MouseActions.insert(std::make_pair(L"MiddleMouseDoubleClickAction", L""));
	m_MouseActions.insert(std::make_pair(L"X1MouseDownAction", L""));
	m_MouseActions.insert(std::make_pair(L"X2MouseDownAction", L""));
	m_MouseActions.insert(std::make_pair(L"X1MouseUpAction", L""));
	m_MouseActions.insert(std::make_pair(L"X2MouseUpAction", L""));
	m_MouseActions.insert(std::make_pair(L"X1MouseDoubleClickAction", L""));
	m_MouseActions.insert(std::make_pair(L"X2MouseDoubleClickAction", L""));
	// Mouse Hover Actions
	m_MouseActions.insert(std::make_pair(L"MouseOverAction", L""));
	m_MouseActions.insert(std::make_pair(L"MouseLeaveAction", L""));
	// Mouse Wheel Scroll Actions
	m_MouseActions.insert(std::make_pair(L"MouseScrollDownAction", L""));
	m_MouseActions.insert(std::make_pair(L"MouseScrollUpAction", L""));
	m_MouseActions.insert(std::make_pair(L"MouseScrollLeftAction", L""));
	m_MouseActions.insert(std::make_pair(L"MouseScrollRightAction", L""));	

}

CMeter::~CMeter()
{
	if (m_MeterStyleList != NULL)
	{
		delete m_MeterStyleList;
	}
	if (m_RelativeMeter != NULL)
	{
		delete m_RelativeMeter;
	}
}

void CMeter::ParseData( CConfigParser* pConfigParser )
{	
	// Parse General Meter Options
	m_X = pConfigParser->GetValueInt(m_MeterName, L"X");
	m_Y = pConfigParser->GetValueInt(m_MeterName, L"Y");
	m_W = pConfigParser->GetValueInt(m_MeterName, L"W");
	m_H = pConfigParser->GetValueInt(m_MeterName, L"H");
	m_MeansureName = pConfigParser->GetValueString(m_MeterName, L"MeansureName");
	m_Hidden = pConfigParser->GetValueString(m_MeterName, L"Hidden");
	m_UpdateDivider = pConfigParser->GetValueInt(m_MeterName, L"UpdateDivider");
	m_OnUpdateAction = pConfigParser->GetValueString(m_MeterName, L"OnUpdateAction");
	m_SolidColor = pConfigParser->GetValueString(m_MeterName, L"SolidColor");
	m_SolidColor2 = pConfigParser->GetValueString(m_MeterName, L"SolidColor2");
	m_GradientAngle = pConfigParser->GetValueInt(m_MeterName, L"GradientAngle");
	m_BevelType = pConfigParser->GetValueString(m_MeterName, L"BevelType");
	m_AntiAlias = pConfigParser->GetValueString(m_MeterName, L"AntiAlias");
	m_DynamicVariables = pConfigParser->GetValueString(m_MeterName, L"DynamicVariables");
	m_TransformationMatrix = pConfigParser->GetValueString(m_MeterName, L"TransformationMaxtix");
	m_MeterStyle = pConfigParser->GetValueString(m_MeterName, L"MeterStyle");
	
	// Parse Image Options
	m_ImageCrop = pConfigParser->GetValueString(m_MeterName, L"ImageCrop");
	m_Greyscale = pConfigParser->GetValueString(m_MeterName, L"Greyscale");
	m_ImageTint = pConfigParser->GetValueString(m_MeterName, L"ImageTine");
	m_ImageFlip = pConfigParser->GetValueString(m_MeterName, L"ImageFlip");
	m_ImageRotate = pConfigParser->GetValueFloat(m_MeterName, L"ImageRotate");
	m_Tile = pConfigParser->GetValueString(m_MeterName, L"Tile");
	m_ColorMatrix = pConfigParser->GetValueString(m_MeterName, L"ColorMatrix");
}






// CMeter 消息处理程序


