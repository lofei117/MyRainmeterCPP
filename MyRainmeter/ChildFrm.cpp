
// ChildFrm.cpp : CChildFrame 类的实现
//

#include "stdafx.h"
#include "MyRainmeter.h"
#include "MyRainmeterDoc.h"

#include "Corner.h"
#include "VRuler.h"
#include "HRuler.h"

#include "ChildFrm.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

// CChildFrame

IMPLEMENT_DYNCREATE(CChildFrame, CMDIChildWndEx)

BEGIN_MESSAGE_MAP(CChildFrame, CMDIChildWndEx)
	ON_WM_CLOSE()
END_MESSAGE_MAP()

// CChildFrame 构造/析构

CChildFrame::CChildFrame()
{
	// TODO: 在此添加成员初始化代码
	
}

CChildFrame::~CChildFrame()
{
}


BOOL CChildFrame::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: 在此处通过修改 CREATESTRUCT cs 来修改窗口类或样式
	if( !CMDIChildWndEx::PreCreateWindow(cs) )
		return FALSE;

	return TRUE;
}

// CChildFrame 诊断

#ifdef _DEBUG
void CChildFrame::AssertValid() const
{
	CMDIChildWndEx::AssertValid();
}

void CChildFrame::Dump(CDumpContext& dc) const
{
	CMDIChildWndEx::Dump(dc);
}
#endif //_DEBUG

// CChildFrame 消息处理程序


BOOL CChildFrame::OnCreateClient(LPCREATESTRUCT lpcs, CCreateContext* pContext)
{
	// TODO: 在此添加专用代码和/或调用基类
	if(pContext->m_pNewViewClass->m_lpszClassName == "CMyRainmeterTextView")
	{
		return CMDIChildWndEx::OnCreateClient(lpcs, pContext);
	}
	if (!m_Rulers.CreateRulers(this, pContext)) {
		TRACE("Error creation of rulers\n");
		return CMDIChildWnd::OnCreateClient(lpcs, pContext);
	}

	return TRUE;
	//return CMDIChildWndEx::OnCreateClient(lpcs, pContext);
}


void CChildFrame::OnClose()
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	CMDIChildWndEx::OnClose();
}

void CChildFrame::ShowRulers( BOOL bShow )
{
	m_Rulers.ShowRulers(bShow);
}

void CChildFrame::UpdateRulersInfo(stRULER_INFO stRulerInfo)
{
	m_Rulers.UpdateRulersInfo(stRulerInfo);
}
	