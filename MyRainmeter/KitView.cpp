
#include "stdafx.h"
#include "MainFrm.h"
#include "KitView.h"
#include "Resource.h"
#include "MyRainmeter.h"

class CKitViewMenuButton : public CMFCToolBarMenuButton
{
	friend class CKitView;

	DECLARE_SERIAL(CKitViewMenuButton)

public:
	CKitViewMenuButton(HMENU hMenu = NULL) : CMFCToolBarMenuButton((UINT)-1, hMenu, -1)
	{
	}

	virtual void OnDraw(CDC* pDC, const CRect& rect, CMFCToolBarImages* pImages, BOOL bHorz = TRUE,
		BOOL bCustomizeMode = FALSE, BOOL bHighlight = FALSE, BOOL bDrawBorder = TRUE, BOOL bGrayDisabledButtons = TRUE)
	{
		pImages = CMFCToolBar::GetImages();

		CAfxDrawState ds;
		pImages->PrepareDrawImage(ds);

		CMFCToolBarMenuButton::OnDraw(pDC, rect, pImages, bHorz, bCustomizeMode, bHighlight, bDrawBorder, bGrayDisabledButtons);

		pImages->EndDrawImage(ds);
	}
};

IMPLEMENT_SERIAL(CKitViewMenuButton, CMFCToolBarMenuButton, 1)

	//////////////////////////////////////////////////////////////////////
	// 构造/析构
	//////////////////////////////////////////////////////////////////////

	CKitView::CKitView()
{
	m_nCurrSort = ID_SORTING_GROUPBYTYPE;
}

CKitView::~CKitView()
{
}

BEGIN_MESSAGE_MAP(CKitView, CDockablePane)
	ON_WM_CREATE()
	ON_WM_SIZE()
	ON_WM_CONTEXTMENU()
	ON_COMMAND(ID_CLASS_ADD_MEMBER_FUNCTION, OnClassAddMemberFunction)
	ON_COMMAND(ID_CLASS_ADD_MEMBER_VARIABLE, OnClassAddMemberVariable)
	ON_COMMAND(ID_CLASS_DEFINITION, OnClassDefinition)
	ON_COMMAND(ID_CLASS_PROPERTIES, OnClassProperties)
	ON_COMMAND(ID_NEW_FOLDER, OnNewFolder)
	ON_WM_PAINT()
	ON_WM_SETFOCUS()
	ON_COMMAND_RANGE(ID_SORTING_GROUPBYTYPE, ID_SORTING_SORTBYACCESS, OnSort)
	ON_UPDATE_COMMAND_UI_RANGE(ID_SORTING_GROUPBYTYPE, ID_SORTING_SORTBYACCESS, OnUpdateSort)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CKitView 消息处理程序

int CKitView::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CDockablePane::OnCreate(lpCreateStruct) == -1)
		return -1;

	CRect rectDummy;
	rectDummy.SetRectEmpty();

	// 创建视图:
	const DWORD dwViewStyle = WS_CHILD | WS_VISIBLE | TVS_HASLINES | TVS_LINESATROOT | TVS_HASBUTTONS | WS_CLIPSIBLINGS | WS_CLIPCHILDREN;

	if (!m_wndKitView.Create(dwViewStyle, rectDummy, this, 2))
	{
		TRACE0("未能创建工具箱视图\n");
		return -1;      // 未能创建
	}

	// 加载图像:
	m_wndToolBar.Create(this, AFX_DEFAULT_TOOLBAR_STYLE, IDR_SORT);
	m_wndToolBar.LoadToolBar(IDR_SORT, 0, 0, TRUE /* 已锁定*/);

	OnChangeVisualStyle();

	m_wndToolBar.SetPaneStyle(m_wndToolBar.GetPaneStyle() | CBRS_TOOLTIPS | CBRS_FLYBY);
	m_wndToolBar.SetPaneStyle(m_wndToolBar.GetPaneStyle() & ~(CBRS_GRIPPER | CBRS_SIZE_DYNAMIC | CBRS_BORDER_TOP | CBRS_BORDER_BOTTOM | CBRS_BORDER_LEFT | CBRS_BORDER_RIGHT));

	m_wndToolBar.SetOwner(this);

	// 所有命令将通过此控件路由，而不是通过主框架路由:
	m_wndToolBar.SetRouteCommandsViaFrame(FALSE);

	CMenu menuSort;
	menuSort.LoadMenu(IDR_POPUP_SORT);

	m_wndToolBar.ReplaceButton(ID_SORT_MENU, CKitViewMenuButton(menuSort.GetSubMenu(0)->GetSafeHmenu()));
	
	CKitViewMenuButton* pButton =  DYNAMIC_DOWNCAST(CKitViewMenuButton, m_wndToolBar.GetButton(0));

	if (pButton != NULL)
	{
		pButton->m_bText = FALSE;
		pButton->m_bImage = TRUE;
		pButton->SetImage(GetCmdMgr()->GetCmdImage(m_nCurrSort));
		pButton->SetMessageWnd(this);
	}

	// 填入一些静态树视图数据(此处只需填入虚拟代码，而不是复杂的数据)
	FillKitView();

	return 0;
}

