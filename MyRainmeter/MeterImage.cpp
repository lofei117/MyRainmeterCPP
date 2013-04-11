// MeterBar.cpp : 实现文件
//

#include "stdafx.h"
#include "MyRainmeter.h"
#include "MeterImage.h"
#include "MyRainmeterDoc.h"
#include "MyRainmeterGraphView.h"
#include "MyPropertyGridProterty.h"
#include "RainmeterUtil.h"


// CMeterImage



CMeterImage::CMeterImage( CXTPTaskPanelGroupItem* pItem, CMyRainmeterGraphView* pView )
{
	m_ImageName = L"%1.png";
	m_PreserveAspectRatio=0;
	m_MeansureName=L"";
	m_Path=L"";
	m_ScaleMargins=L"";

	m_pItem = pItem;
	m_X = pItem->GetItemRect().left;
	m_Y = pItem->GetItemRect().top;
//	m_W = pItem->GetItemRect().Width();
//	m_H = pItem->GetItemRect().Height();
	m_W = m_H = 0;
	m_pGraphView = pView;
	m_pDocument = pView->GetDocument();
}

CMeterImage::~CMeterImage()
{
}

void CMeterImage::Serialize( CArchive& ar )
{

}

void CMeterImage::Draw( CDC* pDC, CXTPTaskPanel* taskPanel )
{
	//taskPanel->GetPaintManager()->DrawGroupItemFrame(pDC, m_pItem, rcItem);	
	
	CImage image;
	image.Load(m_ImageName);
	if(image.IsNull())
	{
		if(!CRainmeterUtil::LoadImageFromResource(&image, IDB_PNG_RAINMETER))
		{
			__super::Draw(pDC, taskPanel);			
			image.Destroy();
			return;
		}
	}
	if(image)
	{
		if (image.GetBPP() == 32) //确认该图像包含Alpha通道
		{
			int i;
			int j;
			for (i=0; i<image.GetWidth(); i++)
			{
				for (j=0; j<image.GetHeight(); j++)
				{
					byte *pByte = (byte *)image.GetPixelAddress(i, j);
					pByte[0] = pByte[0] * pByte[3] / 255;
					pByte[1] = pByte[1] * pByte[3] / 255;
					pByte[2] = pByte[2] * pByte[3] / 255;
				}
			}
		}
		m_W = m_W==0?image.GetWidth():m_W;
		m_H = m_H==0?image.GetHeight():m_H;
		CRect rcItem = m_pItem->GetItemRect();	
		int dX = (m_W-rcItem.Width())/2;
		int dY = (m_H-rcItem.Height())/2;
		rcItem.SetRect(rcItem.left-dX, rcItem.top-dY, rcItem.right+dX, rcItem.bottom+dY);
		m_pItem->SetItemRect(rcItem);		
		//CPoint ptIcon((rcItem.right + rcItem.left - image.GetWidth()) / 2, (rcItem.top + rcItem.bottom - image.GetHeight()) / 2);
		//Image.BitBlt(pDC->m_hDC,ptIcon);
		image.Draw(pDC->m_hDC, rcItem);		
	}
	image.Destroy();
}

int CMeterImage::GetMeterType()
{
	return MeterType::Image;
}

