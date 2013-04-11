
// MyRainmeterGraphView.cpp : CMyRainmeterGraphView 类的实现
//

#include "stdafx.h"
// SHARED_HANDLERS 可以在实现预览、缩略图和搜索筛选器句柄的
// ATL 项目中进行定义，并允许与该项目共享文档代码。
#ifndef SHARED_HANDLERS
#include "MyRainmeter.h"
#endif

#include "MyRainmeterDoc.h"
#include "MyRainmeterGraphView.h"
#include "Meter.h"
#include "MeterBar.h"
#include "MeterImage.h"
#include "MainFrm.h"
#include "MeterString.h"


#ifdef _DEBUG
#define new DEBUG_NEW
#endif


#define ZOOM_MAX            2
#define ZOOM_MIN            0.25
#define ZOOM_NORMAL         1


// CMyRainmeterGraphView

IMPLEMENT_DYNCREATE(CMyRainmeterGraphView, CScrollView)

BEGIN_MESSAGE_MAP(CMyRainmeterGraphView, CScrollView)
	//{{AFX_MSG_MAP(CDemoView)
	//ON_COMMAND(ID_DEMO_TOGGLERULERS, OnRulersTogglerulers)
	//ON_UPDATE_COMMAND_UI(ID_DEMO_TOGGLERULERS, OnUpdateRulersTogglerulers)
	ON_WM_ERASEBKGND()
	ON_WM_LBUTTONDOWN()
	ON_WM_MOUSEMOVE()
	ON_WM_VSCROLL()
	ON_WM_HSCROLL()
	ON_WM_SETCURSOR()
	//}}AFX_MSG_MAP
	// 标准打印命令
	ON_COMMAND(ID_FILE_PRINT, &CScrollView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CScrollView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CMyRainmeterGraphView::OnFilePrintPreview)
	ON_WM_CONTEXTMENU()
	ON_WM_RBUTTONUP()
	ON_COMMAND(ID_VIEW_CODE, &CMyRainmeterGraphView::OnViewCode)
	ON_WM_MOUSEMOVE()
	ON_COMMAND(ID_EDIT_PROPERTIES, &CMyRainmeterGraphView::OnEditProperties)
END_MESSAGE_MAP()

// CMyRainmeterGraphView 构造/析构

CMyRainmeterGraphView::CMyRainmeterGraphView()
{
	// TODO: 在此处添加构造代码
	m_pParent           = NULL;
	m_BrushBackGround.CreateHatchBrush(HS_DIAGCROSS, RGB(191, 191, 191));
	m_bShowRulers       = TRUE;
	int cx = GetSystemMetrics(SM_CXFULLSCREEN);
	int cy = GetSystemMetrics(SM_CYFULLSCREEN);
	m_ViewSize = CSize(cx, cy);

	m_imageManager.SetIcons(IDB_TRASH, 0, 0, CSize(48, 48));
	m_bDragging = FALSE;
}
	
CSize CMyRainmeterGraphView::GetViewSize()
{
	return m_ViewSize;
}


CMyRainmeterGraphView::~CMyRainmeterGraphView()
{
	//m_BackgroundImage.Destroy();
	m_BrushBackGround.DeleteObject();
	
}

BOOL CMyRainmeterGraphView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: 在此处通过修改
	//  CREATESTRUCT cs 来修改窗口类或样式

	return CView::PreCreateWindow(cs);
}

// CMyRainmeterGraphView 绘制

void CMyRainmeterGraphView::OnDraw(CDC* pDC)
{
	CMyRainmeterDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	//CDC dc;
	CDC* pDrawDC = pDC;

	// only paint the rect that needs repainting
	CRect client;
	pDC->GetClipBox(client);
	CRect rect = client;
	
	// paint background

	if (!pDC->IsPrinting())
		DrawBackground(pDC);

	pDoc->Draw(pDrawDC, GetTaskPanel());


	CRect rcTrash(rect.right - 72, rect.bottom - 72, rect.right - 12, rect.bottom - 12);
//	pDC->FillSolidRect(rcTrash, GetSysColor(COLOR_3DFACE));
	pDC->Draw3dRect(rcTrash, GetSysColor(COLOR_3DHIGHLIGHT), GetSysColor(COLOR_3DSHADOW));

	CXTPImageManagerIcon* pImage = m_imageManager.GetImage(0, 48);
	if (pImage)
	{
		CPoint ptImage((rcTrash.right + rcTrash.left - 48) / 2, (rcTrash.top + rcTrash.bottom - 48) / 2);
		pImage->Draw(pDC, ptImage, pImage->GetIcon());
	}
		
}