void CKitView::OnSize(UINT nType, int cx, int cy)
{
	CDockablePane::OnSize(nType, cx, cy);
	AdjustLayout();
}

void CKitView::FillKitView()
{
	HTREEITEM hRoot = m_wndKitView.InsertItem(_T("FakeApp 类"), 0, 0);
	m_wndKitView.SetItemState(hRoot, TVIS_BOLD, TVIS_BOLD);

	HTREEITEM hClass = m_wndKitView.InsertItem(_T("CFakeAboutDlg"), 1, 1, hRoot);
	m_wndKitView.InsertItem(_T("CFakeAboutDlg()"), 3, 3, hClass);

	m_wndKitView.Expand(hRoot, TVE_EXPAND);

	hClass = m_wndKitView.InsertItem(_T("CFakeApp"), 1, 1, hRoot);
	m_wndKitView.InsertItem(_T("CFakeApp()"), 3, 3, hClass);
	m_wndKitView.InsertItem(_T("InitInstance()"), 3, 3, hClass);
	m_wndKitView.InsertItem(_T("OnAppAbout()"), 3, 3, hClass);

	hClass = m_wndKitView.InsertItem(_T("CFakeAppDoc"), 1, 1, hRoot);
	m_wndKitView.InsertItem(_T("CFakeAppDoc()"), 4, 4, hClass);
	m_wndKitView.InsertItem(_T("~CFakeAppDoc()"), 3, 3, hClass);
	m_wndKitView.InsertItem(_T("OnNewDocument()"), 3, 3, hClass);

	hClass = m_wndKitView.InsertItem(_T("CFakeAppView"), 1, 1, hRoot);
	m_wndKitView.InsertItem(_T("CFakeAppView()"), 4, 4, hClass);
	m_wndKitView.InsertItem(_T("~CFakeAppView()"), 3, 3, hClass);
	m_wndKitView.InsertItem(_T("GetDocument()"), 3, 3, hClass);
	m_wndKitView.Expand(hClass, TVE_EXPAND);

	hClass = m_wndKitView.InsertItem(_T("CFakeAppFrame"), 1, 1, hRoot);
	m_wndKitView.InsertItem(_T("CFakeAppFrame()"), 3, 3, hClass);
	m_wndKitView.InsertItem(_T("~CFakeAppFrame()"), 3, 3, hClass);
	m_wndKitView.InsertItem(_T("m_wndMenuBar"), 6, 6, hClass);
	m_wndKitView.InsertItem(_T("m_wndToolBar"), 6, 6, hClass);
	m_wndKitView.InsertItem(_T("m_wndStatusBar"), 6, 6, hClass);

	hClass = m_wndKitView.InsertItem(_T("Globals"), 2, 2, hRoot);
	m_wndKitView.InsertItem(_T("theFakeApp"), 5, 5, hClass);
	m_wndKitView.Expand(hClass, TVE_EXPAND);
}

void CKitView::OnContextMenu(CWnd* pWnd, CPoint point)
{
	CTreeCtrl* pWndTree = (CTreeCtrl*)&m_wndKitView;
	ASSERT_VALID(pWndTree);

	if (pWnd != pWndTree)
	{
		CDockablePane::OnContextMenu(pWnd, point);
		return;
	}

	if (point != CPoint(-1, -1))
	{
		// 选择已单击的项:
		CPoint ptTree = point;
		pWndTree->ScreenToClient(&ptTree);

		UINT flags = 0;
		HTREEITEM hTreeItem = pWndTree->HitTest(ptTree, &flags);
		if (hTreeItem != NULL)
		{
			pWndTree->SelectItem(hTreeItem);
		}
	}

	pWndTree->SetFocus();
	CMenu menu;
	menu.LoadMenu(IDR_POPUP_SORT);

	CMenu* pSumMenu = menu.GetSubMenu(0);

	if (AfxGetMainWnd()->IsKindOf(RUNTIME_CLASS(CMDIFrameWndEx)))
	{
		CMFCPopupMenu* pPopupMenu = new CMFCPopupMenu;

		if (!pPopupMenu->Create(this, point.x, point.y, (HMENU)pSumMenu->m_hMenu, FALSE, TRUE))
			return;

		((CMDIFrameWndEx*)AfxGetMainWnd())->OnShowPopupMenu(pPopupMenu);
		UpdateDialogControls(this, FALSE);
	}
}

