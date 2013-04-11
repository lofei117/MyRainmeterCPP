
#include "stdafx.h"
#include "MainFrm.h"
#include "KitView.h"
#include "Resource.h"
#include "MyRainmeter.h"



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
	ON_WM_PAINT()
	ON_WM_SETFOCUS()
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
	//dwViewStyle = WS_CHILD|WS_VISIBLE|WS_CLIPSIBLINGS|WS_CLIPCHILDREN|WS_TABSTOP
	
	if (!m_wndTaskPanel.Create(dwViewStyle, rectDummy, this, 1))
	{
		TRACE0("未能创建工具箱视图\n");
		return -1;      // 未能创建
	}
	m_wndTaskPanel.SetOwner(this);

	m_wndTaskPanel.GetImageManager()->SetIcons(IDB_TOOLBOXICONS, 0, 0, CSize(16, 16));
	m_wndTaskPanel.SetBehaviour(xtpTaskPanelBehaviourExplorer);
	m_wndTaskPanel.SetTheme(xtpTaskPanelThemeListViewOffice2003);
	m_wndTaskPanel.SetSelectItemOnFocus(TRUE);
	m_wndTaskPanel.AllowDrag(TRUE);

	OnChangeVisualStyle();

	CMenu menuSort;
	menuSort.LoadMenu(IDR_POPUP_SORT);

	// 填入一些静态树视图数据(此处只需填入虚拟代码，而不是复杂的数据)
	ResetToolboxItems();

	return 0;
}

void CKitView::OnSize(UINT nType, int cx, int cy)
{
	CDockablePane::OnSize(nType, cx, cy);
	AdjustLayout();
}

CXTPTaskPanelGroup* CKitView::CreateToolboxGroup( UINT nID )
{
	CXTPTaskPanelGroup* pFolder = m_wndTaskPanel.AddGroup(nID);

	CXTPTaskPanelGroupItem* pPointer = pFolder->AddLinkItem(ID_TOOLBOXITEM_POINTER, 0);
	pPointer->SetItemSelected(TRUE);
	pPointer->AllowDrag(FALSE);
	pPointer->AllowDrop(FALSE);
	pFolder->SetIconIndex(IDR_MAINFRAME);

	return pFolder;
}

void CKitView::ResetToolboxItems()
{
	m_wndTaskPanel.GetGroups()->Clear(FALSE);

	CXTPTaskPanelGroup* pMetersPane = CreateToolboxGroup(ID_TOOLBOXFOLDER_METERS);
	pMetersPane->AddLinkItem(ID_TOOLBOXITEM_BUTTON           ,1);
	pMetersPane->AddLinkItem(ID_TOOLBOXITEM_BITMAP			 ,2);
	pMetersPane->AddLinkItem(ID_TOOLBOXITEM_BAR				 ,3);
	pMetersPane->AddLinkItem(ID_TOOLBOXITEM_HISTOGRAM		 ,4);
	pMetersPane->AddLinkItem(ID_TOOLBOXITEM_IMAGE            ,5);
	pMetersPane->AddLinkItem(ID_TOOLBOXITEM_LINE			 ,6);
	pMetersPane->AddLinkItem(ID_TOOLBOXITEM_ROTATOR          ,7);
	pMetersPane->AddLinkItem(ID_TOOLBOXITEM_ROUNDLINE		 ,8);
	pMetersPane->AddLinkItem(ID_TOOLBOXITEM_STRING           ,9);

	CXTPTaskPanelGroup* pMeansuresPane = CreateToolboxGroup(ID_TOOLBOXFOLDER_MEANSURES);
	pMeansuresPane->AddLinkItem(ID_TOOLBOXITEM_CALC           ,1);
	pMeansuresPane->AddLinkItem(ID_TOOLBOXITEM_CPU			  ,2);
	pMeansuresPane->AddLinkItem(ID_TOOLBOXITEM_DISKSPACE	  ,3);
	pMeansuresPane->AddLinkItem(ID_TOOLBOXITEM_MEMORY		  ,4);
	pMeansuresPane->AddLinkItem(ID_TOOLBOXITEM_NET            ,5);
	pMeansuresPane->AddLinkItem(ID_TOOLBOXITEM_PLUGIN		  ,6);
	pMeansuresPane->AddLinkItem(ID_TOOLBOXITEM_REGISTRY       ,7);
	pMeansuresPane->AddLinkItem(ID_TOOLBOXITEM_TIME			  ,8);
	pMeansuresPane->AddLinkItem(ID_TOOLBOXITEM_UPTIME         ,9);

	/*CXTPTaskPanelGroup* pFolderComponents = CreateToolboxGroup(ID_TOOLBOXFOLDER_COMPONENTS);
	pFolderComponents->AddLinkItem(ID_TOOLBOXITEM_FILESYSTEMWATCHER     ,34);
	pFolderComponents->AddLinkItem(ID_TOOLBOXITEM_EVENTLOG              ,35);
	pFolderComponents->AddLinkItem(ID_TOOLBOXITEM_DIRECTORYENTRY        ,36);
	pFolderComponents->AddLinkItem(ID_TOOLBOXITEM_DIRECTORYSEARCHER     ,37);
	pFolderComponents->AddLinkItem(ID_TOOLBOXITEM_MESSAGEQUEUE          ,38);
	pFolderComponents->AddLinkItem(ID_TOOLBOXITEM_PERFORMANCECOUNTER    ,39);
	pFolderComponents->AddLinkItem(ID_TOOLBOXITEM_PROCESS               ,40);
	pFolderComponents->AddLinkItem(ID_TOOLBOXITEM_SERVICECONTROLLER     ,41);
	pFolderComponents->AddLinkItem(ID_TOOLBOXITEM_TIMER                 ,42);

	CreateToolboxGroup(ID_TOOLBOXFOLDER_CLIPBOARDRING);
	CreateToolboxGroup(ID_TOOLBOXFOLDER_GENERAL);*/

	pMetersPane->SetExpanded(TRUE);
}

void CKitView::OnContextMenu(CWnd* pWnd, CPoint point)
{
	CTreeCtrl* pWndTree = (CTreeCtrl*)&m_wndTaskPanel;
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

	m_wndTaskPanel.SetWindowPos(NULL, rectClient.left + 1, rectClient.top + 1, rectClient.Width() - 2, rectClient.Height() - 2, SWP_NOACTIVATE | SWP_NOZORDER);
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
	m_wndTaskPanel.GetWindowRect(rectTree);
	ScreenToClient(rectTree);

	rectTree.InflateRect(1, 1);
	dc.Draw3dRect(rectTree, ::GetSysColor(COLOR_3DSHADOW), ::GetSysColor(COLOR_3DSHADOW));
}

void CKitView::OnSetFocus(CWnd* pOldWnd)
{
	CDockablePane::OnSetFocus(pOldWnd);

	m_wndTaskPanel.SetFocus();
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


}

CXTPTaskPanel* CKitView::GetTaskPanel()
{
	return &this->m_wndTaskPanel;
}



