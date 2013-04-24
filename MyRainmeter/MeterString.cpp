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
	m_FontColor=L"255,0,0,0";
	//m_StringAlign=L"Left";
	//m_StringStyle=L"Normal";
	//m_StringCase=L"None";
	//m_StringEffect=L"None";
	m_FontEffectColor=L"0,0,0,255";
	//m_ClipString=L"0";
	m_ClipStringW=0;
	m_ClipStringH=0;
	m_Angle=0.0;
	//m_Percentual=L"0";
	m_NumOfDecimals=0;
	m_Scale=1;
	//m_AutoScale=L"0";

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
	Graphics graphics(pDC->m_hDC);	

	// FontStyle
	FontStyle fontStyle = FontStyleRegular;
	if (m_StringStyle.Trim().CompareNoCase(_T("Bold"))==0)
	{
		fontStyle = FontStyleBold;
	}
	else if (m_StringStyle.Trim().CompareNoCase(_T("Italic"))==0)
	{
		fontStyle = FontStyleItalic;
	}
	else if (m_StringStyle.Trim().CompareNoCase(_T("BoldItalic"))==0)
	{
		fontStyle = FontStyleBoldItalic;
	}
	// Font
	Gdiplus::Font font(m_FontFace, m_FontSize, fontStyle);
	
	COLORREF color = CRainmeterUtil::ParseColor2RGBA(m_FontColor);
	SolidBrush brush(Color(GetAValue(color), GetRValue(color), GetGValue(color), GetBValue(color)));
	PointF pt(m_X,m_Y);
	// StringAlignment
	StringFormat format;
	format.SetAlignment(StringAlignmentCenter);	
	if (m_StringAlign.CompareNoCase(_T("LeftTop"))==0 || m_StringAlign.CompareNoCase(_T("LeftCenter"))==0 || m_StringAlign.CompareNoCase(_T("LeftBottom"))==0)
	{
		format.SetAlignment(StringAlignmentFar);
	}
	else if (m_StringAlign.CompareNoCase(_T("CenterTop"))==0 || m_StringAlign.CompareNoCase(_T("CenterCenter"))==0 || m_StringAlign.CompareNoCase(_T("CenterBottom"))==0)
	{
		format.SetAlignment(StringAlignmentCenter);
	}
	else
	{
		format.SetAlignment(StringAlignmentNear);
	}

	// String content
	CString str = m_Prefix+m_Text+m_Postfix;
	if (m_StringCase.CompareNoCase(_T("Upper"))==0)
	{
		str.MakeUpper();
	}
	else if (m_StringCase.CompareNoCase(_T("Lower"))==0)
	{
		str.MakeLower();
	}
	else if (m_StringCase.CompareNoCase(_T("Proper"))==0)
	{
		CString tmp = str;
		str.MakeLower();
		tmp.MakeUpper();
		str.SetAt(0, tmp.GetAt(0));
	}
		
	// Draw SolidColor
	color = CRainmeterUtil::ParseColor2RGBA(m_SolidColor);
	Color solidColor = Color(GetAValue(color), GetRValue(color), GetGValue(color), GetBValue(color));
	Gdiplus::RectF solidRect;//(m_X, m_Y, 50, 50);

	graphics.MeasureString(str, str.GetLength(), &font, pt, &format, &solidRect);
	if (m_SolidColor2.Trim().GetLength()>0)
	{
		color = CRainmeterUtil::ParseColor2RGBA(m_SolidColor2);
		Color solidColor2 = Color(GetAValue(color), GetRValue(color), GetGValue(color), GetBValue(color));
		Gdiplus::LinearGradientBrush linGrBrush(solidRect,  //  绘制区域
			solidColor,  //  第一种颜色
			solidColor2,  //  第二种颜色 
			(Gdiplus::REAL)m_GradientAngle);  //  渐变色的角度

		graphics.FillRectangle(&linGrBrush, solidRect);
	}
	else
	{
		SolidBrush solidBrush(solidColor);
		graphics.FillRectangle(&solidBrush, solidRect);
	}

	// Draw String
	graphics.DrawString(str, str.GetLength(), &font, pt, &format, &brush);
	
	CRect rect(solidRect.GetLeft(), solidRect.GetTop(), solidRect.GetRight(), solidRect.GetBottom());
	m_pItem->SetItemRect(rect);

	graphics.ReleaseHDC(pDC->m_hDC);
	

	//LOGFONT lf = m_CurFont;
	//int nLogY = pDC->GetDeviceCaps(LOGPIXELSY);
	//lf.lfHeight=-MulDiv(m_FontSize, nLogY, 72); 
	//CFont font;
	//font.CreateFontIndirect(&lf);
	////font.CreatePointFontIndirect(&lf, pDC);
	//CFont* pOldFont = pDC->SelectObject(&font);
	//
	//COLORREF color = CRainmeterUtil::ParseColor2RGB(m_FontColor);
	//pDC->SetTextColor(color);
	//pDC->SetBkMode(TRANSPARENT);
	//pDC->TextOut(m_X, m_Y, m_Text);
	////pDC->DrawText(m_Text, m_pItem->GetItemRect(), DT_CENTER);
	//pDC->SelectObject(pOldFont);
	//font.DeleteObject();	
	
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
	CMFCPropertyGridProperty* pProp = new CMFCPropertyGridProperty(_T("MeterName"), m_MeterName, _T("Name of the Meter, it defined the section name like [String1]"));
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
	COLORREF color = CRainmeterUtil::ParseColor2RGBA(m_SolidColor);
	CMyPropertyGridColor32Property* pColorProp= new CMyPropertyGridColor32Property(_T("SolidColor"), color, NULL, _T("Color of the meter background."));
	//pProp = new CMyPropertyGridColor32Property(_T("SolidColor"), m_SolidColor, _T("Color of the meter background. If SolidColor2 is also specified, the background is a gradient composed of SolidColor and SolidColor2."));
	pColorProp->EnableOtherButton(_T("其他..."));
	pColorProp->EnableAutomaticButton(_T("默认"), ::GetSysColor(COLOR_3DFACE));
	pGeneralOptions->AddSubItem(pColorProp);
	// SolidColor2
	color = CRainmeterUtil::ParseColor2RGBA(m_SolidColor2);
	pColorProp = new CMyPropertyGridColor32Property(_T("SolidColor2"), color, NULL, _T("Color of the meter background. If SolidColor2 is also specified, the background is a gradient composed of SolidColor and SolidColor2."));
	pColorProp->EnableOtherButton(_T("其他..."));
	pColorProp->EnableAutomaticButton(_T("默认"), ::GetSysColor(COLOR_3DFACE));
	pGeneralOptions->AddSubItem(pColorProp);
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
	pProp = new CMFCPropertyGridProperty(_T("TransformationMatrix"), m_TransformationMatrix, _T("Defines a 3x2 matrix which can be used to transform the meter."));
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

	// FontColor
	color = CRainmeterUtil::ParseColor2RGBA(m_FontColor);
	//CMFCPropertyGridColorProperty* pColorProp = new CMFCPropertyGridColorProperty(_T("窗口颜色"), ARGB(255, 210, 192, 254), NULL, _T("指定默认的窗口颜色"));
	pColorProp = new CMyPropertyGridColor32Property(_T("FontColor"), color, NULL, _T("字体的颜色"));
	pColorProp->EnableOtherButton(_T("其他..."));
	pColorProp->EnableAutomaticButton(_T("默认"), ::GetSysColor(COLOR_3DFACE));
	pMeterOptions->AddSubItem(pColorProp);

	// StringAlign
	pProp = new CMFCPropertyGridProperty(_T("StringAlign"), m_StringAlign, _T("Horizontal and vertical alignment of the string."));
	/*pProp->AddOption(_T("Left"));	
	pProp->AddOption(_T("Right"));	
	pProp->AddOption(_T("Center"));	*/
	pProp->AddOption(_T("LeftTop"));	
	pProp->AddOption(_T("RightTop"));	
	pProp->AddOption(_T("CenterTop"));	
	pProp->AddOption(_T("LeftBottom"));	
	pProp->AddOption(_T("RightBottom"));	
	pProp->AddOption(_T("CenterBottom"));	
	pProp->AddOption(_T("LeftCenter"));	
	pProp->AddOption(_T("RightCenter"));	
	pProp->AddOption(_T("CenterCenter"));	
	pProp->AllowEdit(FALSE);
	pMeterOptions->AddSubItem(pProp);

	// StringStyle
	pProp = new CMFCPropertyGridProperty(_T("StringStyle"), m_StringStyle, _T("Style of the string. "));
	pProp->AddOption(_T("Normal"));	
	pProp->AddOption(_T("Bold"));	
	pProp->AddOption(_T("Italic"));	
	pProp->AddOption(_T("BoldItalic"));	
	pProp->AllowEdit(FALSE);
	pMeterOptions->AddSubItem(pProp);

	// StringCase
	pProp = new CMFCPropertyGridProperty(_T("StringCase"), m_StringCase, _T("Converts the string to a case. "));
	pProp->AddOption(_T("None"));	
	pProp->AddOption(_T("Upper"));	
	pProp->AddOption(_T("Lower"));	
	pProp->AddOption(_T("Proper"));	
	pProp->AllowEdit(FALSE);
	pMeterOptions->AddSubItem(pProp);

	// StringEffect
	pProp = new CMFCPropertyGridProperty(_T("StringEffect"), m_StringEffect, _T("Effect applied to a string."));
	pProp->AddOption(_T("None"));	
	pProp->AddOption(_T("Shadow"));	
	pProp->AddOption(_T("Border"));	
	pProp->AllowEdit(FALSE);	
	pMeterOptions->AddSubItem(pProp);

	// FontEffectColor
	color = CRainmeterUtil::ParseColor2RGBA(m_FontEffectColor);
	pColorProp = new CMyPropertyGridColor32Property(_T("FontEffectColor"), color, NULL, _T("Color of the StringEffect. "));
	pColorProp->EnableOtherButton(_T("其他..."));
	pColorProp->EnableAutomaticButton(_T("默认"), ::GetSysColor(COLOR_3DFACE));
	pMeterOptions->AddSubItem(pColorProp);

	// ClipString 
	pProp = new CMFCPropertyGridProperty(_T("ClipString"), m_ClipString, _T("Controls how strings are truncated (clipped) or wrapped to fit in or expand the containing meter."));
	pProp->AddOption(_T("0"));	
	pProp->AddOption(_T("1"));	
	pProp->AddOption(_T("2"));	
	pProp->AllowEdit(FALSE);	
	pMeterOptions->AddSubItem(pProp);
	// ClipStringW 
	pProp = new CMFCPropertyGridProperty(_T("ClipStringW"), (_variant_t)m_ClipStringW, _T("Sets a maximum width that the meter will expand to accomodate the string when ClipString=2. "));
	pMeterOptions->AddSubItem(pProp);
	// ClipStringH 
	pProp = new CMFCPropertyGridProperty(_T("ClipStringH"), (_variant_t)m_ClipStringH, _T("Sets a maximum height that the meter will expand to accomodate the string when ClipString=2. "));
	pMeterOptions->AddSubItem(pProp);
	
	// Angle
	pProp = new CMFCPropertyGridProperty(_T("Angle"), (_variant_t)m_Angle, _T("Defines the angle of the text in radians. "));
	pMeterOptions->AddSubItem(pProp);

	// Percentual  
	pProp = new CMFCPropertyGridProperty(_T("Percentual"), m_Percentual, _T("If set to 1, percentual measure values are used for the %N syntax. "));
	pProp->AddOption(_T("0"));	
	pProp->AddOption(_T("1"));	
	pProp->AllowEdit(FALSE);	
	pMeterOptions->AddSubItem(pProp);

	// NumOfDecimals 
	pProp = new CMFCPropertyGridProperty(_T("NumOfDecimals"), (_variant_t)m_NumOfDecimals, _T("Number of decimals to display with numerical measure values for the %N syntax. "));
	pMeterOptions->AddSubItem(pProp);

	// Scale 
	pProp = new CMFCPropertyGridProperty(_T("Scale"), (_variant_t)m_Scale, _T("Scaling factor used for the measure value(s) for the %N syntax in Text. "));
	pMeterOptions->AddSubItem(pProp);

	// AutoScale  
	pProp = new CMFCPropertyGridProperty(_T("AutoScale"), m_AutoScale, _T("Automatically scales the measure value(s) for the %N syntax in Text. "));
	pProp->AddOption(_T("0"));	
	pProp->AddOption(_T("1"));	
	pProp->AddOption(_T("1k"));	
	pProp->AddOption(_T("2"));	
	pProp->AddOption(_T("2k"));	
	pProp->AllowEdit(FALSE);	
	pMeterOptions->AddSubItem(pProp);

	// Add options above here
	pPropGridCtrl->AddProperty(pMeterOptions);
	//**************** String Meter Options Area End **************************//

	//**************** Mouse Actions Area Start **************************//
	// Add options below here	
	CMFCPropertyGridProperty* pMouseActions = new CMFCPropertyGridProperty(_T("鼠标事件"));
	for (unordered_map<wstring,wstring>::iterator iter = m_MouseActions.begin(); iter!= m_MouseActions.end(); ++iter)
	{
		pAction = new CMyPropertyGridActionProterty(iter->first.c_str(), iter->second.c_str(), _T("Action to execute"));
		pMouseActions->AddSubItem(pAction);		
	}
	pMouseActions->Expand(FALSE);
	// Add options above here
	pPropGridCtrl->AddProperty(pMouseActions);
	//**************** Mouse Actions Options Area End **************************//
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
	s = s.Trim();
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
		value = ((CMyPropertyGridColor32Property*)pProp)->GetValue();
		m_SolidColor = value.bstrVal;
	}
	else if (s.CompareNoCase(L"SolidColor2") == 0)
	{
		value = ((CMyPropertyGridColor32Property*)pProp)->GetValue();
		m_SolidColor2 = value.bstrVal;
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
		m_TransformationMatrix = value.bstrVal;
	}
	else if (s.CompareNoCase(L"Text") == 0)
	{
		m_Text = value.bstrVal;
	}
	else if (s.CompareNoCase(L"Prefix") == 0)
	{
		m_Prefix = value.bstrVal;
	}
	else if (s.CompareNoCase(L"Postfix") == 0)
	{
		m_Postfix = value.bstrVal;
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
	else if (s.CompareNoCase(L"FontColor") == 0)
	{
		value = ((CMyPropertyGridColor32Property*)pProp)->GetValue();
		m_FontColor = value.bstrVal;
	}
	else if (s.CompareNoCase(L"StringAlign") == 0)
	{
		m_StringAlign = value.bstrVal;
	}
	else if (s.CompareNoCase(L"StringStyle") == 0)
	{
		m_StringStyle = value.bstrVal;
	}
	else if (s.CompareNoCase(L"StringCase") == 0)
	{
		m_StringCase = value.bstrVal;
	}
	else if (s.CompareNoCase(L"StringEffect") == 0)
	{
		m_StringEffect = value.bstrVal;
	}
	else if (s.CompareNoCase(L"FontEffectColor") == 0)
	{
		value = ((CMyPropertyGridColor32Property*)pProp)->GetValue();
		m_FontEffectColor = value.bstrVal;
	}
	else if (s.CompareNoCase(L"ClipString") == 0)
	{
		m_ClipString = value.bstrVal;
	}
	else if (s.CompareNoCase(L"ClipStringW") == 0)
	{
		m_ClipStringW = value.intVal;
	}
	else if (s.CompareNoCase(L"ClipStringH") == 0)
	{
		m_ClipStringH = value.intVal;
	}
	else if (s.CompareNoCase(L"Angle") == 0)
	{
		m_Angle = value.fltVal;
	}
	else if (s.CompareNoCase(L"Percentual") == 0)
	{
		m_Percentual = value.bstrVal;
	}
	else if (s.CompareNoCase(L"NumOfDecimals") == 0)
	{
		m_NumOfDecimals = value.intVal;
	}
	else if (s.CompareNoCase(L"Scale") == 0)
	{
		m_Scale = value.intVal;
	}
	else if (s.CompareNoCase(L"AutoScale") == 0)
	{
		m_AutoScale = value.bstrVal;
	}
	else
	{
		CMFCPropertyGridProperty* pParent = pProp->GetParent();
		CString tmp = pParent->GetName();
		tmp = tmp.Trim();
		if (tmp.CompareNoCase(_T("鼠标事件"))==0)
		{
			wstring action = s;
			m_MouseActions[action]=value.bstrVal;
		}
	}

	//m_pItem->SetItemRect(CRect(m_X,m_Y,m_X+m_W,m_Y+m_H));

	//Invalidate();

	m_pDocument->UpdateAllViews(NULL);	
}

