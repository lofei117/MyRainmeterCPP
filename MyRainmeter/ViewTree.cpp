
#include "stdafx.h"
#include "ViewTree.h"
#include "MyRainmeter.h"
#include "ConstInfo.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CViewTree

CViewTree::CViewTree()
{
}

CViewTree::~CViewTree()
{
}

BEGIN_MESSAGE_MAP(CViewTree, CTreeCtrl)
	ON_NOTIFY_REFLECT(NM_DBLCLK, &CViewTree::OnNMDblclk)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CViewTree 消息处理程序

BOOL CViewTree::OnNotify(WPARAM wParam, LPARAM lParam, LRESULT* pResult)
{
	BOOL bRes = CTreeCtrl::OnNotify(wParam, lParam, pResult);

	NMHDR* pNMHDR = (NMHDR*)lParam;
	ASSERT(pNMHDR != NULL);

	if (pNMHDR && pNMHDR->code == TTN_SHOW && GetToolTips() != NULL)
	{
		GetToolTips()->SetWindowPos(&wndTop, -1, -1, -1, -1, SWP_NOMOVE | SWP_NOACTIVATE | SWP_NOSIZE);
	}

	return bRes;
}


void CViewTree::OnNMDblclk(NMHDR *pNMHDR, LRESULT *pResult)
{
	// TODO: 在此添加控件通知处理程序代码
	*pResult = 0;
	
	CString file = GetSelectItemPath();
	
	if (!PathIsDirectory(file))
	{
		AfxGetApp()->OpenDocumentFile(file);
	}	
}

CString CViewTree::GetSelectItemPath() const
{
	HTREEITEM hItem = GetSelectedItem();	
	if (!GetParentItem(hItem))
	{
		return L"";
	}

	CString relativePath = GetItemText(hItem);
	HTREEITEM pParent = GetParentItem(hItem);

	while(GetParentItem(pParent))
	{
		relativePath = GetItemText(pParent) + L"\\" + relativePath;

		pParent = GetParentItem(pParent);
	}

	//file =  theApp.m_SkinFolder + L"\\" + file;
	CString file;
	PathCombine(file.GetBuffer(MAX_FILENAME_LENGTH), theApp.m_SkinFolder, relativePath);
	return file;
}
