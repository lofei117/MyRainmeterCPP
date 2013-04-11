// Meter.cpp : 实现文件
//

#include "stdafx.h"
#include "MyRainmeter.h"
#include "Meter.h"


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
	m_TransfromationMatrix=L"1;0;0;1;0;0";

	// General Image Options
	m_ImageCrop=L"";	
	m_Greyscale=L"0";
	m_ImageTint=L"255,255,255,255";
	m_ImageAlpha=255;
	m_ImageFlip=L"None";
	m_ImageRotate=0.0;
	m_Tile=L"0";
		
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






// CMeter 消息处理程序