void CMyRainmeterGraphView::DrawBackground( CDC* pDC )
{
	CMyRainmeterDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	// 当且仅当图片未加载时加载
	if(m_BackgroundImage.IsNull())
		m_BackgroundImage.Load(pDoc->m_SystemBgPath);
	if(!m_BackgroundImage.IsNull())
	{
	//	m_BackgroundImage.Draw(pDC->m_hDC,0,0, m_DesktopSize.cx, m_DesktopSize.cy);
		HBITMAP hBitmap=m_BackgroundImage.Detach();//获得图片句柄用以转换
		CBitmap m_bmpBK;
		m_bmpBK.DeleteObject();
		m_bmpBK.Attach(hBitmap);//转换为CBitmap对象
		CRect rect;
		GetClientRect(&rect);//获得目标尺寸，即窗口客户区的上左下右坐标
		BITMAP bitMap;//位图结构体
		m_bmpBK.GetBitmap(&bitMap);//传递指针
		CDC dcMem;//目标DC
		dcMem.CreateCompatibleDC(pDC);//创建与dc兼容的内存DC
		dcMem.SelectObject(&m_bmpBK);//将位图对象m_bmpBK载入内存DC
		//dcMem.SetStretchBltMode(STRETCH_HALFTONE); 
		//dcMem.StretchBlt(0,0,rect.Width(),rect.Height(),&dcMem,0,0,m_DesktopSize.cx,m_DesktopSize.cy,SRCCOPY);
		
		pDC->SetStretchBltMode(STRETCH_HALFTONE); 
		CPoint point = GetScrollPosition();
		pDC->StretchBlt(0,0,m_ViewSize.cx,m_ViewSize.cy,&dcMem,0,0,bitMap.bmWidth,bitMap.bmHeight,SRCCOPY);
		//pDC->BitBlt(point.x,point.y,rect.Width(),rect.Height(),&dcMem, point.x,point.y,SRCCOPY);	
		m_bmpBK.DeleteObject();
		dcMem.DeleteDC();
	}
	else
		AfxMessageBox(_T("桌面背景加载失败！请重新设置背景后试试，如果问题仍然存在，请与我联系~~"));	
}

// 
void CMyRainmeterGraphView::OnInitialUpdate()
{
	CScrollView::OnInitialUpdate();

	m_wndDragTarget.Register(this);		// 注册COleDataObject对象以实现拖拽
	
	SetScrollSizes(MM_TEXT, m_ViewSize);		//滚动区域
	m_pParent = ((CChildFrame*)GetParentFrame());	//父窗口
	m_pParent->ShowRulers(TRUE);				//开启标尺
	OnUpdate(NULL, 0, NULL);

	EnableToolTips(TRUE);
	m_ToolTip.Create(this); 
	m_ToolTip.Activate(TRUE);
//	m_ToolTip.AddTool(this,_T("提示信息!")); 	
	m_ToolTip.SetDelayTime(TTDT_INITIAL, 100);// 100ms
	m_ToolTip.SetDelayTime(TTDT_AUTOPOP, 1000*4);// 4s
	m_ToolTip.SetDelayTime(TTDT_RESHOW, 100);// 100ms
}


// CMyRainmeterGraphView 打印


void CMyRainmeterGraphView::OnFilePrintPreview()
{
#ifndef SHARED_HANDLERS
	AFXPrintPreview(this);
#endif
}

BOOL CMyRainmeterGraphView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// 默认准备
	return DoPreparePrinting(pInfo);
}

