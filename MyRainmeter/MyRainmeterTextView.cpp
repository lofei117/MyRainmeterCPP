// MyRainmeterTextView.cpp : 实现文件
//

#include "stdafx.h"
#include "MyRainmeter.h"
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
END_MESSAGE_MAP()


// CMyRainmeterTextView 绘图

void CMyRainmeterTextView::OnDraw(CDC* pDC)
{
	CDocument* pDoc = GetDocument();
	// TODO: 在此添加绘制代码
}


// CMyRainmeterTextView 诊断

#ifdef _DEBUG
void CMyRainmeterTextView::AssertValid() const
{
	CView::AssertValid();
}

#ifndef _WIN32_WCE
void CMyRainmeterTextView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}
#endif
#endif //_DEBUG


// CMyRainmeterTextView 消息处理程序
