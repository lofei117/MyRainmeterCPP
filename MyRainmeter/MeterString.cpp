// MeterBar.cpp : 实现文件
//

#include "stdafx.h"
#include "MyRainmeter.h"
#include "MeterString.h"
#include "MyRainmeterDoc.h"
#include "MyRainmeterGraphView.h"
#include "MyPropertyGridProterty.h"
#include "RainmeterUtil.h"


// CMeterString



CMeterString::CMeterString( CXTPTaskPanelGroupItem* pItem, CMyRainmeterGraphView* pView )
{
	m_Text=L"%1";
	m_FontFace=L"Arial";
	m_FontSize=10;
	m_FontColor=L"0,0,0,255";
	m_StringAligh=L"Left";
	m_StringStyle=L"Normal";
	m_StringCase=L"None";
	m_StringEffect=L"None";
	m_FontEffectColor=L"0,0,0,255";
	m_ClipString=L"0";
	m_Angle=0.0;
	m_Percentual=0;
	m_NumOfDecimals=0;
	m_Scale=1;
	m_AutoScale=L"0";

	m_pItem = pItem;
	m_X = pItem->GetItemRect().left;
	m_Y = pItem->GetItemRect().top;
	//	m_W = pItem->GetItemRect().Width();
	//	m_H = pItem->GetItemRect().Height();
	m_W = m_H = 0;
	m_pGraphView = pView;
	m_pDocument = pView->GetDocument();
}

CMeterString::~CMeterString()
{
}

void CMeterString::Serialize( CArchive& ar )
{

}

void CMeterString::Draw( CDC* pDC, CXTPTaskPanel* taskPanel )
{
	// TODO Need to Override the method here
	//__super::Draw(pDC, taskPanel);
	
	CFont font;
	font.CreatePointFontIndirect(&m_CurFont, pDC);
	CFont* pOldFont = pDC->SelectObject(&font);
	pDC->SetBkMode(TRANSPARENT);
	//pDC->TextOut(20, 154, L"hello");
	pDC->DrawText(L"hello", m_pItem->GetItemRect(), 0);
	pDC->SelectObject(pOldFont);
	font.DeleteObject();	
}

int CMeterString::GetMeterType()
{
	return MeterType::String;
}

