
// MyRainmeterView.cpp : CMyRainmeterView 类的实现
//

#include "stdafx.h"
// SHARED_HANDLERS 可以在实现预览、缩略图和搜索筛选器句柄的
// ATL 项目中进行定义，并允许与该项目共享文档代码。
#ifndef SHARED_HANDLERS
#include "MyRainmeter.h"
#endif

#include "MyRainmeterDoc.h"
#include "MyRainmeterView.h"
#include "Meter.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CMyRainmeterView

IMPLEMENT_DYNCREATE(CMyRainmeterView, CScrollView)

BEGIN_MESSAGE_MAP(CMyRainmeterView, CScrollView)
	// 标准打印命令
	ON_COMMAND(ID_FILE_PRINT, &CScrollView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CScrollView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CMyRainmeterView::OnFilePrintPreview)
	ON_WM_CONTEXTMENU()
	ON_WM_RBUTTONUP()
	ON_COMMAND(ID_VIEW_CODE, &CMyRainmeterView::OnViewCode)
END_MESSAGE_MAP()

// CMyRainmeterView 构造/析构

CMyRainmeterView::CMyRainmeterView()
{
	// TODO: 在此处添加构造代码
	
}

CMyRainmeterView::~CMyRainmeterView()
{
	
}

BOOL CMyRainmeterView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: 在此处通过修改
	//  CREATESTRUCT cs 来修改窗口类或样式

	return CView::PreCreateWindow(cs);
}

// CMyRainmeterView 绘制

void CMyRainmeterView::OnDraw(CDC* pDC)
{
	CMyRainmeterDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	// TODO: 在此处为本机数据添加绘制代码
	//设置背景图片
	//CPaintDC dc(this);
	//CImage nImage;
	//nImage.Load(pDoc->systemBgPath);//加载图片
	//HBITMAP hBitmap=nImage.Detach();//获得图片句柄用以转换
	//CBitmap m_bmpBK;
	//m_bmpBK.DeleteObject();
	//m_bmpBK.Attach(hBitmap);//转换为CBitmap对象
	//CRect rect;
	//GetClientRect(&rect);//获得目标尺寸，即窗口客户区的上左下右坐标
	//BITMAP bitMap;//位图结构体
	//m_bmpBK.GetBitmap(&bitMap);//传递指针
	//CDC dcMem;//目标DC
	//dcMem.CreateCompatibleDC(&dc);//创建与dc兼容的内存DC
	//dcMem.SelectObject(&m_bmpBK);//将位图对象m_bmpBK载入内存DC
	//dc.StretchBlt(0,0,rect.Width(),rect.Height(),&dcMem,0,0,bitMap.bmWidth,bitMap.bmHeight,SRCCOPY);
	//pDC->SetStretchBltMode(STRETCH_HALFTONE); 
	//pDC->StretchBlt(0,0,rect.Width(),rect.Height(),&dcMem,0,0,bitMap.bmWidth,bitMap.bmHeight,SRCCOPY);	

	//获取屏幕大小 包括任务栏
	int cx = GetSystemMetrics(SM_CXFULLSCREEN);
	int cy = GetSystemMetrics(SM_CYFULLSCREEN);
	// 当且仅当图片未加载时加载
	if(backgroundImage.IsNull())
		backgroundImage.Load(pDoc->systemBgPath);
	if(!backgroundImage.IsNull())
		backgroundImage.Draw(pDC->m_hDC,0,0,cx, cy);
	else
		AfxMessageBox(_T("桌面背景加载失败！请重新设置背景后试试，如果问题仍然存在，请与我联系~~"));
	SetScrollSizes(MM_TEXT,CSize(cx, cy));    
	
	
	//AfxMessageBox(pDoc->systemBgPath);
}

// 
void CMyRainmeterView::OnInitialUpdate()
{
	CScrollView::OnInitialUpdate();
	
	int cx = GetSystemMetrics(SM_CXFULLSCREEN);
	int cy = GetSystemMetrics(SM_CYFULLSCREEN);
	SetScrollSizes(MM_TEXT,CSize(cx, cy)); 
}


// CMyRainmeterView 打印


void CMyRainmeterView::OnFilePrintPreview()
{
#ifndef SHARED_HANDLERS
	AFXPrintPreview(this);
#endif
}

BOOL CMyRainmeterView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// 默认准备
	return DoPreparePrinting(pInfo);
}

void CMyRainmeterView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: 添加额外的打印前进行的初始化过程
}

void CMyRainmeterView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: 添加打印后进行的清理过程
}

void CMyRainmeterView::OnRButtonUp(UINT /* nFlags */, CPoint point)
{
	ClientToScreen(&point);
	OnContextMenu(this, point);
}

void CMyRainmeterView::OnContextMenu(CWnd* /* pWnd */, CPoint point)
{
#ifndef SHARED_HANDLERS
	theApp.GetContextMenuManager()->ShowPopupMenu(IDR_POPUP_EDIT, point.x, point.y, this, TRUE);
#endif
}


// CMyRainmeterView 诊断

#ifdef _DEBUG
void CMyRainmeterView::AssertValid() const
{
	CView::AssertValid();
}

void CMyRainmeterView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CMyRainmeterDoc* CMyRainmeterView::GetDocument() const // 非调试版本是内联的
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CMyRainmeterDoc)));
	return (CMyRainmeterDoc*)m_pDocument;
}
#endif //_DEBUG


// CMyRainmeterView 消息处理程序


void CMyRainmeterView::OnViewCode()
{
	// TODO: 在此添加命令处理程序代码
	
	POSITION tDocTemplatePos = theApp.m_pDocManager->GetFirstDocTemplatePosition();
	CDocTemplate* pDocTemplate = theApp.m_pDocManager->GetNextDocTemplate(tDocTemplatePos);
	pDocTemplate = theApp.m_pDocManager->GetNextDocTemplate(tDocTemplatePos);
	if (pDocTemplate!=NULL)
	{
		pDocTemplate->OpenDocumentFile(NULL);
	}
		
}
