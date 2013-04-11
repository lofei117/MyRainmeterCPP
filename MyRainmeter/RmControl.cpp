#include "stdafx.h"
#include "MyRainmeter.h"
#include "MyRainmeterDoc.h"
#include "MyRainmeterGraphView.h"
#include "RmControl.h"
#include "ConfigParser.h"


// CRmControl

CRmControl::CRmControl()
{

}

CRmControl::CRmControl(CXTPTaskPanelGroupItem *pItem, CMyRainmeterGraphView* pView)
{
	m_pItem = pItem;
	m_pGraphView = pView;
	m_pDocument	 = pView->GetDocument();	
}

CRmControl::~CRmControl()
{
}

void CRmControl::Invalidate()
{
	ASSERT_VALID(this);
#ifndef SHARED_HANDLERS
	if (m_pDocument)
	{
		//m_pDocument->UpdateAllViews(NULL);
		m_pGraphView->Invalidate(FALSE);
	}
#endif
}

void CRmControl::Remove()
{

}

void CRmControl::Serialize( CArchive& ar )
{

}

void CRmControl::Draw( CDC* pDC, CXTPTaskPanel* taskPanel )
{
	CRect rcItem = m_pItem->GetItemRect();		

	CXTPImageManagerIcon* pImage = taskPanel->GetImageManager()->GetImage(m_pItem->GetIconIndex());
	taskPanel->GetPaintManager()->DrawGroupItemFrame(pDC, m_pItem, rcItem);
	if (pImage)
	{
		CPoint ptIcon((rcItem.right + rcItem.left - 16) / 2, (rcItem.top + rcItem.bottom - 16) / 2);
		pImage->Draw(pDC, ptIcon, pImage->GetIcon());
	}
}

void CRmControl::Draw( CDC* pDC, CXTPTaskPanel* taskPanel, CXTPTaskPanelGroupItem* pItem )
{
	CRect rcItem = pItem->GetItemRect();		

	CXTPImageManagerIcon* pImage = taskPanel->GetImageManager()->GetImage(pItem->GetIconIndex());
	taskPanel->GetPaintManager()->DrawGroupItemFrame(pDC, pItem, rcItem);
	if (pImage)
	{
		CPoint ptIcon((rcItem.right + rcItem.left - 16) / 2, (rcItem.top + rcItem.bottom - 16) / 2);
		pImage->Draw(pDC, ptIcon, pImage->GetIcon());
	}
}

void CRmControl::InternalRelease()
{
	m_pDocument	= NULL;
	m_pItem->InternalRelease();
	m_pItem = NULL;	
}

void CRmControl::InitProperties( CMFCPropertyGridCtrl* pPropGridCtrl )
{
	// TODO 将自己的属性更新到属性列表
}

void CRmControl::UpdateProperties()
{

}


void CRmControl::PropertyChanged( CMFCPropertyGridProperty* pProp )
{

}

CString CRmControl::ToString() const
{
	return L"";
}