void CMyRainmeterGraphView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: 添加额外的打印前进行的初始化过程
}

void CMyRainmeterGraphView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: 添加打印后进行的清理过程
}

void CMyRainmeterGraphView::OnRButtonUp(UINT /* nFlags */, CPoint point)
{
	ClientToScreen(&point);
	OnContextMenu(this, point);
}

void CMyRainmeterGraphView::OnContextMenu(CWnd* /* pWnd */, CPoint point)
{
#ifndef SHARED_HANDLERS
	theApp.GetContextMenuManager()->ShowPopupMenu(IDR_POPUP_GRAPH, point.x, point.y, this, TRUE);
#endif
}


// CMyRainmeterGraphView 诊断

#ifdef _DEBUG
void CMyRainmeterGraphView::AssertValid() const
{
	CView::AssertValid();
}

void CMyRainmeterGraphView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CMyRainmeterDoc* CMyRainmeterGraphView::GetDocument() const // 非调试版本是内联的
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CMyRainmeterDoc)));
	return (CMyRainmeterDoc*)m_pDocument;
}
#endif //_DEBUG


// CMyRainmeterGraphView 消息处理程序



void CMyRainmeterGraphView::OnViewCode()
{
	// TODO: 在此添加命令处理程序代码
	GetDocument()->SwitchViewCodeFrame();	
}

void CMyRainmeterGraphView::OnEditProperties()
{
	// TODO: 在此添加命令处理程序代码
	CMainFrame* pMain = (CMainFrame*)AfxGetMainWnd();
	//pMain->GetPropWnd()->Slide(TRUE);
	pMain->GetPropWnd()->ShowPane(TRUE, FALSE, TRUE);
	
}

void CMyRainmeterGraphView::OnUpdate(CView* /*pSender*/, LPARAM /*lHint*/, CObject* /*pHint*/)
{
	// TODO: 在此添加专用代码和/或调用基类
	
	SetScrollSizes(MM_TEXT, m_ViewSize);   
	UpdateRulersInfo(RW_POSITION, GetScrollPosition());
	Invalidate();	
}

void CMyRainmeterGraphView::OnRulersTogglerulers() 
{
	m_bShowRulers = !m_bShowRulers;
	m_pParent->ShowRulers(m_bShowRulers);
}

void CMyRainmeterGraphView::OnUpdateRulersTogglerulers(CCmdUI* pCmdUI) 
{
	pCmdUI->SetCheck(m_bShowRulers);
}

void CMyRainmeterGraphView::OnMouseMove(UINT nFlags, CPoint point)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值

	// Update the ruler mark
	UpdateRulersInfo(RW_POSITION, GetScrollPosition(), point);

	CScrollView::OnMouseMove(nFlags, point);
}



BOOL CMyRainmeterGraphView::OnEraseBkgnd( CDC* pDC )
{
	//FillOutsideRect(pDC, &m_BrushBackGround);
	return TRUE;
}

void CMyRainmeterGraphView::OnLButtonDown( UINT nFlags, CPoint point )
{
	// TODO:
	
	CPoint relPoint = GetScrollPosition()+point;
	int nHit = HitTest(relPoint);
	if(nHit<0)
	{
		GetDocument()->m_pCurRmCtrl = NULL;
		CMainFrame* pMainFrm = (CMainFrame*)AfxGetMainWnd();
		CPropertiesWnd* pPropWnd = pMainFrm->GetPropWnd();
		pPropWnd->SetCurObjProperties(NULL);
		return;
	}
	CRmControl* pRmCtrl = (nHit >= 0? GetDocument()->m_arrItems[nHit]: NULL);
	if(!pRmCtrl)
		return;

	CXTPTaskPanelGroupItem* pItem = pRmCtrl->m_pItem;

	if (!pItem)
		return;

	GetDocument()->m_pCurRmCtrl = pRmCtrl;
	CMainFrame* pMainFrm = (CMainFrame*)AfxGetMainWnd();
	CPropertiesWnd* pPropWnd = pMainFrm->GetPropWnd();
	pPropWnd->SetCurObjProperties(pRmCtrl);


	COleDataSource ds;
	if (!pItem->PrepareDrag(ds))
		return;

	m_bDragging = TRUE;

	DROPEFFECT dropEffect = ds.DoDragDrop(DROPEFFECT_COPY|DROPEFFECT_MOVE);

	m_bDragging = FALSE;

	/*if (dropEffect == DROPEFFECT_MOVE)
	{
		pItem->InternalRelease();
		GetDocument()->RemoveAt(nHit);
		GetDocument()->m_pCurRmCtrl = NULL;
		GetDocument()->m_arrItems.RemoveAt(nHit);
	}*/

	Invalidate(FALSE);
	//CScrollView::OnLButtonDown(nFlags, point);
}