void CMeterImage::InitProperties( CMFCPropertyGridCtrl* pPropGridCtrl )
{
	//**************** General Options Area Start **************************//
	CMFCPropertyGridProperty* pGeneralOptions = new CMFCPropertyGridProperty(_T("普通选项"));
	// Add options below here
	CMFCPropertyGridProperty* pProp = new CMFCPropertyGridProperty(_T("MeterName"), m_MeterName, _T("Name of the Meter, it defined the section name like [Image1]"));
	pGeneralOptions->AddSubItem(pProp);
	pProp = new CMFCPropertyGridProperty(_T("Meter"), _T("Image"), _T("Type of the meter (e.g. Bar or String). You are not allowed to modify it here"));
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
	

	//**************** General Image Options Area Start **************************//
	CMFCPropertyGridProperty* pImageOptions = new CMFCPropertyGridProperty(_T("普通图片选项"));
	// Add options below here
	// ImageCrop
	pProp = new CMFCPropertyGridProperty(_T("ImageCrop"), m_ImageCrop, _T("Crops the image. The value should be in the form: X, Y, W, H, Origin. Origin is optional and can be set to one of the following:	\n1: Top left. \n2: Top right.\n3: Bottom right.\n4: Bottom left.\n	5: Center (both W and H)."));
	pImageOptions->AddSubItem(pProp); 
	// Greyscale
	pProp = new CMFCPropertyGridProperty(_T("Greyscale"), (_variant_t)m_DynamicVariables, _T("If set to 1, the image is greyscaled."));
	pProp->AddOption(_T("0"));	
	pProp->AddOption(_T("1"));	
	pProp->AllowEdit(FALSE);
	pImageOptions->AddSubItem(pProp);
	// ImageTint
	pProp = new CMFCPropertyGridProperty(_T("ImageTint"), m_ImageTint, _T("Color to tint the image with. "));
	pImageOptions->AddSubItem(pProp); 
	// ImageAlpha
	pProp = new CMFCPropertyGridProperty(_T("ImageAlpha"), (_variant_t) m_ImageAlpha, _T("Opacity of the image ranging from 0 (invisible) to 255 (opaque). If set, overrides the alpha component specified in ImageTint."));
	pProp->EnableSpinControl(TRUE, 0, 255);
	//pProp->AllowEdit(FALSE);
	pImageOptions->AddSubItem(pProp);
	// ImageFlip
	pProp = new CMFCPropertyGridProperty(_T("ImageFlip"), m_ImageFlip, _T("Flips the image. Valid values are None, Horizontal, Vertical or Both."));
	pProp->AddOption(_T("None"));	
	pProp->AddOption(_T("Horizontal"));	
	pProp->AddOption(_T("Vertical "));	
	pProp->AddOption(_T("Both"));	
	pProp->AllowEdit(FALSE);
	pImageOptions->AddSubItem(pProp);
	// ImageRotate
	pProp = new CMFCPropertyGridProperty(_T("ImageRotate"), (_variant_t) m_ImageRotate, _T("Rotates the image by the specified angle in degrees. Negative angles can be used for counter-clockwise rotation."));
	pImageOptions->AddSubItem(pProp);
	// Tile
	pProp = new CMFCPropertyGridProperty(_T("Tile"), (_variant_t)m_Tile, _T("If set to 1, the image is tiled (repeated) within the bounds defined by W and H."));
	pProp->AddOption(_T("0"));	
	pProp->AddOption(_T("1"));	
	pProp->AllowEdit(FALSE);
	pImageOptions->AddSubItem(pProp);
	// ColorMatrix
	pProp = new CMFCPropertyGridProperty(_T("ColorMatrix"), m_TransfromationMatrix, _T("Defines a 5x5 matrix used to manipulate the color values of the image."));
	pImageOptions->AddSubItem(pProp);
		
	// Add options above here
	pPropGridCtrl->AddProperty(pImageOptions);
	//**************** General Image Options Area End **************************//


	//**************** Image Meter Options Area Start **************************//
	CMFCPropertyGridProperty* pMeterOptions = new CMFCPropertyGridProperty(_T("Image雨滴选项"));	
	// Add options below here	
	static const TCHAR imgFilter[] = _T("图像文件 (*.bmp,*.jpg,*.gif,*.png,*.ico)|*.bmp;*.png;*.jpg;*.ico;*.gif|jpeg文件 (*.jpg)|*.jpg|png文件 (*.png)|*.png|bmp文件(*.bmp)|*.bmp|gif文件 (*.gif)|*.gif|ico文件 (*.ico)|*.ico||");
	pProp  = new CMFCPropertyGridFileProperty(_T("ImageName"), TRUE, m_ImageName , _T(""), 0, imgFilter, _T("Path of the image file."));
	pMeterOptions->AddSubItem(pProp);
	pProp = new CMyPropertyGridActionProterty(_T("Path"), m_Path , _T("Path of the image folder location."));
	pMeterOptions->AddSubItem(pProp);
	pProp = new CMFCPropertyGridProperty(_T("PreserveAspectRatio"), _T("0"), _T("Controls how W and H scale the image when Tile=0."));
	pProp->AddOption(_T("0"));	
	pProp->AddOption(_T("1"));	
	pProp->AddOption(_T("2"));	
	pProp->AllowEdit(FALSE);
	pMeterOptions->AddSubItem(pProp);
	pProp = new CMFCPropertyGridProperty(_T("ScaleMargins"), m_ScaleMargins , _T("Margins of the image to exclude from scaling when Tile=0 and PreserveAspectRatio=0."));
	pMeterOptions->AddSubItem(pProp);

	// Add options above here
	pPropGridCtrl->AddProperty(pMeterOptions);
	//**************** Image Meter Options Area End **************************//


}

