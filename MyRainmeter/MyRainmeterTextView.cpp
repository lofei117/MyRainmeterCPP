// MyRainmeterTextView.cpp : 实现文件
//

#include "stdafx.h"
#include "MyRainmeter.h"
#include "MyRainmeterDoc.h"
#include "MyRainmeterTextView.h"


// CMyRainmeterTextView

IMPLEMENT_DYNCREATE(CMyRainmeterTextView, CEditView)

CMyRainmeterTextView::CMyRainmeterTextView()
{
	
}

CMyRainmeterTextView::~CMyRainmeterTextView()
{
}

BEGIN_MESSAGE_MAP(CMyRainmeterTextView, CEditView)
	ON_EN_CHANGE(AFX_IDW_PANE_FIRST, OnEditChange)
END_MESSAGE_MAP()


// CMyRainmeterTextView 诊断

#ifdef _DEBUG
void CMyRainmeterTextView::AssertValid() const
{
	CEditView::AssertValid();
}

#ifndef _WIN32_WCE
void CMyRainmeterTextView::Dump(CDumpContext& dc) const
{
	CEditView::Dump(dc);
}


#endif
#endif //_DEBUG

void CMyRainmeterTextView::SetText( CString sText )
{
	SetWindowText(sText);
}

CString CMyRainmeterTextView::GetText()
{
	CString sTemp;	
	GetWindowText(sTemp);
	return sTemp;
}

// CMyRainmeterTextView 消息处理程序


void CMyRainmeterTextView::OnEditChange()
{
	CMyRainmeterDoc* pDoc = (CMyRainmeterDoc*)GetDocument();
	pDoc->m_Text = GetText();
}

BOOL CMyRainmeterTextView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: 在此添加专用代码和/或调用基类
	//cs.style |= ES_READONLY;
	return CEditView::PreCreateWindow(cs);
}