void CMeterString::InitProperties( CMFCPropertyGridCtrl* pPropGridCtrl )
{
	m_pPropWnd = pPropGridCtrl;
	//**************** General Options Area Start **************************//
	CMFCPropertyGridProperty* pGeneralOptions = new CMFCPropertyGridProperty(_T("普通选项"));
	// Add options below here
	CMFCPropertyGridProperty* pProp = new CMFCPropertyGridProperty(_T("MeterName"), m_MeterName, _T("Name of the Meter, it defined the section name like [Image1]"));
	pGeneralOptions->AddSubItem(pProp);
	pProp = new CMFCPropertyGridProperty(_T("Meter"), _T("String"), _T("Type of the meter (e.g. Bar or String). You are not allowed to modify it here"));
	pProp->AllowEdit(FALSE);
	pGeneralOptions->AddSubItem(pProp);
	pProp = new CMFCPropertyGridProperty(_T("MeterStyle"), m_MeterStyle, _T("Specifies one or more sections as MeterStyles from which option values are inherited. Multiple MeterStyles are delimited with pipes (|)."));
	pGeneralOptions->AddSubItem(pProp);
	pProp = new CMFCPropertyGridProperty(_T("MeansureName"), m_MeansureName, _T("MeansureName"));
	pGeneralOptions->AddSubItem(pProp);

	// Location of the meter
	CMFCPropertyGridProperty* pLocation = new CMFCPropertyGridProperty(_T("Location"), 0, TRUE);	
	pProp = new CMFCPropertyGridProperty(_T("X"), (_variant_t) m_X, _T("location.X of the image"));
	pProp->EnableSpinControl(TRUE, 0, m_pGraphView->GetViewSize().cx);
	pLocation->AddSubItem(pProp);
	pProp = new CMFCPropertyGridProperty(_T("Y"), (_variant_t) m_Y, _T("location.Y of the image"));
	pProp->EnableSpinControl(TRUE, 0, m_pGraphView->GetViewSize().cy);
	pLocation->AddSubItem(pProp);
	pGeneralOptions->AddSubItem(pLocation);

	// Size of the meter
	CMFCPropertyGridProperty* pSize = new CMFCPropertyGridProperty(_T("Size"), 0, TRUE);	
	pProp = new CMFCPropertyGridProperty(_T("W"), (_variant_t) m_W, _T("width of the image"));
	pProp->EnableSpinControl(TRUE, 0, m_pGraphView->GetViewSize().cx);
	pSize->AddSubItem(pProp);
	pProp = new CMFCPropertyGridProperty(_T("H"), (_variant_t) m_H, _T("height of the image"));
	pProp->EnableSpinControl(TRUE, 0, m_pGraphView->GetViewSize().cy);
	pSize->AddSubItem(pProp);
	pGeneralOptions->AddSubItem(pSize); 
	// Hidden
	pProp = new CMFCPropertyGridProperty(_T("Hidden"), (_variant_t)m_Hidden, _T("If set to 1, the meter is hidden. The visibility can also be changed with the !ShowMeter and !HideMeter bangs."));
	pProp->AddOption(_T("0"));	
	pProp->AddOption(_T("1"));	
	pProp->AllowEdit(FALSE);
	pGeneralOptions->AddSubItem(pProp);
	// UpdateDivider
	pProp = new CMFCPropertyGridProperty(_T("UpdateDivider"), (_variant_t)m_UpdateDivider, _T("Sets the update frequency of the meter."));
	pGeneralOptions->AddSubItem(pProp);
	// OnUpdateAction
	CMFCPropertyGridProperty* pAction = new CMyPropertyGridActionProterty(_T("OnUpdateAction"), m_OnUpdateAction, _T("Action to execute on each Update of the meter. This option obeys any UpdateDivider on the meter."));
	pGeneralOptions->AddSubItem(pAction);
	// SolidColor
	pProp = new CMFCPropertyGridProperty(_T("SolidColor"), m_SolidColor, _T("Color of the meter background. If SolidColor2 is also specified, the background is a gradient composed of SolidColor and SolidColor2."));
	pGeneralOptions->AddSubItem(pProp);
	// GradientAngle
	pProp = new CMFCPropertyGridProperty(_T("GradientAngle"), (_variant_t)m_GradientAngle, _T("Angle of the gradient in degrees (for SolidColor and SolidColor2)."));
	pGeneralOptions->AddSubItem(pProp);
	// BevelType
	pProp = new CMFCPropertyGridProperty(_T("BevelType"), (_variant_t)m_BevelType, _T("If enabled, draws a bevel around the edges of the rectangle specified by H and W. Valid values are:0: No bevel\r\n1: Raised \r\n2: Sunken"));
	pProp->AddOption(_T("0"));
	pProp->AddOption(_T("1"));	
	pProp->AddOption(_T("2"));
	pProp->AllowEdit(FALSE);
	pGeneralOptions->AddSubItem(pProp);
	// AntiAlias
	pProp = new CMFCPropertyGridProperty(_T("AntiAlias"), (_variant_t)m_AntiAlias, _T("If set to 1, antialising is used to display the meter."));
	pProp->AddOption(_T("0"));	
	pProp->AddOption(_T("1"));	
	pProp->AllowEdit(FALSE);
	pGeneralOptions->AddSubItem(pProp);
	// DynamicVariables
	pProp = new CMFCPropertyGridProperty(_T("DynamicVariables"), (_variant_t)m_DynamicVariables, _T("If set to 1, the meter is dynamic."));
	pProp->AddOption(_T("0"));	
	pProp->AddOption(_T("1"));	
	pProp->AllowEdit(FALSE);
	pGeneralOptions->AddSubItem(pProp);
	// TransformationMatrix
	pProp = new CMFCPropertyGridProperty(_T("TransformationMatrix"), m_TransfromationMatrix, _T("Defines a 3x2 matrix which can be used to transform the meter."));
	pGeneralOptions->AddSubItem(pProp);

	// Add options above here
	pPropGridCtrl->AddProperty(pGeneralOptions);		// Remember to add the options to the main grid control IN and ONLY IN the end
	//**************** General Options Area End **************************//
	

	//**************** String Meter Options Area Start **************************//
	CMFCPropertyGridProperty* pMeterOptions = new CMFCPropertyGridProperty(_T("String雨滴选项"));	
	// Add options below here	
	pProp = new CMFCPropertyGridProperty(_T("Text"), m_Text , _T("Text to display."));
	pMeterOptions->AddSubItem(pProp);
	pProp = new CMFCPropertyGridProperty(_T("Prefix"), m_Prefix , _T("Text displayed before Text."));
	pMeterOptions->AddSubItem(pProp);
	pProp = new CMFCPropertyGridProperty(_T("Postfix"), m_Postfix , _T("Text displayed after Text."));
	pMeterOptions->AddSubItem(pProp);

	// Font area
	LOGFONT lf;
	CFont* font = CFont::FromHandle((HFONT) GetStockObject(DEFAULT_GUI_FONT));
	font->GetLogFont(&lf);
	lstrcpy(lf.lfFaceName, m_FontFace);
	lf.lfUnderline=FALSE;
	lf.lfItalic=FALSE;	
	m_CurFont = lf;
	CWindowDC dc(m_pPropWnd);
	int nLogY = dc.GetDeviceCaps(LOGPIXELSY);
	lf.lfHeight=-MulDiv(m_FontSize, nLogY, 72); 
	
	pProp = new CMFCPropertyGridFontProperty(_T("FontFace"), lf, CF_EFFECTS | CF_SCREENFONTS, _T("字体"));	
	pMeterOptions->AddSubItem(pProp);

	/*pProp = new CMFCPropertyGridProperty(_T("FontSize"), (_variant_t) m_FontSize, _T("Size of the font."));
	pProp->EnableSpinControl(TRUE, 6, 32);
	pProp->AllowEdit(FALSE);
	pMeterOptions->AddSubItem(pProp);*/

	//ARGB
	CMFCPropertyGridColorProperty* pColorProp = new CMFCPropertyGridColorProperty(_T("窗口颜色"), RGB(210, 192, 254), NULL, _T("指定默认的窗口颜色"));
	pColorProp->EnableOtherButton(_T("其他..."));
	pColorProp->EnableAutomaticButton(_T("默认"), ::GetSysColor(COLOR_3DFACE));
	pMeterOptions->AddSubItem(pColorProp);

	/*static const TCHAR imgFilter[] = _T("图像文件 (*.bmp,*.jpg,*.gif,*.png,*.ico)|*.bmp;*.png;*.jpg;*.ico;*.gif|jpeg文件 (*.jpg)|*.jpg|png文件 (*.png)|*.png|bmp文件(*.bmp)|*.bmp|gif文件 (*.gif)|*.gif|ico文件 (*.ico)|*.ico||");
	pProp  = new CMFCPropertyGridFileProperty(_T("ImageName"), TRUE, m_ImageName , _T(""), 0, imgFilter, _T("Path of the image file."));
	pMeterOptions->AddSubItem(pProp);
	pProp = new CMFCPropertyGridProperty(_T("Path"), m_Path , _T("Path of the image folder location."));
	pMeterOptions->AddSubItem(pProp);
	pProp = new CMFCPropertyGridProperty(_T("PreserveAspectRatio"), _T("0"), _T("Controls how W and H scale the image when Tile=0."));
	pProp->AddOption(_T("0"));	
	pProp->AddOption(_T("1"));	
	pProp->AddOption(_T("2"));	
	pProp->AllowEdit(FALSE);
	pMeterOptions->AddSubItem(pProp);
	pProp = new CMFCPropertyGridProperty(_T("ScaleMargins"), m_ScaleMargins , _T("Margins of the image to exclude from scaling when Tile=0 and PreserveAspectRatio=0."));
	pMeterOptions->AddSubItem(pProp);*/

	// Add options above here
	pPropGridCtrl->AddProperty(pMeterOptions);
	//**************** Image Meter Options Area End **************************//


}