void CKitView::AdjustLayout()
{
	if (GetSafeHwnd() == NULL)
	{
		return;
	}

	CRect rectClient;
	GetClientRect(rectClient);

	int cyTlb = m_wndToolBar.CalcFixedLayout(FALSE, TRUE).cy;

	m_wndToolBar.SetWindowPos(NULL, rectClient.left, rectClient.top, rectClient.Width(), cyTlb, SWP_NOACTIVATE | SWP_NOZORDER);
	m_wndKitView.SetWindowPos(NULL, rectClient.left + 1, rectClient.top + cyTlb + 1, rectClient.Width() - 2, rectClient.Height() - cyTlb - 2, SWP_NOACTIVATE | SWP_NOZORDER);
}

BOOL CKitView::PreTranslateMessage(MSG* pMsg)
{
	return CDockablePane::PreTranslateMessage(pMsg);
}

void CKitView::OnSort(UINT id)
{
	if (m_nCurrSort == id)
	{
		return;
	}

	m_nCurrSort = id;

	CKitViewMenuButton* pButton =  DYNAMIC_DOWNCAST(CKitViewMenuButton, m_wndToolBar.GetButton(0));

	if (pButton != NULL)
	{
		pButton->SetImage(GetCmdMgr()->GetCmdImage(id));
		m_wndToolBar.Invalidate();
		m_wndToolBar.UpdateWindow();
	}
}

void CKitView::OnUpdateSort(CCmdUI* pCmdUI)
{
	pCmdUI->SetCheck(pCmdUI->m_nID == m_nCurrSort);
}

void CKitView::OnClassAddMemberFunction()
{
	AfxMessageBox(_T("添加成员函数..."));
}

void CKitView::OnClassAddMemberVariable()
{
	// TODO: 在此处添加命令处理程序代码
}

void CKitView::OnClassDefinition()
{
	// TODO: 在此处添加命令处理程序代码
}

void CKitView::OnClassProperties()
{
	// TODO: 在此处添加命令处理程序代码
}

void CKitView::OnNewFolder()
{
	AfxMessageBox(_T("新建文件夹..."));
}

void CKitView::OnPaint()
{
	CPaintDC dc(this); // 用于绘制的设备上下文

	CRect rectTree;
	m_wndKitView.GetWindowRect(rectTree);
	ScreenToClient(rectTree);

	rectTree.InflateRect(1, 1);
	dc.Draw3dRect(rectTree, ::GetSysColor(COLOR_3DSHADOW), ::GetSysColor(COLOR_3DSHADOW));
}

void CKitView::OnSetFocus(CWnd* pOldWnd)
{
	CDockablePane::OnSetFocus(pOldWnd);

	m_wndKitView.SetFocus();
}

void CKitView::OnChangeVisualStyle()
{
	m_KitViewImages.DeleteImageList();

	UINT uiBmpId = theApp.m_bHiColorIcons ? IDB_KIT_VIEW_24 : IDB_KIT_VIEW;

	CBitmap bmp;
	if (!bmp.LoadBitmap(uiBmpId))
	{
		TRACE(_T("无法加载位图: %x\n"), uiBmpId);
		ASSERT(FALSE);
		return;
	}

	BITMAP bmpObj;
	bmp.GetBitmap(&bmpObj);

	UINT nFlags = ILC_MASK;

	nFlags |= (theApp.m_bHiColorIcons) ? ILC_COLOR24 : ILC_COLOR4;

	m_KitViewImages.Create(16, bmpObj.bmHeight, nFlags, 0, 0);
	m_KitViewImages.Add(&bmp, RGB(255, 0, 0));

	m_wndKitView.SetImageList(&m_KitViewImages, TVSIL_NORMAL);

	m_wndToolBar.CleanUpLockedImages();
	m_wndToolBar.LoadBitmap(theApp.m_bHiColorIcons ? IDB_SORT_24 : IDR_SORT, 0, 0, TRUE /* 锁定*/);
}