void CMeterImage::UpdateProperties()
{
	m_X = m_pItem->GetItemRect().left;
	m_Y = m_pItem->GetItemRect().top;
}

void CMeterImage::PropertyChanged( CMFCPropertyGridProperty* pProp )
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
	else if (s.CompareNoCase(L"ImageCrop") == 0)
	{
		m_ImageCrop = value.bstrVal;
	}
	else if (s.CompareNoCase(L"Greyscale") == 0)
	{
		m_Greyscale = value.bstrVal;
	}
	else if (s.CompareNoCase(L"ImageTint") == 0)
	{
		m_ImageTint = value.bstrVal;
	}
	else if (s.CompareNoCase(L"ImageAlpha") == 0)
	{
		m_ImageAlpha = value.intVal;
	}
	else if (s.CompareNoCase(L"ImageFlip") == 0)
	{
		m_ImageFlip = value.bstrVal;
	}
	else if (s.CompareNoCase(L"ImageRotate") == 0)
	{
		m_ImageRotate = value.fltVal;
	}
	else if (s.CompareNoCase(L"Tile") == 0)
	{
		m_Tile = value.bstrVal;
	}
	else if (s.CompareNoCase(L"ColorMatrix") == 0)
	{
		m_ColorMatrix = value.bstrVal;
	}
	else if (s.CompareNoCase(L"ImageName") == 0)
	{
		m_ImageName = value.bstrVal;
		m_W = m_H = 0;
	}
	else if (s.CompareNoCase(L"Path") == 0)
	{
		m_Path = value.bstrVal;
	}
	else if (s.CompareNoCase(L"PreserveAspectRatio") == 0)
	{
		m_PreserveAspectRatio = value.intVal;
	}
	else if (s.CompareNoCase(L"ScaleMargins") == 0)
	{
		m_ScaleMargins = value.bstrVal;
	}	 
	else
	{
	}
	
	//t = pProp->GetOriginalValue();  //改变之前的值
	//CString d;
	
	//d = t.bstrVal;      //从COleVariant到CString
	m_pItem->SetItemRect(CRect(m_X,m_Y,m_X+m_W,m_Y+m_H));

	//Invalidate();
	
	m_pDocument->UpdateAllViews(NULL);	
	//Invalidate();
	//AfxMessageBox(s);
}

CString CMeterImage::ToString() const
{
	CString sTemp;
	//sTemp.Append(_T(";这是由MyRainmeter程序生成的用于桌面美化工具Rainmeter的配置文件\r\n"));
	//sTemp.Append(_T("\r\n"));
	sTemp.Append(_T(";Meter Image\r\n"));
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
	// General Image Options
	sTemp.Append(_T(";普通图片选项\r\n"));
	sTemp.Append(CRainmeterUtil::OrgKeyValuePair(_T("Greyscale"), m_Greyscale));
	sTemp.Append(CRainmeterUtil::OrgKeyValuePair(_T("ImageTint"), m_ImageTint));
	sTemp.Append(CRainmeterUtil::OrgKeyValuePair(_T("ImageAlpha"), m_ImageAlpha));
	sTemp.Append(CRainmeterUtil::OrgKeyValuePair(_T("ImageFlip"), m_ImageFlip));
	sTemp.Append(CRainmeterUtil::OrgKeyValuePair(_T("ImageRotate"), m_ImageRotate));
	sTemp.Append(CRainmeterUtil::OrgKeyValuePair(_T("Tile"), m_Tile));
	sTemp.Append(CRainmeterUtil::OrgKeyValuePair(_T("ColorMatrix"), m_ColorMatrix));

	// Image Meter Options
	sTemp.Append(_T(";Image雨滴选项\r\n"));
	//sTemp.Append(CRainmeterUtil::OrgKeyValuePair(_T("ImageCrop"), m_ColorMatrix));
	sTemp.Append(CRainmeterUtil::OrgKeyValuePair(_T("ImageName"), m_ImageName));
	sTemp.Append(CRainmeterUtil::OrgKeyValuePair(_T("Path"), m_Path));
	sTemp.Append(CRainmeterUtil::OrgKeyValuePair(_T("PreserveAspectRatio"), m_PreserveAspectRatio));
	sTemp.Append(CRainmeterUtil::OrgKeyValuePair(_T("ScaleMargins"), m_ScaleMargins));	
	sTemp.Append(L"\r\n");
	return sTemp;
}