CString CMeterString::ToString() const
{
	CString sTemp;
	//sTemp.Append(_T(";这是由MyRainmeter程序生成的用于桌面美化工具Rainmeter的配置文件\r\n"));
	//sTemp.Append(_T("\r\n"));
	sTemp.Append(_T(";;;;;;;;;;;;;Meter String;;;;;;;;;;;;\r\n"));
	// Section name
	sTemp.Append(_T("["+m_MeterName+"]\r\n"));	
	//sTemp.Append(_T(";普通选项\r\n"));
	// General options
	sTemp.Append(CRainmeterUtil::OrgKeyValuePair(_T("Meter"), L"String", _T("Meter 类型")));
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
	sTemp.Append(CRainmeterUtil::OrgKeyValuePair(_T("SolidColor2"), m_SolidColor2, _T("")));
	sTemp.Append(CRainmeterUtil::OrgKeyValuePair(_T("GradientAngle"), m_GradientAngle));
	sTemp.Append(CRainmeterUtil::OrgKeyValuePair(_T("BevelType"), m_BevelType));
	sTemp.Append(CRainmeterUtil::OrgKeyValuePair(_T("AntiAlias"), m_AntiAlias));
	sTemp.Append(CRainmeterUtil::OrgKeyValuePair(_T("DynamicVariables"), m_DynamicVariables));
	sTemp.Append(CRainmeterUtil::OrgKeyValuePair(_T("TransformationMatrix"), m_TransformationMatrix));
	
	// Image Meter Options
	sTemp.Append(_T(";String雨滴选项\r\n"));
	sTemp.Append(CRainmeterUtil::OrgKeyValuePair(_T("Text"), m_Text));
	sTemp.Append(CRainmeterUtil::OrgKeyValuePair(_T("Prefix"), m_Prefix));
	sTemp.Append(CRainmeterUtil::OrgKeyValuePair(_T("Postfix"), m_Postfix));
	sTemp.Append(CRainmeterUtil::OrgKeyValuePair(_T("FontFace"), m_FontFace));	
	sTemp.Append(CRainmeterUtil::OrgKeyValuePair(_T("FontSize"), m_FontSize));
	sTemp.Append(CRainmeterUtil::OrgKeyValuePair(_T("FontColor"), m_FontColor));	
	sTemp.Append(CRainmeterUtil::OrgKeyValuePair(_T("StringAlign"), m_StringAlign));	
	sTemp.Append(CRainmeterUtil::OrgKeyValuePair(_T("StringStyle"), m_StringStyle));	
	sTemp.Append(CRainmeterUtil::OrgKeyValuePair(_T("StringCase"), m_StringCase));
	sTemp.Append(CRainmeterUtil::OrgKeyValuePair(_T("StringEffect"), m_StringEffect));
	sTemp.Append(CRainmeterUtil::OrgKeyValuePair(_T("FontEffectColor"), m_FontEffectColor));
	sTemp.Append(CRainmeterUtil::OrgKeyValuePair(_T("ClipString"), m_ClipString));
	sTemp.Append(CRainmeterUtil::OrgKeyValuePair(_T("ClipStringW"), m_ClipStringW));
	sTemp.Append(CRainmeterUtil::OrgKeyValuePair(_T("ClipStringH"), m_ClipStringH));
	sTemp.Append(CRainmeterUtil::OrgKeyValuePair(_T("Angle"), m_Angle));
	sTemp.Append(CRainmeterUtil::OrgKeyValuePair(_T("Percentual"), m_Percentual));
	sTemp.Append(CRainmeterUtil::OrgKeyValuePair(_T("NumOfDecimals"), m_NumOfDecimals));
	sTemp.Append(CRainmeterUtil::OrgKeyValuePair(_T("Scale"), m_Scale));
	sTemp.Append(CRainmeterUtil::OrgKeyValuePair(_T("AutoScale"), m_AutoScale));

	// Mouse Actions
	for (unordered_map<wstring,wstring>::const_iterator iter = m_MouseActions.begin(); iter!= m_MouseActions.end(); ++iter)
	{
		sTemp.Append(CRainmeterUtil::OrgKeyValuePair(iter->first.c_str(), iter->second.c_str()));
	}

	sTemp.Append(L"\r\n");
	return sTemp;
}