void CMyRainmeterGraphView::OnVScroll( UINT nSBCode, UINT nPos, CScrollBar* pScrollBar )
{
	UpdateRulersInfo(RW_VSCROLL, GetScrollPosition());
	Invalidate(FALSE);

	CScrollView::OnVScroll(nSBCode, nPos, pScrollBar);
}

void CMyRainmeterGraphView::OnHScroll( UINT nSBCode, UINT nPos, CScrollBar* pScrollBar )
{
	UpdateRulersInfo(RW_HSCROLL, GetScrollPosition());
	Invalidate(FALSE);

	CScrollView::OnHScroll(nSBCode, nPos, pScrollBar);
}

void CMyRainmeterGraphView::UpdateRulersInfo( int nMessage, CPoint ScrollPos, CPoint Pos /*= CPoint(0, 0)*/ )
{
	if (!m_pParent)
		return;
	stRULER_INFO pRulerInfo;
	pRulerInfo.uMessage    = nMessage;
	pRulerInfo.ScrollPos   = ScrollPos;
	pRulerInfo.Pos         = Pos;
	pRulerInfo.DocSize     = m_ViewSize;
	pRulerInfo.fZoomFactor = 1;

	m_pParent->UpdateRulersInfo(pRulerInfo);
}


DROPEFFECT CMyRainmeterGraphView::OnDragOver(COleDataObject* pDataObject, DWORD dwKeyState, CPoint point)
{
	UpdateRulersInfo(RW_POSITION, GetScrollPosition(), point);
	// TODO: 在此添加专用代码和/或调用基类
	if (!pDataObject || !pDataObject->IsDataAvailable(CXTPTaskPanel::GetClipboardFormat()))
		return DROPEFFECT_NONE;
	
	if (!m_bDragging || ((dwKeyState & MK_CONTROL) == MK_CONTROL))
		return DROPEFFECT_COPY;

	if (PtInTrash(point))
	{
		return DROPEFFECT_MOVE;
	}
	CRmControl* pCurRmCtrl = GetDocument()->m_pCurRmCtrl;
	if(pCurRmCtrl != NULL)
	{
		/*CMainFrame* pMainFrm = (CMainFrame*)AfxGetMainWnd();
		CPropertiesWnd* pPropWnd = pMainFrm->GetPropWnd();
		pPropWnd->SetCurObjProperties(pCurRmCtrl);*/
		pCurRmCtrl->UpdateProperties();
	}

	return DROPEFFECT_MOVE;
	
//	return CScrollView::OnDragOver(pDataObject, dwKeyState, point);
}