void CMeterString::UpdateProperties()
{
	m_X = m_pItem->GetItemRect().left;
	m_Y = m_pItem->GetItemRect().top;
}

void CMeterString::PropertyChanged( CMFCPropertyGridProperty* pProp )
{	
	int i = (int) pProp->GetData ();
	CString s = pProp->GetName();  //被改变的参数名
	COleVariant value = pProp->GetValue(); //改变之后的值	

	if (s.CompareNoCase(L"MeterName") == 0)
	{
		m_MeterName = value.bstrVal;
	} 
	else if (s.CompareNoCase(L"MeansureName") == 0)
	{
		m_MeansureName = value.bstrVal;
	}
	else if (s.CompareNoCase(L"MeterStyle") == 0)
	{
		m_MeterStyle = value.bstrVal;
	}
	else if (s.CompareNoCase(L"X") == 0)
	{
		m_X = value.intVal;		
	}
	else if (s.CompareNoCase(L"Y") == 0)
	{
		m_Y = value.intVal;
	}
	else if (s.CompareNoCase(L"Location") == 0)
	{
		//CMFCPropertyGridProperty* pX = pProp->GetSubItem(0);
		m_X = pProp->GetSubItem(0)->GetValue().intVal;
		m_Y = pProp->GetSubItem(1)->GetValue().intVal;
	}
	else if (s.CompareNoCase(L"W") == 0)
	{
		m_W = value.intVal;		
	}
	else if (s.CompareNoCase(L"H") == 0)
	{
		m_H = value.intVal;
	}
	else if (s.CompareNoCase(L"Size") == 0)
	{
		//CMFCPropertyGridProperty* pX = pProp->GetSubItem(0);
		m_W = pProp->GetSubItem(0)->GetValue().intVal;
		m_H = pProp->GetSubItem(1)->GetValue().intVal;
	}
	else if (s.CompareNoCase(L"Hidden") == 0)
	{
		m_Hidden = value.bstrVal;
	}
	else if (s.CompareNoCase(L"UpdateDivider") == 0)
	{
		m_UpdateDivider = value.intVal;
	}
	else if (s.CompareNoCase(L"OnUpdateAction") == 0)
	{
		m_OnUpdateAction = value.bstrVal;
	}
	else if (s.CompareNoCase(L"SolidColor") == 0)
	{
		m_SolidColor = value.bstrVal;
	}
	else if (s.CompareNoCase(L"GradientAngle") == 0)
	{
		m_GradientAngle = value.intVal;
	}
	else if (s.CompareNoCase(L"BevelType") == 0)
	{
		m_BevelType = value.bstrVal;
	}
	else if (s.CompareNoCase(L"AntiAlias") == 0)
	{
		m_AntiAlias = value.bstrVal;
	}
	else if (s.CompareNoCase(L"DynamicVariables") == 0)
	{ 
		m_DynamicVariables = value.bstrVal;
	}
	else if (s.CompareNoCase(L"TransformationMatrix") == 0)
	{
		m_TransfromationMatrix = value.bstrVal;
	}
	else if (s.CompareNoCase(L"Text") == 0)
	{
		m_Text = value.bstrVal;
	}
	else if (s.CompareNoCase(L"FontFace") == 0)
	{
		LPLOGFONT pLogFont = ((CMFCPropertyGridFontProperty*)pProp)->GetLogFont();

		CWindowDC dc(m_pPropWnd);
		int nLogY = dc.GetDeviceCaps(LOGPIXELSY);
		if (nLogY != 0)
		{			
			m_FontFace = pLogFont->lfFaceName;
			m_FontSize = MulDiv(72, -pLogFont->lfHeight, nLogY);
			//AfxMessageBox(m_FontSize);
		}
		m_CurFont = *pLogFont;
	}
	else
	{
	}

	//t = pProp->GetOriginalValue();  //改变之前的值
	//CString d;

	//d = t.bstrVal;      //从COleVariant到CString
	//m_pItem->SetItemRect(CRect(m_X,m_Y,m_X+m_W,m_Y+m_H));

	//Invalidate();

	m_pDocument->UpdateAllViews(NULL);	
	//Invalidate();
	//AfxMessageBox(s);
}

