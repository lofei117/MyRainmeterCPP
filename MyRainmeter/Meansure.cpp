// Meansure.cpp : 实现文件
//

#include "stdafx.h"
#include "MyRainmeter.h"
#include "Meansure.h"


// CMeansure

IMPLEMENT_DYNAMIC(CMeansure, CWnd)

CMeansure::CMeansure()
{
	m_UpdateDivider=1;
	m_InvertMeansure=0;
	m_MaxValue=1.0;
	m_MinValue=0.0;
	m_AverageSize=1;
	m_Disabled=0;
	m_DynamicVariables=0;
}

CMeansure::~CMeansure()
{
}


BEGIN_MESSAGE_MAP(CMeansure, CWnd)
END_MESSAGE_MAP()



// CMeansure 消息处理程序