void CMeterString::ParseData( CConfigParser* pConfigParser )
{
	__super::ParseData(pConfigParser);

	m_Text = pConfigParser->GetValueString(m_MeterName, L"Text");
	m_Prefix = pConfigParser->GetValueString(m_MeterName, L"Prefix");
	m_Postfix = pConfigParser->GetValueString(m_MeterName, L"Postfix");
	m_FontFace = pConfigParser->GetValueString(m_MeterName, L"FontFace");
	m_FontSize = pConfigParser->GetValueInt(m_MeterName, L"FontSize");
	m_FontColor = pConfigParser->GetValueString(m_MeterName, L"FontColor", L"0,0,0,255");
	m_StringAlign = pConfigParser->GetValueString(m_MeterName, L"StringAlign");
	m_StringStyle = pConfigParser->GetValueString(m_MeterName, L"StringStyle");
	m_StringCase = pConfigParser->GetValueString(m_MeterName, L"StringCase");
	m_StringEffect = pConfigParser->GetValueString(m_MeterName, L"StringEffect");
	m_FontEffectColor = pConfigParser->GetValueString(m_MeterName, L"FontEffectColor");

	m_ClipString = pConfigParser->GetValueString(m_MeterName, L"ClipString");
	m_ClipStringW = pConfigParser->GetValueInt(m_MeterName, L"ClipStringW");
	m_ClipStringH = pConfigParser->GetValueInt(m_MeterName, L"ClipStringH");
	
	m_Angle = pConfigParser->GetValueFloat(m_MeterName, L"Angle");
	m_Percentual = pConfigParser->GetValueString(m_MeterName, L"Percentual");
	m_NumOfDecimals = pConfigParser->GetValueInt(m_MeterName, L"NumOfDecimals");
	m_Scale = pConfigParser->GetValueInt(m_MeterName, L"Scale");
	m_AutoScale = pConfigParser->GetValueString(m_MeterName, L"AutoScale");

	m_pItem->SetItemRect(CRect(m_X, m_Y, m_W, m_H));
}