CString CMeterString::ToString() const
{
	CString sTemp;
	//sTemp.Append(_T(";这是由MyRainmeter程序生成的用于桌面美化工具Rainmeter的配置文件\r\n"));
	//sTemp.Append(_T("\r\n"));
	sTemp.Append(_T(";Meter String\r\n"));
	// Section name
	sTemp.Append(_T("["+m_MeterName+"]\r\n"));	
	sTemp.Append(_T(";普通选项\r\n"));
	// General options
	sTemp.Append(CRainmeterUtil::OrgKeyValuePair(_T("Meter"), L"Image", _T("Meter 类型")));
	sTemp.Append(CRainmeterUtil::OrgKeyValuePair(_T("MeterStyle"), m_MeterStyle));
	sTemp.Append(CRainmeterUtil::OrgKeyValuePair(_T("MeansureName"), m_MeansureName));
	sTemp.Append(CRainmeterUtil::OrgKeyValuePair(_T("X"), m_X));
	sTemp.Append(CRainmeterUtil::OrgKeyValuePair(_T("Y"), m_Y));
	sTemp.Append(CRainmeterUtil::OrgKeyValuePair(_T("W"), m_W));
	sTemp.Append(CRainmeterUtil::OrgKeyValuePair(_T("H"), m_H));
	sTemp.Append(CRainmeterUtil::OrgKeyValuePair(_T("Hidden"), m_Hidden, _T("是否隐藏")));
	sTemp.Append(CRainmeterUtil::OrgKeyValuePair(_T("UpdateDivider"), m_UpdateDivider, _T("")));
	sTemp.Append(CRainmeterUtil::OrgKeyValuePair(_T("OnUpdateAction"), m_OnUpdateAction, _T("")));
	sTemp.Append(CRainmeterUtil::OrgKeyValuePair(_T("SolidColor"), m_SolidColor, _T("")));
	sTemp.Append(CRainmeterUtil::OrgKeyValuePair(_T("GradientAngle"), m_GradientAngle));
	sTemp.Append(CRainmeterUtil::OrgKeyValuePair(_T("BevelType"), m_BevelType));
	sTemp.Append(CRainmeterUtil::OrgKeyValuePair(_T("AntiAlias"), m_AntiAlias));
	sTemp.Append(CRainmeterUtil::OrgKeyValuePair(_T("DynamicVariables"), m_DynamicVariables));
	sTemp.Append(CRainmeterUtil::OrgKeyValuePair(_T("TransfromationMatrix"), m_TransfromationMatrix));
	
	// Image Meter Options
	sTemp.Append(_T(";String雨滴选项\r\n"));
	//sTemp.Append(CRainmeterUtil::OrgKeyValuePair(_T("ImageCrop"), m_ColorMatrix));
	sTemp.Append(CRainmeterUtil::OrgKeyValuePair(_T("Text"), m_Text));
	sTemp.Append(CRainmeterUtil::OrgKeyValuePair(_T("Prefix"), m_Prefix));
	sTemp.Append(CRainmeterUtil::OrgKeyValuePair(_T("Postfix"), m_Postfix));
	sTemp.Append(CRainmeterUtil::OrgKeyValuePair(_T("FontFace"), m_FontFace));	
	sTemp.Append(CRainmeterUtil::OrgKeyValuePair(_T("FontSize"), m_FontSize));
	sTemp.Append(CRainmeterUtil::OrgKeyValuePair(_T("FontColor"), m_FontColor));	
	sTemp.Append(L"\r\n");
	return sTemp;
}