BOOL CMyRainmeterGraphView::OnDrop(COleDataObject* pDataObject, DROPEFFECT dropEffect, CPoint point)
{
	CMyRainmeterDoc *pDoc = GetDocument();
	if(!pDoc)return FALSE;
	// TODO: 在此添加专用代码和/或调用基类
	if (PtInTrash(point))
	{
		pDoc->Remove(GetDocument()->m_pCurRmCtrl);
		pDoc->m_pCurRmCtrl = NULL;
		pDoc->UpdateAllViews(this);
		return TRUE;
	}
	CXTPTaskPanelGroupItem* pItemDrop = (CXTPTaskPanelGroupItem*)CXTPTaskPanelItem::CreateFromOleData(pDataObject);

	if (!pItemDrop)
		return FALSE;

	ASSERT_KINDOF(CXTPTaskPanelGroupItem, pItemDrop);

	CString itemCaption = pItemDrop->GetCaption();
	
	
	CPoint ScrollPos = this->GetScrollPosition();
	CRect itemRect = CRect(point.x + ScrollPos.x - 16, point.y + ScrollPos.y - 16, point.x +ScrollPos.x + 16, point.y + ScrollPos.y + 16);
	pItemDrop->SetItemRect(itemRect);
	
//	pItemDrop->SetTooltip(itemCaption);
	m_ToolTip.AddTool(this, itemCaption, itemRect, 1);

	CRmControl* pRmCtrl;
	if (dropEffect == DROPEFFECT_COPY)
	{	
		if (itemCaption.CompareNoCase(_T("Bar")) == 0)
		{
			pRmCtrl = new CMeterBar(pItemDrop);
		}
		else if (itemCaption.CompareNoCase(_T("Image")) == 0)
		{
			CMeterImage* pMeterImage = new CMeterImage(pItemDrop, this);
			pMeterImage->SetMeterName(_T("Image1"));
			pRmCtrl = pMeterImage;
			//pRmCtrl = new CMeterImage(pItemDrop, this);					
		} 
		else if (itemCaption.CompareNoCase(_T("String")) == 0)
		{
			CMeterString* pMeterString = new CMeterString(pItemDrop, this);
			pMeterString->SetMeterName(_T("String1"));
			pRmCtrl = pMeterString;
		} 
		else
		{
			pRmCtrl = new CRmControl(pItemDrop, this);
		}
		pDoc->m_pCurRmCtrl = pRmCtrl;
		pDoc->Add(pRmCtrl);
	}
	else if (dropEffect == DROPEFFECT_MOVE)
	{
		pRmCtrl = pDoc->m_pCurRmCtrl;
		pRmCtrl->m_pItem = pItemDrop;
		pRmCtrl->UpdateProperties();
	}
	else
	{
		return TRUE;
	}
		
	CMainFrame* pMainFrm = (CMainFrame*)AfxGetMainWnd();
	CPropertiesWnd* pPropWnd = pMainFrm->GetPropWnd();
	pPropWnd->SetCurObjProperties(pRmCtrl);

	Invalidate(FALSE);
	pDoc->UpdateAllViews(this);

	return TRUE;
//	return CScrollView::OnDrop(pDataObject, dropEffect, point);
}



BOOL CMyRainmeterGraphView::PtInTrash(CPoint point)
{
	CPaintDC dc(this);
	CRect client;
	dc.GetClipBox(client);
	//CRect rc = client;
	CXTPClientRect rc(this);
	CRect rcTrash(rc.right - 72, rc.bottom - 72, rc.right - 12, rc.bottom - 12);
	
	return rcTrash.PtInRect(point);
}

CXTPTaskPanel* CMyRainmeterGraphView::GetTaskPanel()
{
	//CWnd* pSplitterWnd = GetParentFrame()->GetDlgItem(IDS_KIT_VIEW);
	CMainFrame* pMainWnd = (CMainFrame *)AfxGetMainWnd();
	CKitView* pKitViewPane = pMainWnd->GetKitVew();
	
	ASSERT_KINDOF(CKitView, pKitViewPane);

	return (CXTPTaskPanel*)pKitViewPane->GetTaskPanel();
}

int CMyRainmeterGraphView::HitTest( CPoint point ) const
{	
	for (int i = (int)GetDocument()->m_arrItems.GetSize() - 1; i >= 0; i--)
	{
		CRmControl* pRmCtrl = GetDocument()->m_arrItems[i];
		CXTPTaskPanelGroupItem* pItem=pRmCtrl->m_pItem;

		if (pItem->GetItemRect().PtInRect(point))
			return i;
	}
	return -1;
}



BOOL CMyRainmeterGraphView::PreTranslateMessage(MSG* pMsg)
{
	// TODO: 在此添加专用代码和/或调用基类
	{
		m_ToolTip.RelayEvent(pMsg);
	}
	
	return CScrollView::PreTranslateMessage(pMsg);
}




