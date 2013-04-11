// MeterBar.cpp : 实现文件
//

#include "stdafx.h"
#include "MyRainmeter.h"
#include "MeterBar.h"


// CMeterBar



CMeterBar::CMeterBar()
{

}

CMeterBar::CMeterBar( CXTPTaskPanelGroupItem* pItem )
{
	m_pItem = pItem;
}

CMeterBar::~CMeterBar()
{
}

void CMeterBar::Serialize( CArchive& ar )
{

}

void CMeterBar::Draw( CDC* pDC, CXTPTaskPanel* taskPanel )
{
	CRect rcItem = m_pItem->GetItemRect();		

	//taskPanel->GetPaintManager()->DrawGroupItemFrame(pDC, m_pItem, rcItem);
	CImage Image;
	Image.Load(L"E:\\study\\myproject\\MyRainmeterCPP\\Debug\\rainmeter.png");	

	if(Image)
	{
		if (Image.GetBPP() == 32) //确认该图像包含Alpha通道
		{
			int i;
			int j;
			for (i=0; i<Image.GetWidth(); i++)
			{
				for (j=0; j<Image.GetHeight(); j++)
				{
					byte *pByte = (byte *)Image.GetPixelAddress(i, j);
					pByte[0] = pByte[0] * pByte[3] / 255;
					pByte[1] = pByte[1] * pByte[3] / 255;
					pByte[2] = pByte[2] * pByte[3] / 255;
				}
			}
		}
		CPoint ptIcon((rcItem.right + rcItem.left - Image.GetWidth()) / 2, (rcItem.top + rcItem.bottom - Image.GetHeight()) / 2);
		//Image.BitBlt(pDC->m_hDC,ptIcon);
		Image.Draw(pDC->m_hDC, ptIcon);
		Image.Destroy();
	}
}

int CMeterBar::GetMeterType()
{
	return MeterType::Bar;
}

void CMeterBar::FillProperties( CMFCPropertyGridCtrl* pPropGridCtrl )
{
	//AfxMessageBox(L"meterbar");
}





// CMeterBar 消息处理程序


